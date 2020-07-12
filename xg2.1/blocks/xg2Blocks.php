<?php
/*
 * Created on Sep 4, 2005 by greyhair 
 *
 * GPL Released. Enjoy
 * 
 * Edit the folling lines to fit you site or use the Admin
 * Area for this.
 * 
 * Dont need this file if i can get it to pass thru xoops db.
 * 
 */

/*
 * The Gallery 2 image block.		
 *																			
 * 1. Select which block you want to show from the list below:				
 *																			
 * randomImage  : A random image is shown									
 * recentImage  : The most recent image is shown							
 * viewedImage  : The most popular image is shown							
 * randomAlbum  : The highlight from a random album is shown				
 * recentAlbum  : The highlight from the most recent album is shown			
 * viewedAlbum  : The highlight from the most popular album is shown		
 * dailyImage   : A new image each day										
 * weeklyImage  : A new image each week										
 * monthlyImage : A new image each month									
 * dailyAlbum   : A new album highlight each day							
 * weeklyAlbum  : A new album highlight each week							
 * monthlyAlbum : A new album highlight each month							
 *																			
 *   $options[0] = "randomImage";
 *
 * 2. Select what album/image properties you want displayed, you can		
 *    display more than one, but separate them by |	 (the pipe symbol)		
 *																			
 * title   : Show the title													
 * views   : Show how many views the item has								
 * date    : Show the capture/upload date									
 * owner   : Show the item owner											
 * heading : Show the item heading ("Random Image","Daily Image", etc)		
 * fullSize: Show the full sized item (not a thumbnail)						
 * none    : Don't show anything, just the thumbnail						
 *																			
 *   $options[1] = "title|heading";	
 * 
 * 																		  
 */

function b_xg2_image_show($options) {
	//global $xoopsConfig, $xoopsUser, $xoopsModuleConfig, $gallery;
	global $xoopsConfig, $xoopsModule, $xoopsUser, $xoopsModuleConfig;
	require_once(dirname(__FILE__) . '/../../../mainfile.php');
	require_once(dirname(__FILE__) . '/../includes/functions.inc');
	require_once(dirname(__FILE__) . '/../class/class.inc');
	$xg2_dirname = str_replace('\\', '/', dirname(dirname(__FILE__))); // Thanks to CryAngel
	$xg2_dirname = str_replace(XOOPS_ROOT_PATH .'/modules/', '', dirname(dirname(__FILE__)));
	
	if (empty($xoopsModule) || $xoopsModule->getVar('dirname') != $xg2_dirname) {	
		$module_handler =& xoops_gethandler('module');
		$module =& $module_handler->getByDirname($xg2_dirname);
		$config_handler =& xoops_gethandler('config');
		$config =& $config_handler->getConfigsByCat(0,$module->getVar('mid'));
	} else {
		$module =& $xoopsModule;
		$config =& $xoopsModuleConfig;
	}
    $block = array();
    
	require_once(dirname(__FILE__) . '/../'. $config['xg2_relativeG2Path'] .'/' . $config['xg2_embedphpfile']);
	
		
	/*
 	 *  Is XoopsGallery2 configured??
 	 */
 
	if ($config['xg2_configed'] == 0){
	 			$sideBar = "<center> "._MI_CONFIGURATION_NOT_DONE." </center> ";
	 			$block['sidebar'] = $sideBar;
	 			unset($sideBar);			
				return $block;
		}
	/*
	 *  Get who I am...
	 */
	 if (!xg2Auth::xg2Init(true)) {
			return false;
		}
   /*
	if ($config['xg2_showSidebar'] == 1) {
		$block['xg2_blockhtml'] = _XG2_MI_DISABLE_SIDEBAR_FIRST;
		return $block;
		}
	*/
	
/* 
 * No longer need to handleReqest for getting random, etc images.
   $ret = GalleryEmbed::handleRequest();
   	if ($ret['isDone']){
   		echo('error');
  	}
 */  	 
   	
    $iTimes=1;
    $typeOptions = $options[0];
    if ($iTimes <  $options[1]){
    	while ($iTimes < $options[1]) {
   			$typeOptions .= '|'. $options[0];
   			$iTimes++;
		}
    }
   	
	list($ret,$html,$head) = GalleryEmbed::getImageBlock(array('blocks'=>$typeOptions,'show'=>$options[2]));
	
	// $block['blockhead'] = $head;
	$block['xg2_blockhtml'] = $html;
		
/* no longer need done??
	$ret2 = GalleryEmbed::done();
	 if ($ret2){
   		$ret2->getAsHtml();
   	}
 */
	return $block;
	}
/*
 * end of block function
 * 
 */

function xg2_ImageBlock_edit ($options){
	/*
	 * 
	 */
$form = "<table width=\"75%\"  border=\"0\">" .
		"<tr><td>&nbsp;</td><td>&nbsp;</td><td>".
		_XG2_BLOCK_TYPE_DESC .
		"</td></tr>".
		"<tr><td> <div align=\"right\">*" .
		_XG2_RANDOMIMAGE ."<br />" .
		_XG2_RECENTIMAGE ."<br />" .
		_XG2_VIEWEDIMAGE ."<br />" .
		_XG2_RANDOMALBUM ."<br />" .
		_XG2_RECENTALBUM ."<br />" .
		_XG2_VIEWEDALBUM ."<br />" .
		_XG2_DAILYIMAGE ."<br />" .
		_XG2_WEEKLYIMAGE ."<br />" .
		_XG2_MONTHLYIMAGE ."<br />" .
		_XG2_DAILYALBUM ."<br />" .
		_XG2_WEEKLYALBUM ."<br />" .
		_XG2_MONTHLYALBUM ."</div></td>" .
		"  <td>&nbsp;</td> <td>" .
		_XG2_RANDOMIMAGE_DESC ."<br />" .
		_XG2_RECENTIMAGE_DESC ."<br />" .
		_XG2_VIEWEDIMAGE_DESC ."<br />" .
		_XG2_RANDOMALBUM_DESC ."<br />" .
		_XG2_RECENTALBUM_DESC ."<br />" .
		_XG2_VIEWEDALBUM_DESC ."<br />" .
		_XG2_DAILYIMAGE_DESC ."<br />" .
		_XG2_WEEKLYIMAGE_DESC ."<br />" .
		_XG2_MONTHLYIMAGE_DESC ."<br />" .
		_XG2_DAILYALBUM_DESC ."<br />" .
		_XG2_WEEKLYALBUM_DESC ."<br />" .
		_XG2_MONTHLYALBUM_DESC ."</div></td>" .
		"  </tr>" .
		"  <tr><td> <div align=\"right\">" .
		_XG2_BLOCK_TYPE .
		"</div></td>" .
		"  <td>&nbsp;</td>" .
		"  <td> <select name=\"options[0]\">" ;
$form	.= "<option value=\"randomImage\"";
		if($options[0]=="randomImage") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_RANDOMIMAGE ."</option>";
$form	.= "<option value=\"recentImage\"";
		if($options[0]=="recentImage") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_RECENTIMAGE ."</option>";
$form	.= "<option value=\"viewedImage\"";
		if($options[0]=="viewedImage") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_VIEWEDIMAGE ."</option>";
$form	.= "<option value=\"randomAlbum\"";
		if($options[0]=="randomAlbum") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_RANDOMALBUM ."</option>";
$form	.= "<option value=\"recentAlbum\"";
		if($options[0]=="recentAlbum") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_RECENTALBUM ."</option>";
$form	.= "<option value=\"viewedAlbum\"";
		if($options[0]=="viewedAlbum") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_VIEWEDALBUM ."</option>";
$form	.= "<option value=\"dailyImage\"";
		if($options[0]=="dailyImage") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_DAILYIMAGE ."</option>";
$form	.= "<option value=\"weeklyImage\"";
		if($options[0]=="weeklyImage") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_WEEKLYIMAGE ."</option>";
$form	.= "<option value=\"monthlyImage\"";
		if($options[0]=="monthyImage") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_MONTHLYIMAGE ."</option>";
$form	.= "<option value=\"dailyAlbum\"";
		if($options[0]=="dailyAlbum") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_DAILYALBUM ."</option>";
$form	.= "<option value=\"weeklyAlbum\"";
		if($options[0]=="weeklyAlbum") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_WEEKLYALBUM ."</option>";
$form	.= "<option value=\"monthlyAlbum\"";
		if($options[0]=="monthyAlbum") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_MONTHLYALBUM ."</option>";

$form	.=" </select></td>" .
		"</tr> <tr> <td>" .
		_XG2_BLOCK_TYPE_TIMES .
		":</td> <td>&nbsp;</td> <td>" .
		"  <td> <select name=\"options[1]\">";
$form	.= "<option value=1";
		if($options[1]==1) {$form .= " selected='selected' ";}
$form	.= ">1</option>";
$form	.= "<option value=2";
		if($options[1]==2) {$form .= " selected='selected' ";}
$form	.= ">2</option>";
$form	.= "<option value=3";
		if($options[1]==3) {$form .= " selected='selected' ";}
$form	.= ">3</option>";
$form	.= "<option value=4";
		if($options[1]==4) {$form .= " selected='selected' ";}
$form	.= ">4</option>";
$form	.= "<option value=5";
		if($options[1]==5) {$form .= " selected='selected' ";}
$form	.= ">5</option>";
$form	.= "<option value=6";
		if($options[1]==6) {$form .= " selected='selected' ";}
$form	.= ">6</option>";
$form	.= "<option value=7";
		if($options[1]==7) {$form .= " selected='selected' ";}
$form	.= ">7</option>";
$form	.= "<option value=8";
		if($options[1]==8) {$form .= " selected='selected' ";}
$form	.= ">8</option>";
$form	.= "<option value=9";
		if($options[1]==9) {$form .= " selected='selected' ";}
$form	.= ">9</option>";
$form	.= "<option value=10";
		if($options[1]==10) {$form .= " selected='selected' ";}
$form	.= ">10</option>";
$form	.=" </select></td></tr> <tr> <td>&nbsp;</td> <td>&nbsp;</td> <td>" .
		"</tr> <tr> <td>&nbsp;</td> <td>&nbsp;</td> <td>&nbsp;</td> </tr> <tr>" .
		"<tr> <td>&nbsp;</td> <td>&nbsp;</td> <td>" .
		_XG2_BLOCK_OPTIONS_DESC .
		"</td> </tr> " .
		"<tr> <td><div align=\"right\">" .
		_XG2_BLOCK_NONE . "<br />" .
		_XG2_BLOCK_TITLE . "<br />" .
		_XG2_BLOCK_VIEWS . "<br />" .
		_XG2_BLOCK_DATE . "<br />" .
		_XG2_BLOCK_OWNER . "<br />" .
		_XG2_BLOCK_HEADING . "<br />" .
		_XG2_BLOCK_FULLSIZE . "<br />" .
		" </div></td><td>&nbsp;</td><td>" .
		_XG2_BLOCK_NONE_DESC . "<br />" .
		_XG2_BLOCK_TITLE_DESC . "<br />" .
		_XG2_BLOCK_VIEWS_DESC . "<br />" .
		_XG2_BLOCK_DATE_DESC . "<br />" .
		_XG2_BLOCK_OWNER_DESC . "<br />" .
		_XG2_BLOCK_HEADING_DESC . "<br />" .
		_XG2_BLOCK_FULLSIZE_DESC . "<br />" .
  		" </td></tr> <tr> <td><div align=\"right\">" .
  		_XG2_BLOCK_OPTIONS .
  		":</div></td> <td>&nbsp;</td> <td>
        <select name=\"options[2]\" size=\"7\" multiple id=\"options[2]\">";
$form	.= "<option value=\"none\"";
		if($options[2]=="none") {$form .= " selected='selected'  ";}
$form	.= ">". _XG2_BLOCK_NONE ."</option>";
$form	.= "<option value=\"title\"";
		if($options[2]=="title") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_BLOCK_TITLE ."</option>";
$form	.= "<option value=\"views\"";
		if($options[2]=="views") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_BLOCK_VIEWS ."</option>";
$form	.= "<option value=\"date\"";
		if($options[2]=="date") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_BLOCK_DATE ."</option>";
$form	.= "<option value=\"owner\"";
		if($options[2]=="owner") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_BLOCK_OWNER ."</option>";
$form	.= "<option value=\"heading\"";
		if($options[2]=="heading") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_BLOCK_HEADING ."</option>";
$form	.= "<option value=\"fullsize\"";
		if($options[2]=="fullsize") {$form .= " selected='selected' ";}
$form	.= ">"._XG2_BLOCK_FULLSIZE ."</option>";
         
$form	.=" </select>" .
		"</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>" .
		"</tr> </table>";

return $form;

}
function xg2_SideBar_show(){
	require_once(dirname(__FILE__) . '/../../../mainfile.php');
	require_once(dirname(__FILE__) . '/../includes/functions.inc');
	require_once(dirname(__FILE__) . '/../class/class.inc');
	
	global $xoopsConfig, $xoopsUser, $xoopsModule, $xoopsModuleConfig, $gallery, $xg2bardata;
	
	$xg2_dirname = str_replace(XOOPS_ROOT_PATH .'/modules/', '', dirname(dirname(__FILE__)));
	
	if (empty($xoopsModule) || $xoopsModule->getVar('dirname') != $xg2_dirname) {	
		$module_handler =& xoops_gethandler('module');
		$module =& $module_handler->getByDirname($xg2_dirname);
		$config_handler =& xoops_gethandler('config');
		$config =& $config_handler->getConfigsByCat(0,$module->getVar('mid'));
	} else {
		$module =& $xoopsModule;
		$config =& $xoopsModuleConfig;
	}

	require_once(dirname(__FILE__) . '/../'. $config['xg2_relativeG2Path'] .'/'. $config['xg2_embedphpfile']);
		
	$block = array();
	$sideBar = '';
	/*
 	 *  Is XoopsGallery2 configured??
 	 */
	if ($config['xg2_configed'] == 0){
	 			$sideBar = "<center> "._MI_CONFIGURATION_NOT_DONE." </center> ";
	 			$block['sidebar'] = $sideBar;
	 			unset($sideBar);			
				return $block;
		}
	 $retInit = xg2Auth::xg2Init(true);
	 if (!$retInit) {
			return false;
		}

	if ($xoopsModuleConfig['xg2_showSidebar'] == 1) {
		$sideBar = _XG2_MI_DISABLE_SIDEBAR_FIRST;
		$block['sidebar'] = $sideBar;
		unset($sideBar);
		return $block;
		}
 
	GalleryCapabilities::set('showSidebarBlocks', false);
	$xg2bardata = GalleryEmbed::handleRequest();

	if (isset($xg2bardata['headHtml'])) {
		list($title, $css, $javascript) = GalleryEmbed::parseHead($xg2bardata['headHtml']);
	}

	if(!isset($xg2bardata['sidebarBlocksHtml'])) {
		$sideBar = _XG2_MI_ENABLE_SIDEBAR_IN_G2;
	}
	else { 
		$num_blocks = count($xg2bardata['sidebarBlocksHtml']) - 1;
	/*
	 *  We dont want the style sheet or jave script with the menu bar
	 *  We do, by the way, pick this up in the main window.
	 * 
		foreach($css as $stylesheet) {
			$sideBar .= $stylesheet;
		}
		foreach($javascript as $java) {
			$sideBar .= $java;
		}
	 *
	 *
	 */
	 
		$sideBar .= "<div id=\"gsSidebar\">";
			for($i = 0; $i <= $num_blocks; $i++) {
				$sideBar .= $xg2bardata['sidebarBlocksHtml'][$i];
			}
		$sideBar .= "</div>";
	}
	$block['sidebar'] = $sideBar;
	unset($sideBar);
	GalleryEmbed::done();
	return $block;
	
}
function xg2_SideBar_edit(){

}
 /*
  * End of Sidebar block
  */


?>