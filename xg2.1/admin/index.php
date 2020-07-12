<?php
/*
 * admin/index.php edited on Nov 14, 2005
 *
 * GNU released
 * 
 */
require_once(dirname(__FILE__) . '/../../../mainfile.php');
include '../../../include/cp_header.php';

include_once(dirname(__FILE__) . '/../includes/functions.inc');
include_once(dirname(__FILE__) . '/../class/class.inc');

if ( !empty($_REQUEST['op']) ) {
	$op = $_REQUEST['op'];
}

switch ($op) {
		
		case "meXport" :
			xoops_cp_header();
			xg2_ExportMe();
			xoops_cp_footer();
			break;
		case "uXport" :
			xoops_cp_header();
			xg2_UserExport();
			xoops_cp_footer();
			break;
	
		case "gXport" :
			xoops_cp_header();
			xg2_ExportGroups();
			xoops_cp_footer();
			break;
			
		case "removeUser" :
			xoops_cp_header();
			xg2_RemoveUser();
			xoops_cp_footer();
			break;

		case "removeGroup" :
			xoops_cp_header();
			xg2_RemoveGroup();
			xoops_cp_footer();
			break;
		
		default :
			xoops_cp_header();
			xg2_DisplayAdminPage();
			xg2_listXoopsUsers();
			xg2_listXoopsInActiveUsers();
			xg2_listXoopsGroups();
			xoops_cp_footer();
			break;
	}

?>
