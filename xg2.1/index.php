<?php
/*
 * index.php edited 13-September-05 again...
 *
 * GNU Licensed
 */
 
 
 /*
  *  Security Check
  */
require_once(dirname(__FILE__) . '/../../mainfile.php');
include XOOPS_ROOT_PATH.'/header.php';
include_once(dirname(__FILE__) . '/includes/functions.inc');
include_once(dirname(__FILE__) . '/class/class.inc');
$xoopsOption['template_main'] = 'xg2_index.html';

 /*
  *  Load language equalizer
  * _LANGCODE carries the language info and it should
  * compatable...
  */
 
global $xg2bodyHtml, $gallery, $xg2bardata;


/* 
 * xtodo: need to develop group associations.  Will xg2 handle more than one group?
 * xtodo: need to develop error handelers for $uid, etc.
 */


if ($xg2bodyHtml==null) {
	
	/* 
	 * First, lets see if we configured xoops to use gallery2
	 * if not then cough, bitch and complain.
	 */
	
	 if ($xoopsModuleConfig['xg2_configed'] == 0){
	 			echo ("<center> "._MI_CONFIGURATION_NOT_DONE." </center> ");
				include XOOPS_ROOT_PATH.'/footer.php';
			return;
		}

	if (!isset($xg2bardata)){
 	if (!xg2Auth::xg2Init(false)){
 	echo "ah crap";
 	}}

	// handle the G2 request

	if ($xoopsModuleConfig['xg2_showSidebar'] == 1) {
		 include XOOPS_ROOT_PATH.'/footer.php';
		GalleryCapabilities::set('showSidebarBlocks', true);
		$xg2data = GalleryEmbed::handleRequest();
		if (isset($xg2data['sidebarBlocksHtml']) && !empty($xg2data['sidebarBlocksHtml'])) {
			$xg2bodyHtml = '<div id="gsSidebar" class = "gcBorder1">' . join('', $xg2data['sidebarBlocksHtml']) . '</div>';
		}
	}
    else {
    	GalleryCapabilities::set('showSidebarBlocks', false);
    	if(isset($xg2bardata)){
    	 		$xg2data =& $xg2bardata;
    	} else {
		$xg2data = GalleryEmbed::handleRequest();
    	}
    }
	
	  
	// show error message if isDone is not defined
	if (!isset($xg2data['isDone'])) {
		echo _MI_ISDONE_FAILED;
		exit;
	}
		    
	// die if it was a binary data (image) request
	if ($xg2data['isDone']) {
		exit; // uploads module does this too
	}
	// Main G2 error message

	//if ($ret) {
	//	echo $ret->getAsHtml();
	//}
	
  } 
  $title = ''; $javascript = array();    $css = array();
  if (isset($xg2data['headHtml'])) {
    list($title, $css, $javascript) = GalleryEmbed::parseHead($xg2data['headHtml']);
    $header = '';
    foreach($css as $csstext) {
			// $cssline = $csstext;
			// $cssline = str_replace('"','\"',$cssline);
			$header .= $csstext; 
  }
    foreach($javascript as $javatext) {
			//$javaline = $javatext;
			//$javaline = str_replace('"','\"',$javaline);
			$header .= $javatext; 
  }
  	
	$xg2bodyHtml=$xg2data['bodyHtml'];
}

// very boring template.  
$xoopsTpl->assign('xg2_header', $header);
$xoopsTpl->assign('xg2_body', $xg2bodyHtml);

include XOOPS_ROOT_PATH.'/footer.php';   

?>

