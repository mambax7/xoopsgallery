<?php
/*
 * $RCSfile: theme.inc,v $
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
/**
 * @version $Revision: 1.9 $ $Date: 2006/03/22 03:52:38 $
 * @package Gallery
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This implements a gallery theme with a scrollable view of all image thumbnails and
 * slideshow support in a single dynamic page.  Displays inline items ONLY; subalbums
 * or other items types are NOT shown.
 *
 * @package GalleryTheme
 * @subpackage Theme
 */
class SliderTheme extends GalleryTheme {

    /**
     * Constructor
     */
    function SliderTheme() {
	global $gallery;

	$this->setId('slider');
	$this->setName($gallery->i18n('Slider'));
	$this->setDescription(
	    $gallery->i18n('Image viewer/slideshow; subalbums/other items not shown'));
	$this->setVersion('1.0.3');
	$this->setRequiredCoreApi(array(7, 0));
	$this->setRequiredThemeApi(array(2, 0));
	$this->setStandardSettings(array(
	    'colorpack' => '',
	    'sidebarBlocks' => serialize(array(
		 array('search.SearchBlock', array('showAdvancedLink' => true)),
		 array('imageblock.ImageBlock', array())))));
    }

    /**
     * @see GalleryTheme::showAlbumPage
     */
    function showAlbumPage(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData($template, $item, $params,
	    array('parents', 'systemLinks', 'itemLinks'),
	    $childIds);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$theme =& $template->getVariableByReference('theme');

	list ($ret, $imageWidths, $imageHeights) =
	    $this->_buildItemList($childIds, $theme['children']);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$theme['imageWidths'] = implode(',', $imageWidths);
	$theme['imageHeights'] = implode(',', $imageHeights);
	$theme['imageCount'] = count($imageWidths);

	$template->head('themes/slider/templates/header.tpl');
	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showPhotoPage
     */
    function showPhotoPage(&$template, $item, $params) {
	$renderId = GalleryUtilities::getRequestVariables('renderId');
	if (!empty($renderId)) {
	    /* Render this item */
	    list ($ret, $image) = GalleryCoreApi::loadEntitiesById($renderId);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $template->setVariable('theme', array('item' => (array)$item,
						  'image' => (array)$image));
	    return array(null, 'render.tpl');
	}

	/* Otherwise, load the parent with initial view of this item  */
	list ($ret, $parent) = GalleryCoreApi::loadEntitiesById($item->getParentId());
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($parent);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $tplFile) = $this->showAlbumPage($template, $parent, $params, $childIds);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$theme =& $template->getVariableByReference('theme');
	foreach ($theme['children'] as $tmp) {
	    if ($tmp['id'] == $item->getId()) {
		if (isset($tmp['imageIndex'])) {
		    $theme['viewIndex'] = $tmp['imageIndex'];
		}
		break;
	    }
	}

	return array(null, $tplFile);
    }

    /**
     * @see GalleryTheme::showModulePage
     */
    function showModulePage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showAdminPage
     */
    function showAdminPage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showErrorPage
     */
    function showErrorPage(&$template) {
	return array(null, 'error.tpl');
    }

    /**
     * @see GalleryTheme::showProgressBarPage
     */
    function showProgressBarPage(&$template, $item, $params) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * Prepare data about items in this album.
     * @access private
     */
    function _buildItemList($childIds, &$children) {
	$imageWidths = $imageHeights = $childItems = array();
	if (!empty($childIds)) {
	    $ret = GalleryCoreApi::studyPermissions($childIds);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $childItems) = GalleryCoreApi::loadEntitiesById($childIds);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $preferredFullImages) =
		GalleryCoreApi::fetchPreferredsByItemIds($childIds);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $resizedImages) =
		GalleryCoreApi::fetchResizesByItemIds($childIds);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    list ($ret, $thumbnails) =
		GalleryCoreApi::fetchThumbnailsByItemIds($childIds);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	}
	$i = -1;
	foreach ($childItems as $child) {
	    $i++;
	    $childId = $child->getId();
	    if (!GalleryUtilities::isA($child, 'GalleryDataItem')) {
		continue;
	    }

	    if (isset($thumbnails[$childId])) {
		if (!($thumbnails[$childId]->getWidth() && $thumbnails[$childId]->getHeight())) {
		    list ($ret, $thumbnails[$childId]) =
			GalleryCoreApi::rebuildDerivativeCache($thumbnails[$childId]->getId());
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		}
		$children[$i]['thumbnail'] = (array)$thumbnails[$childId];
	    }

	    list ($ret, $permissions) = GalleryCoreApi::getPermissions($childId);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    $images = array();
	    if (isset($permissions['core.viewSource'])) {
		/* Full size; check for preferred copy */
		if (isset($preferredFullImages[$childId])) {
		    $images[] = $preferredFullImages[$childId];
		} else if ($child->canBeViewedInline()) {
		    $images[] = $child;
		}
	    }
	    if (isset($permissions['core.viewResizes']) && isset($resizedImages[$childId])) {
		foreach ($resizedImages[$childId] as $resize) {
		    $images[] = $resize;
		}
	    }
	    if (isset($thumbnails[$childId])) {
		$images[] = $thumbnails[$childId];
	    }

	    if (!empty($images)) {
		$image = $images[0];

		/* Rebuild derivative if needed so width/height known */
		if (GalleryUtilities::isA($image, 'GalleryDerivativeImage')
			&& !($image->getWidth() && $image->getHeight())) {
		    list ($ret, $image) = GalleryCoreApi::rebuildDerivativeCache($image->getId());
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		}
		$image = (array)$image;
		$children[$i]['image'] = $image;
		$children[$i]['imageIndex'] = count($imageWidths);
		if (GalleryUtilities::isExactlyA($child, 'GalleryPhotoItem') &&
			    $image['width'] > 0 && $image['height'] > 0) {
		    /* Display in <img> */
		    $imageWidths[] = $image['width'];
		    $imageHeights[] = $image['height'];
		} else {
		    /* Item must render itself */
		    $children[$i]['renderItem'] = 1;
		    $imageWidths[] = $imageHeights[] = -1;
		}
	    }
	}
	return array(null, $imageWidths, $imageHeights);
    }
}
?>
