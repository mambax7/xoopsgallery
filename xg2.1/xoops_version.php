<?php
/*
 * Start the Security! 
 * FYI, If xoops_root_path isn't defigned we are in trouble
 */
if( ! defined( 'XOOPS_ROOT_PATH' ) ) exit ;
include_once(XOOPS_ROOT_PATH.'/mainfile.php');

/*
 *  Trying to have a free directory structure here
 *  I hope :)
 */
$myxg2name = basename( dirname( __FILE__ ) ) ;

/*
 * Start xoops_version.php proper
 */

$modversion['name'] = _XG2_MI_NAME;
$modversion['version'] = '2.04';
$modversion['description'] = _XG2_MI_DESCRIPTION;
$modversion['author'] = 'Greyhair';
$modversion['credits'] = _XG2_MI_CREDITS;
$modversion['help'] = 'http://www.xoopsgallery.org/';
$modversion['license'] = 'GPL';
$modversion['official'] = 1;
$modversion['image'] = 'images/gallery-tag.png';
$modversion['dirname'] = "$myxg2name";

// Sql file (must contain sql generated by phpMyAdmin or phpPgAdmin)
// All tables should not have any prefix!
$modversion['sqlfile']['mysql'] = "sql/mysql.sql";
//$modversion['sqlfile']['postgresql'] = "sql/pgsql.sql";

// Tables created by sql file (without prefix!)
$modversion['tables'][0] = "xg2_data";

// Admin things
/*
 * Currently, there isn't anything to admin
 * xtodo: User sync, Group sync, and other "admin" functions
 */
$modversion['hasAdmin'] = 1;
$modversion['adminindex'] = "admin/index.php";
$modversion['adminmenu'] = "admin/menu.php";

/*
 * Blocks
 */
$modversion['blocks'][1]['file'] = "xg2Blocks.php";
$modversion['blocks'][1]['name'] = _XG2_MI_BLOCK_SIDEBAR;
$modversion['blocks'][1]['description'] = _XG2_MI_BLOCK_SIDEBAR_DES;
$modversion['blocks'][1]['show_func'] = "xg2_SideBar_show";
$modversion['blocks'][1]['edit_func'] = "xg2_SideBar_edit";
$modversion['blocks'][1]['template'] = "xg2_block_sidebar.html";
$modversion['blocks'][2]['file'] = "xg2Blocks.php";
$modversion['blocks'][2]['name'] = _XG2_MI_BLOCK_IMAGE;
$modversion['blocks'][2]['description'] = _XG2_MI_BLOCK_IMAGE_DES;
$modversion['blocks'][2]['show_func'] = "b_xg2_image_show";
$modversion['blocks'][2]['options'] = "randomImage|3|none";
$modversion['blocks'][2]['edit_func'] = "xg2_ImageBlock_edit";
$modversion['blocks'][2]['template'] = "xg2_block_image.html";



/* 
 * Templates 
 */

 $modversion['templates'][1]['file'] = 'xg2_index.html';
 $modversion['templates'][1]['description'] = _XG2_MI_INDEX_DESCRIPTION;



/*
 * Comments
 * This will be fun. NOT.
 * A gallery 2 module needs to be made to blend the gallery 2 and xoops comments
 */
$modversion['hasComments'] = 0;
// $modversion['comments']['itemName'] = 'xoops_imageid';
// $modversion['comments']['pageName'] = 'view_photo.php';
// $modversion['comments']['extraParams'] = array('albumName', 'id');

// Comment callback functions
// $modversion['comments']['callbackFile'] = 'include/functions.php';
// $modversion['comments']['callback']['approve'] = 'xoopsgallery_com_approve';
// $modversion['comments']['callback']['update'] = 'xoopsgallery_com_update';

/*
 *  Currently no extra functions needed.
 */
// Extra install/uninstall script for this module
// $modversion['onInstall'] = 'include/functions.php';
// $modversion['onUninstall'] = 'include/functions.php';

// Config options
/*
 *  So far these are only the xoops to gallery2 params. 
 */
 
/*
 *  What is this.. and how to use it.
 */
$modversion['hasMain'] = 1;
$modversion['hasconfig'] = 1;
 
// Name of the file that embeds gallery2 into xoops (or any CMS)
// Typically embed.php (see default) 
$modversion['config'][0] = array(
	'name' => 'xg2_embedphpfile',
	'title' => '_MI_EMBED_PHP_FILE',
	'description' => '_MI_EMBED_PHP_FILE_DSC',
	'formtype' => 'textbox',
	'valuetype' => 'text',
	'default' => "embed.php");
//
// gallery 2 is asking for the file name that creates the link
// between gallery2 and xoops (index.php)
// First build the embed uri example http://www.mydomain.com/modules/xg2/index.php
// If I'm wrong well fix it... it is but a guess.
$defaultURI = dirname(dirname('http://'. $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'])) .'/'.$modversion['dirname']. '/index.php';
$modversion['config'][1] = array(
	'name' => 'xg2_embedUri',
	'title' => '_XG2_MI_EMBED_URI',
	'description' => '_XG2_MI_EMBED_URIDSC',
	'formtype' => 'textbox',
	'valuetype' => 'text',
	'default' => $defaultURI);
// relativeG2Path - The New Gallery 2 (2.1) does not use this any more, but
// I do. I call it engine, you call it what you want, just remember to change
// the engine directory name too.
$modversion['config'][2] = array(
	'name' => 'xg2_relativeG2Path',
	'title' => '_XG2_MI_RELATIVE_G2_PATH',
	'description' => '_XG2_MI_RELATIVE_G2_PATHDSC',
	'formtype' => 'textbox',
	'valuetype' => 'text',
	'default' => "engine");
// What should be "spit out" if the login is not currnet or we are not
// logged in. (http://www.mysite.com/user.php)
// I'm gunna try to guess here -- backup 3 levels...
$redirectPATH = dirname(dirname(dirname('http://'. $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF']))) . '/user.php';
$modversion['config'][3] = array(
	'name' => 'xg2_loginRedirect',
	'title' => '_XG2_MI_LOGIN_REDIRECT',
	'description' => '_XG2_MI_LOGIN_REDIRECTDSC',
	'formtype' => 'textbox',
	'valuetype' => 'text',
	'default' => $redirectPATH);
// activeUserId.  Currently set to 1 but i think it should be 0
// xtodo: investigate activeUserId.
$modversion['config'][4] = array(
	'name' => 'xg2_activeUserId',
	'title' => '_XG2_MI_ACTIVE_USERID',
	'description' => '_XG2_MI_ACTIVE_USERIDDSC',
	'formtype' => 'textbox',
	'valuetype' => 'text',
	'default' => "1");
// baseg2URI.  This is the path to the gallery2 installation.
$baseg2URI = dirname(dirname('http://'. $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'])) .'/'.$modversion['dirname']. '/engine/';
$modversion['config'][5] = array(
	'name' => 'xg2_baseG2Uri',
	'title' => '_XG2_MI_BASE_URI',
	'description' => '_XG2_MI_BASE_URIDSC',
	'formtype' => 'textbox',
	'valuetype' => 'text',
	'default' => $baseg2URI);
// the http path for the cookie root.  Xoops seams to be 
// http://www.mysite.com/ or "/"
//
$modversion['config'][6] = array(
	'name' => 'xg2_cookiepath',
	'title' => '_XG2_MI_COOKIE_PATH',
	'description' => '_XG2_MI_COOKIE_PATHDSC',
	'formtype' => 'textbox',
	'valuetype' => 'text',
	'default' => "/");
// Do you want gallery to show a side bar inside the "main" display or
// would you like to use the sidebar block, your choice just remember to 
// reflect these settings in the gallery2 site administration section too.
//
$modversion['config'][7] = array(
	'name' => 'xg2_showSidebar',
	'title' => '_XG2_MI_SHOW_SIDEBAR',
	'description' => '_XG2_MI_SHOW_SIDEBARDSC',
	'formtype' => 'yesno',
	'valuetype' => 'init',
	'default' => "0");
// Q: Have we configured gallery2 and the xoopsgallery2 module?
// A: Who's we, buddy!  If you say no, you get an error screen. 
//
$modversion['config'][8] = array(
	'name' => 'xg2_configed',
	'title' => '_XG2_MI_CONFIG_DONE',
	'description' => '_XG2_MI_CONFIG_DONEDSC',
	'formtype' => 'yesno',
	'valuetype' => 'init',
	'default' => "0");
// Currently done.
//
//
?>
