<?php
/*
 *  index.php 
 */
define('_MI_CONFIGURATION_NOT_DONE','the parameters for xoopsgallery2 have not been completed. <br> Please complete before tring again. <br> thanks.');
define('_MI_EMBED_PHP_FILE','embed.php');
define('_XG2_MI_EMBED_FILEDSC','The Gallery2 Embed file name \'embed.php\'');
define('_MI_FAILED_TO_CREATE_1','Failed to create XG2 user with extId [');
define('_MI_FAILED_TO_CREATE_2',']. Here is the error message from XG2: <br />');
define('_XG2_MI_FAILED', 'XG2 did not return a success status. Here is the error message from G2: <br />');
define('_MI_ISDONE_FAILED', 'isDone is not defined, something very bad must have happened.');
/*
 *  xoops_version.php
 */
define('_XG2_MI_NAME','XoopsGallery2');
define('_XG2_MI_DESCRIPTION',"A Xoops port of Gallery 2 (v 2.1.1a) See http://Gallery.sf.net ");
define('_XG2_MI_CREDITS','Maintained by Glen Starrett, Chris Thornton and others (see the README_XOOPS for credits)');
define('_XG2_MI_BLOCK_SIDEBAR','Gallery Menu');
define('_XG2_MI_BLOCK_SIDEBAR_DES','Gallery Menu Description');
define('_XG2_MI_BLOCK_IMAGE','Gallery Block');
define('_XG2_MI_BLOCK_IMAGE_DES','Display a variuos types of images in a block');


define('_XG2_MI_INDEX_DESCRIPTION','Gallery Index Templay Description');

define('_XG2_MI_BLOCK_RANDOM','Random Images');
define('_XG2_MI_BLOCK_RANDOM_DES','Random Images Block Description');

define('_XG2_MI_EMBED_URI','Embed URI');
define('_XG2_MI_EMBED_URIDSC','This is the URI that will be used to link xoops and gallery2.  We interface using the index.php file.  The default should work fine, if not fix it to link to xg2/index.php file.  Remember if you renamed xg2 to something else, make sure it is changed here too.');
define('_XG2_MI_RELATIVE_G2_PATH','Relative Path');
define('_XG2_MI_RELATIVE_G2_PATHDSC','The name of the gallery2 directory.  XG2 names it engine, but you can change that too.');
define('_XG2_MI_LOGIN_REDIRECT','Login Redirect');
define('_XG2_MI_LOGIN_REDIRECTDSC','Where to send Login Redirects if the user connection expires or does not have permission to access.');
define('_XG2_MI_ACTIVE_USERID','Active UserID');
define('_XG2_MI_ACTIVE_USERIDDSC','Hmmm don\'t know.  It is required but is not used.  Use the default, this may go away in the future');
define('_XG2_MI_BASE_URI','URI to the Gallery 2 installation');
define('_XG2_MI_BASE_URIDSC','This is the URI to the gallery 2 installation.  Example: http://www.example.com/modules/xg2/engine/  If you change the gallery2 install directory from engine to another name, please change here too.');
define('_XG2_MI_COOKIE_PATH','Cookie Path');
define('_XG2_MI_COOKIE_PATHDSC','Path to cookie generator application \'xoops\'.  Default should work fine.');
define('_XG2_MI_SHOW_SIDEBAR','Gallery2 sidebar');
define('_XG2_MI_SHOW_SIDEBARDSC','Gallery2 has its own sidebar, use it (YES) if you dont want a block, else NO (No is the recomended setting)');
define('_XG2_MI_CONFIG_DONE','Configuration Complete?');
define('_XG2_MI_CONFIG_DONEDSC','Well, is the configuration complete?');
define('_XG2_MI_ADMIN_INDEX', 'Admin Index');
define('_XG2_MI_ADMIN_ADDUSER', 'Add User');
define('_XG2_MI_ADMIN_ADDGROUP', 'Add Group');
define('_XG2_MI_ADMIN_REMOVEUSER', 'Remove User');
define('_XG2_MI_ADMIN_REMOVEGROUP', 'Remove Group');
?>
