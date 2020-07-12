<?php
/*
 * Created on Sep 2, 2005 by greyhair
 * 
 * GNU licensed.. read up!
 * 
 * I'm hoping this is for security.
 */
include_once(dirname(__FILE__) . '/../../../mainfile.php');



/*
 * xg2_addexternalMapEntry: add an externalId map entry
 *
 * Add an entry in the G2 externalId, entityId map table
 *
 * @author Andy Staudacher
 * @access public
 * @param integer the uid
 * @param integer the entityId from G2
 * @param integer/string the roles type, 1 for groups, 0 for users, or the entityType string
 * @return bool true or false
 */

function xg2_addExternalMapEntry($externalId, $entityId, $entityType, $gallery) 
	{
		global $xoopsModuleConfig, $gallery;
		include_once(dirname(__FILE__) . '/../' . $xoopsModuleConfig['xg2_relativeG2Path'] .'/'. $xoopsModuleConfig['xg2_embedphpfile']);
		
		
		if (is_int($entityType)) {
			$entityType = $entityType == 0 ? 'GalleryUser' : 'GalleryGroup';
			}
		// We are looking for Gallery 2's ExternalIdMap.class, btw.
		require_once (dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/modules/core/classes/ExternalIdMap.class');
		
		$ret = ExternalIdMap :: addMapEntry(array ('externalId' => $externalId,
												   'entityType' => $entityType,
												   'entityId' => $entityId));
		if ($ret) {
			echo ('Failed to create a extmap entry for role uid ['.$externalId.'] and entityId ['.$entityId.'], entityType ['.$entityType.']. Here is the error message from G2: <br />'.$ret->getAsHtml());
			return false;
		}
		return true;
	}



/*
 * xg2_getallexternalIdmappings: get all extId, entityId mappings
 *
 * get all extId, entityId mappings from G2
 * useful, i.e. for import/export synchronization update
 * used only by the import/export method
 *
 * @author Andy Staudacher
 * @return array(bool success, array(entityId => array(externalId => integer,
 *                             entityType => string, entityId => integer)),
 *                             array(externalId => array(externalId => integer,
 *                             entityType => string, entityId => integer)))
 * @throws Systemexception if it failed
 */
function xg2_getAllExternalIdMappings() {
		// init G2 transaction, load G2 API, if not already done so
		require_once (dirname(__FILE__) . '/../class/class.inc');
		if (!xg2Auth::xg2Init(false)){
			return ;
		}
		
		global $xoopsUser, $xoopsModuleConfig, $gallery;
		require_once (dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/modules/core/classes/ExternalIdMap.class');
		require_once (dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/modules/core/classes/GalleryStorage.class');
		
		// require_once (dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/modules/core/classes/DatabaseSearchResults.class');
		$query = 'SELECT [ExternalIdMap::entityId], [ExternalIdMap::externalId], [ExternalIdMap::entityType]
					FROM [ExternalIdMap]';
    
    	list ($ret, $results) = $gallery->search($query, array());
    	
    	if ($ret) {
      		echo('Failed to fetch a list of all extId maps fromG2. Here is the error message from G2: <br /> [#(1)]'. $ret->getAsHtml());
            return array(false, null, null); 
    	}
    	
        $mapsbyentityid = array();
    	$mapsbyexternal = array();
    	
    	while ($result = $results->nextResult()) {
			$entry = array('externalId' => $result[1], 'entityId' => $result[0], 'entityType' => $result[2]);
			$mapsbyentityid[$result[0]] = $entry;
      		$mapsbyexternal[$result[1]] = $entry;
    	}
    
    	return array(true, $mapsbyentityid, $mapsbyexternal);
	}

/*
 * xoops API                                          
 * Lists xoops users
 * 
 */

function xg2_listXoopsUsers()
{
	global $xoopsUser, $xoopsModuleConfig, $xoopsModule, $gallery;
		$member_handler = &xoops_gethandler('member');
		$thisModuleid = $xoopsModule->getVar('mid');
      	$criteria = new Criteria('level', 0, '>');
        $criteria->setSort('name');
        $userslist =& $member_handler->getUserList($criteria);
        echo ('<table border="1"> <tr><td><b>'.
               _XG2_USER_ID .'</b></td><td><b>'.
               _XG2_USER_NAME .'</b></td><td><b>'. 
               _XG2_MODULE_ADMIN .'</b></td></tr>');
        foreach ($userslist as $u_id => $u_name) {
            echo ('<tr><td><b>'.$u_id .'</b></td><td><b>'. $u_name .'</b></td>');
              $isMember =& xoops_gethandler('member');
              $isUser =& $isMember->getUser($u_id);
              $isItGallery =& $isUser->isAdmin($thisModuleid);
            if ($isItGallery){
           		echo ('<td>'. _YES .'</td></tr>');
            } else{
           echo ('<td></td></tr>');
            }
        }
        echo ('</table>');
}

function xg2_listXoopsInActiveUsers()
{
	global $xoopsUser, $xoopsModuleConfig, $xoopsModule, $gallery;
		$member_handler = &xoops_gethandler('member');
		$thisModuleid = $xoopsModule->getVar('mid');
      	$criteria = new Criteria('level', 0, '>');
        $criteria->setSort('name');
        $userslist =& $member_handler->getUserList($criteria);
        echo ('<table border="1"> <tr><td><b>'.
               _XG2_USER_ID .'</b></td><td><b>'.
               _XG2_USER_NAME .'</b></td><td><b>'. 
               _XG2_MODULE_ADMIN .'</b></td></tr>');
        foreach ($userslist as $u_id => $u_name) {
            echo ('<tr><td><b>'.$u_id .'</b></td><td><b>'. $u_name .'</b></td>');
              $isMember =& xoops_gethandler('member');
              $isUser =& $isMember->getUser($u_id);
              $isItGallery =& $isUser->isAdmin($thisModuleid);
            if ($isItGallery){
           		echo ('<td>'. _YES .'</td></tr>');
            } else{
           echo ('<td></td></tr>');
            }
        }
        echo ('</table>');
}

/*
 * XOOPs API                                          
 * lists xoops groups 
 * 
 *  - 1 June 06 fixed show group id only and fixed table layout.
 */
function xg2_listXoopsGroups()
{
	global $xoopsUser, $xoopsModuleConfig, $xoopsModule, $gallery;
		$member_handler =& xoops_gethandler('member');
		$grouplist =& $member_handler->getGroups();
		$count = count($grouplist);
        echo ('<table border="1"> <tr><td><b>'.
               _XG2_GROUP_ID .'</b></td><td><b>'.
               _XG2_GROUP_NAME .'</b></td></tr>');
        for ($i = 0; $i < $count; $i++) {
        	$gperm_handler =& xoops_gethandler('groupperm');
        	$groupRead=$gperm_handler->checkRight("module_read", $xoopsModule->getVar('mid'), $grouplist[$i]->getVar('groupid'), 1);
        	$groupAdmin=$gperm_handler->checkRight("module_admin", $xoopsModule->getVar('mid'), $grouplist[$i]->getVar('groupid'), 1);
        	if ($groupRead || $groupAdmin){
            echo ('<tr><td><b>'.$grouplist[$i]->getVar('groupid').'</b></td><td><b>'. $grouplist[$i]->getVar('name') .'</b></td></tr>');
        	}
        }
        echo ('</table>');
}

/*
 * Exports xoops groups to gallery2
 */
function xg2_ExportGroups()
{
	/* 
	 * This is to export the xoopsgallery capable groups to gallery 2
	 * 1. Start the G2 Api
	 * 2. See if the group exists, if not make one.
	 * 3. See if we are already a group update
	 * 4. done.
	 * 				 
	 */
  	global $xoopsUser, $xoopsModuleConfig, $xoopsModule, $gallery;
   	include_once(XOOPS_ROOT_PATH . '/mainfile.php');
  	require_once(dirname(__FILE__).'/../class/class.inc');
  	require_once(dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/' . $xoopsModuleConfig['xg2_embedphpfile']);
  	
  	// start G2 API, please.
  		$ret = GalleryEmbed::init();
  		if ($ret) {
   			 echo($ret->getAsHtml()); // API init had error, details..
 		 }
  	
		$member_handler =& xoops_gethandler('member');
		$grouplist =& $member_handler->getGroups();
		$count = count($grouplist);
        
        for ($i = 0; $i < $count; $i++) {
        	$xgDone = '';
        	$gperm_handler =& xoops_gethandler('groupperm');
        	$groupRead=$gperm_handler->checkRight("module_read", $xoopsModule->getVar('mid'), $grouplist[$i]->getVar('groupid'), 1);
        	$groupAdmin=$gperm_handler->checkRight("module_admin", $xoopsModule->getVar('mid'), $grouplist[$i]->getVar('groupid'), 1);
			$xoopsGroupId = $grouplist[$i]->getVar('groupid');
			$xoopsGroupName= $grouplist[$i]->getVar('name');
			$args['groupname']=$xoopsGroupName;
			$xgDone = false; 
			/* 
			 * is the group able to access (read or admin)?
			 */
			if ($groupRead || $groupAdmin ){
				
			/*
			 * If yes first need to see if we are "maped" already
			 */
			 $ret = GalleryEmbed::isExternalIdMapped($xoopsGroupId, 'GalleryGroup');
			 			 
				if ($ret) {
				 $query = '
							SELECT	[GalleryGroup::id]
							FROM	[GalleryGroup]
							WHERE	[GalleryGroup::groupName] = ?
						';
					
					list($ret, $results) = $gallery->search($query, $xoopsGroupName);
	    			$result = $results->nextResult();
	    			if($result){
	     				$retExport=GalleryEmbed::addExternalIdMapEntry($xoopsGroupId, $result[0], 'GalleryGroup');
	     				$xgMsg= _XG2_GROUP_EXPORTCREATED;
	     				$xgDone = true;
	     				
	    			} 
					
					if(!$xgDone){
						$retcreate = GalleryEmbed::createGroup($xoopsGroupId, $args['groupname']);
						$xgMsg= _XG2_GROUP_CREATED;
	     				$xgDone = true;
	     				
	     				if($retcreate){
	     					$xgDone = false;
	     					echo (_MI_FAILED_TO_CREATE_1 . $args['groupname'] .', '. $xoopsGroupId . _MI_FAILED_TO_CREATE_2 . $retcreate->getAsHtml());
	     					return;
	     				}
	    			}	
				} else {
					$retcreate2 = GalleryEmbed::updateGroup($xoopsGroupId, $args['groupname']);
					$xgMsg= _XG2_GROUP_UPDATED;
						if ($retcreate2) {
							/*
					 		 *  Oh no, it didn't work.
							 */
							echo (_MI_FAILED_TO_CREATE_1 . $args['groupname'] .', '. $xoopsGroupId . _MI_FAILED_TO_CREATE_2 . $retcreate2->getAsHtml());
							return;
								
						}	
			 }
			 echo($xoopsGroupName. ' - '. $xgMsg);
			 } // close ADMIN or Read
        } // close FOR
    echo ('<br><br><br>');
    echo ('Back to XoopsGallery Admisitration Module <a href=index.php>'. _XG2_HERE .'</a>');
	echo ('<br>');
}

	/**
	 * This is to export the xoopsgallery admin to gallery 2
	 * 1. Start the G2 Api
	 * 2. See if the admin user is a gallery user, if not make her one.
	 * 3. See if we are already in admin group if so skip and say "already done, dood"
	 * 3. Get user perameters.
	 * 4. Send the admin data as a user, then as an admin
	 * 5. done.
	 * 				 
	 **/
function xg2_ExportMe()
{

	
  	global $xoopsConfig, $xoopsModule, $xoopsUser, $xoopsModuleConfig, $gallery;
  	include_once(XOOPS_ROOT_PATH . '/mainfile.php');
  	require_once(dirname(__FILE__).'/../class/class.inc');
  	require_once(dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/' . $xoopsModuleConfig['xg2_embedphpfile']);
	  $activeUser=xg2Auth::xg2_getMyUid();
				if(!$xoopsUser->getVar('loginname')){
					//v2.0.13 & v2.3.0(beta1)
					$xoopsUserName = $xoopsUser->getVar('uname');
					$xoopsFullName = $xoopsUser->getVar('name');
				}else{
					//v2.2.x
					$xoopsUserName = $xoopsUser->getVar('loginname');
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

	 // Start the Gallery2 Api  aka "Start yer engines"
	 $ret = GalleryEmbed::init();

  	if ($ret) {
   		 echo($ret->getAsHtml()); // has error details..
 		 }

 		 // Am I a user? 
	$ret = GalleryEmbed::isExternalIdMapped($activeUser, 'GalleryUser');
	if ($ret && ($ret->getErrorCode() & ERROR_MISSING_OBJECT)) {				
		/*
		 *  This makes the user!
		 */
		 $query = '
			SELECT
	  			[GalleryUser::id]
			FROM
	  			[GalleryUser]
			WHERE
	  			[GalleryUser::userName] = ?
	';

	/* Check to see if we have a collision */
		list($ret, $results) = $gallery->search($query, $xoopsUserName);
	    $result = $results->nextResult();
	     
		 $retExport=GalleryEmbed::addExternalIdMapEntry($activeUser, $result[0], 'GalleryUser');
		
			if($retExport){
			
				$retcreate = GalleryEmbed::createUser($activeUser, $args);
			
			    if ($retcreate) {
					/*
				 	 *  Oh no, it didn't work.
					 */
					$retcreate2 = GalleryEmbed::updateUser($activeUser, $args);
					if ($retcreate2) {
						/*
					 	 *  Oh no, it didn't work AGAIN.
						 */
						echo _MI_FAILED_TO_CREATE_1 . $args['username'] .', '. $activeUser . _MI_FAILED_TO_CREATE_2 . $retcreate->getAsHtml();
						return false;
					} else { 
					echo(_XG2_YOUR_UPDATED);
				}	
					//return false;
				} else {
					echo(_XG2_YOUR_CREATED);
				}	
			}
	} 
		/*
		 *  This makes the user an admin!
		 *  1. fetch the admin group id
		 *  2. find g2 id# for me
		 *  2. add me g2 id# to g2 admin group.
		 */
	
			list ($ret, $adminGroupId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.adminGroup');
			if ($ret) {
				echo(_XG2_ADMIN_GROUP_FETCH_ERROR . $ret->getAsHtml());
	    		return false;
			}
			
	    /*
   		 *  if an admin group doesn't exist already, creat one NOW
	     */
	     $ret = GalleryEmbed::isExternalIdMapped('GalleryAdminGroup', 'GalleryGroup');
	    	if ($ret){
				GalleryEmbed::addExternalIdMapEntry('GalleryAdminGroup', $adminGroupId, 'GalleryGroup');
				echo (_XG2_GALLERY_ADMIN_GROUP_ADDED);
			} 
     	
		/*
		 * Am I a Gallery2 admin?
		 */
			list ($ret, $isSiteAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
    			if ($ret) {
		    		print $ret->getAsHtml();
			    	return;
    			}
    	//If I am not a gallery2 admin then make me one.
		if (!$isSiteAdmin) {
		 	$ret2 =  GalleryEmbed::addUserToGroup($activeUser, 'GalleryAdminGroup');
			if ($ret2) {
				echo(_XG2_ADD_YOU_ERROR . $ret->getAsHtml());
				return false;
			} else {
			echo($args['username'] . _XG2_ADMIN_ADDED);
			}
		} else {
			// I am a site admin no update necessary
			echo ($args['username'] . _XG2_ADMIN_ALREADY);
			}
	echo ('<br><br><br>');
    echo ('Back to XoopsGallery Admisitration Module <a href=index.php>'. _XG2_HERE .'</a>');
	echo ('<br>');
	return true;				 		

}

function xg2_UserExport() 
{
		/* 
	 * This is to export the xoops Users to gallery 2 (no roles assumed here
	 *  ie I dont know (or care) if you are an admin or not)
	 * 1. Start the G2 Api
	 * 2. See if the admin user is a gallery user, if not make her one.
	 * 3. See if we are already in admin group if so skip and say "already done, dood"
	 * 3. Get user perameters.
	 * 4. Send the admin data as a user, then as an admin
	 * 5. done.
	 * 				 
	 */
  	global $xoopsConfig, $xoopsModule, $xoopsUser, $xoopsModuleConfig, $gallery;
  	include_once(XOOPS_ROOT_PATH . '/mainfile.php');
  	require_once(dirname(__FILE__).'/../class/class.inc');
  	require_once(dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/' . $xoopsModuleConfig['xg2_embedphpfile']);
	  //$activeUser=xg2Auth::xg2_getMyUid();
	  $member_handler = &xoops_gethandler('member');
	  $thisModuleid = $xoopsModule->getVar('mid');
      $criteria = new Criteria('level', 0, '>');
      $criteria->setSort('name');
      // user list of "active" members - level greater than 0 via criteria.
      $userslist =& $member_handler->getUserList($criteria);
      // var_dump($userslist);  //remove debug info - gh
      
      foreach ($userslist as $u_id => $u_name) {
      	$xgDone = '';
		  $isMember =& xoops_gethandler('member');
		  $isUser =& $isMember->getUser($u_id);
		   
				if(!$xoopsUser->getVar('loginname')){
					//v2.0.13 & v2.3.0(beta1)
					$xoopsUserName = $isUser->getVar('uname');
					$xoopsFullName = $isUser->getVar('name');

					
				}else{
					//v2.2.x
					$xoopsUserName = $isUser->getVar('loginname');
					$xoopsFullName = $isUser->getVar('uname');
					
				};
			
				$args['fullname']  	=	$xoopsFullName;
				$args['username'] 	= 	$xoopsUserName;
				$args['hashedpassword'] =	$isUser->getVar('pass');
				$args['hashmethod'] = 	'md5';
				$args['email'] 		=	$isUser->getVar('email');
				$args['language']	=	_LANGCODE;
				// FYI, the admin's creation date is 0
				$args['creationtimestamp']	=	$isUser->getVar('user_regdate');

	      // Start the Gallery2 Api  aka "Start yer engines"
	     
		  $ret = GalleryEmbed::init();
		    if ($ret) {
		      echo($ret->getAsHtml()); // has init error details.
		  	}
		    // Am I a user? 

		   $ret = GalleryEmbed::isExternalIdMapped($u_id, 'GalleryUser');
			 			 
				if ($ret) {
				
				 $query = '
							SELECT	[GalleryUser::id]
							FROM	[GalleryUser]
							WHERE	[GalleryUser::userName] = ?
						';
					
					list($ret, $results) = $gallery->search($query, $args['username']);
	    			$result = $results->nextResult();
	    			if($result){
	    				

	    				/*
	    				 * If a result is returned an entity exists
	    				 * thus create an externalmap to xoops user
	    				 */
	    				$retExport=GalleryEmbed::addExternalIdMapEntry($u_id, $result[0], 'GalleryUser');
	     				$xgMsg= _XG2_USER_EXPORTCREATED;
	     				$xgDone = true;
     				
	     				
	    			} 
					
					if(!$xgDone){
						/*
						 * No external map created (thus not "Done") so create a new
						 * user
						 */
						$retcreate = GalleryEmbed::createUser($u_id, $args);
						$xgMsg= _XG2_USER_CREATED;
	     				$xgDone = true;
	     				
	     				if($retcreate){
	     					$xgDone = false;
	     					echo (_MI_FAILED_TO_CREATE_1 .' '. $args['username'] .', '. $u_id .' '. _MI_FAILED_TO_CREATE_2 .' '. $retcreate->getAsHtml());
	     					return;
	     				}
	    			}	
				} else {
					$retcreate2 = GalleryEmbed::updateUser($u_id, $args);
					$xgMsg= _XG2_USER_UPDATED;

						if ($retcreate2) {
							/*
					 		 *  Oh no, it didn't work.
							 */

							echo (_MI_FAILED_TO_CREATE_1 .' '. $args['username'] .', '. $u_id .' '. _MI_FAILED_TO_CREATE_2 .' '. $retcreate2->getAsHtml());
							return;
								
						}	
			 }
			 echo($args['username']. ' - '. $xgMsg);

      } // for each
    echo ('<br><br><br>');
    echo ('Back to XoopsGallery Admisitration Module <a href=index.php>'. _XG2_HERE .'</a>');
	echo ('<br>');
}
function xg2_UserRemove($xoopsUserToRemoveID) 
{
		/* 
	 * This is to remove the inactive xoops Users from gallery 2 (no roles assumed here
	 *  ie I dont know (or care) if you are an admin or not)
	 * 1. Start the G2 Api
	 * 2. See if the admin user is a gallery user, if not make her one.
	 * 3. See if we are already in admin group if so skip and say "already done, dood"
	 * 3. Get user perameters.
	 * 4. Send the admin data as a user, then as an admin
	 * 5. done.
	 * 				 
	 */
  	global $xoopsConfig, $xoopsModule, $xoopsUser, $xoopsModuleConfig, $gallery;
  	include_once(XOOPS_ROOT_PATH . '/mainfile.php');
  	require_once(dirname(__FILE__).'/../class/class.inc');
  	require_once(dirname(__FILE__) . '/../'. $xoopsModuleConfig['xg2_relativeG2Path'] .'/' . $xoopsModuleConfig['xg2_embedphpfile']);
	  //$activeUser=xg2Auth::xg2_getMyUid();
	  $member_handler = &xoops_gethandler('member');
	 // $thisModuleid = $xoopsModule->getVar('mid');  //not used? gh
      $criteria = new Criteria('level', 0, '=');
      $criteria->setSort('name');
      // user list of "active" members
      $nonuserslist =& $member_handler->getUserList($criteria);
           
     	  $ret = GalleryEmbed::init();
		    if ($ret) {
		      echo($ret->getAsHtml()); // has init error details.
		  	}
	if(!isset($xoopsUserToRemoveID)){	 
	 foreach ($nonuserslist as $u_id => $u_name) {
		  
	      $ret = GalleryEmbed::deleteUser($u_id);
	    	if ($ret) {
		      echo($ret->getAsHtml()); // has init error details.
		  	}
      } // fer each end
	 } else {
      	  $ret = GalleryEmbed::deleteUser($xoopsUserToRemoveID);
      	  if ($ret) {
		      echo($ret->getAsHtml()); // has init error details.
		  	}
      }
}
function xg2_DisplayAdminPage() {
	
global $xoopsUser;
	$xg2_dirname = str_replace(XOOPS_ROOT_PATH .'/modules/', '', dirname(dirname(__FILE__)));
	echo (_XG2_EXPORT .' '.'<b>'. $xoopsUser->getVar('uname').' '.'</b>'. _XG2_TO_GALLERY  .'<a href=index.php?op=meXport>'. _XG2_HERE .'</a>');
	echo ('<br>');
	echo ('<br>');
	echo (_XG2_EXPORT .' '. _XG2_ALL_XOOPS_USERS .' '. _XG2_TO_GALLERY  .' <a href=index.php?op=uXport>'. _XG2_HERE .'</a>');
	echo ('<br>');
	echo ('<br>');
	echo (_XG2_EXPORT .' '. _XG2_ALL_XOOPS_GROUPS .' '. _XG2_TO_GALLERY  .' <a href=index.php?op=gXport>'. _XG2_HERE .'</a>');
	echo ('<br>');
	echo ('<br>');
	echo (_XG2_REMOVE .' '. _XG2_INACTIVE_XOOPS_USERS .' '. _XG2_FROM_GALLERY  .' <a href=index.php?op=uRemove>'. _XG2_HERE .'</a>');
	echo ('<br>');
	echo "show a link to remove xoops group to gallery2";
	echo ('<br>');
	
 return;
	
}

?>
