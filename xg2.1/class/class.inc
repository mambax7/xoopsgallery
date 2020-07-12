<?php
/*
 * Created on Nov 23, 2005
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 /*
 * getMyUid is a function to determine two things 
 * is the user an admin (yes, then pass uid as admin, no determine uid)
 * 
 * xtodo:  $xoopsUser->isActive() may help security??
 */
 
class xg2Auth {
	 
function xg2_getMyUid()
{ 
	global $xoopsUser;
		if (!$xoopsUser == ''){
 			if ($xoopsUser->getVar('uid') != "")	{
			$uId = $xoopsUser->getVar('uid');	
			} 
		}
	
		if ($xoopsUser == ''){
			$uId = 0;
		}
	// return what you found!
	return $uId;
}

function xg2Init($fullInit = true)
 
  {	
  	global $xoopsConfig, $xoopsModule, $xoopsUser, $xoopsModuleConfig, $gallery;
  	include_once(XOOPS_ROOT_PATH . '/mainfile.php');
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
	require_once(dirname(__FILE__) . '/../'. $config['xg2_relativeG2Path'] .'/' . $config['xg2_embedphpfile']);
	
    // only init if not already done so
    if ( xg2Auth::isInitiated() ) {
    	 return true;
    }
    
    if ($config['xg2_configed'] == 0){
		return false;
    }
	$activeUser=xg2Auth::xg2_getMyUid();
    // initiate G2 
    /*
     *  The old way
     * $ret = GalleryEmbed::init(array('embedPath' => $config['xg2_embedPath'],
									'embedUri' => $config['xg2_embedUri'],
									'relativeG2Path' => $config['xg2_relativeG2Path'],
									'loginRedirect' => $config['xg2_loginRedirect'],
									'activeUserId' => $activeUser,
									'activeLanguage' =>_LANGCODE,
				    				'fullInit' => $fullInit));
     */
	$ret = GalleryEmbed::init(array('embedUri' => $config['xg2_embedUri'],
									'g2Uri' => $config['xg2_baseG2Uri'],
									'loginRedirect' => $config['xg2_loginRedirect'],
									'activeUserId' => $activeUser,
									'activeLanguage' => _LANGCODE,
				    				'fullInit' => $fullInit));

	if ($ret) {
		if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			// check if there's no G2 user mapped to the activeUserId
			$ret = GalleryEmbed::isExternalIdMapped($activeUser, 'GalleryUser');
			if ($ret && ($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {
				/* 
				 * xoops user is not mapped to a G2 user, create G2 user now
				 * Get Arguments for the new user:
				 * fullname may not be set, I"m hoping that this is not
				 * required.				 
				 *
				 * Here is a v2.0.13+ to 2.2.4 fix
				 * 2.0.13+ uses uname
				 * 2.2.3+ uses loginname
				 */
				if(!$xoopsUser->getVar('loginname')){
					//v2.0.13
					$xoopsUserName = $xoopsUser->getVar('uname');
					echo('uname');
					$xoopsFullName = $xoopsUser->getVar('name');
				}else{
					//v2.2.x
					$xoopsUserName = $xoopsUser->getVar('loginname');
					echo('loginname');
					$xoopsFullName = $xoopsUser->getVar('uname');
				};
				
				$args['fullname']  	=	$xoopsFullName;
				$args['username'] 	= 	$xoopsUserName;
				$args['hashedpassword'] =	$xoopsUser->getVar('pass');
				$args['hashmethod'] = 	'md5';
				$args['email'] 		=	$xoopsUser->getVar('email');
				$args['language']	=	_LANGCODE;
				// FYI, the admin's creation date is 0
				$args['creationtimestamp']	=	$xoopsUser->getVar('user_regdate');
				
				/*
				 *  This makes the user!
				 */
									
				$retcreate = GalleryEmbed::createUser($activeUser, $args);
				if ($retcreate) {
					/*
					 *  Oh no, it didn't work.
					 */
					echo _MI_FAILED_TO_CREATE_1 . $args['username'] .', '. $activeUser . _MI_FAILED_TO_CREATE_2 . $retcreate->getAsHtml();
					return false;
				}
									
				/*
				 *  Wha? I dont understand what the external map entry does.  This could
				 *  create the externalMapEntry if doesnt' exist.  Further reading shows that
				 *  either createUeser or addExternalMapEntry is used. not both.  ...we'll see...
				 */
				
				//if (!xg2_addExternalMapEntry($xoopsUser->getVar('uname'), $activeUser, 0, $gallery)) {
				//	return false;
				//}
					 		
				/*
				 *  Full XG2 initialization with the newly created user
				 *  
				
				$ret = GalleryEmbed::init(array('embedPath' => $config['xg2_embedPath'],
									'embedUri' => $config['xg2_embedUri'],
									'relativeG2Path' => $config['xg2_relativeG2Path'],
									'loginRedirect' => $config['xg2_loginRedirect'],
									'activeUserId' => $activeUser,
									'activeLanguage' =>_LANGCODE,
									'fullInit' => 'true'));
				 */
				$ret = GalleryEmbed::init(array('embedUri' => $config['xg2_embedUri'],
									'g2Uri' => $config['xg2_baseG2Uri'],
									'loginRedirect' => $config['xg2_loginRedirect'],
									'activeUserId' => $activeUser,
									'activeLanguage' =>_LANGCODE,
				    				'fullInit' => 'true'));
			} 
			else {
				/*
				 * Not an unknown user error (dern) 
				 */
				echo _XG2_MI_FAILED ."(dern)" . $ret->getAsHtml();
			}
		} 
		else {
			echo _XG2_MI_FAILED . $ret->getAsHtml();
		}
	}
   echo($ret);
   if (!$ret) {
       xg2Auth::isInitiated(true);
       return true;
   }
  }
  

function isInitiated($newvalue = null)
  {
  	static $initiated;
    if (!isset($initiated)) {
      $initiated = false;
    }
    if (isset($newvalue) && (is_bool($newvalue) || is_int($newvalue))) {
      $initiated = $newvalue;
    }
    return $initiated;
  }
  }
?>
