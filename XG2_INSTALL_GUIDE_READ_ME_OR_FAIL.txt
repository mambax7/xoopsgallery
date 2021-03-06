Ok here is a little guide to help you.

1. read this install doc twice. :)


2. If you want to migrate your xg1 files to xg2 unzip the contents
   of the XoopsGallery.users.zip to your old xoopsgallery/cache/albums 
   directory.  it should extract a directory called .users.
   This file can be obtained from xoopsgallery.org.

5. When migrating... go slow.  Try 5 or 6 albums at a time. (I have had
   success with up to 1000 images at a time.  Issues have come up with movies
   they don't like to migrate)

6. Enjoy.  Please post questions to the xoopsgallery.org site.

____________________________
This is an release candidate...

Required Information

1.	Username and password to upload files to the Xoops �classes� 
	directory, aka FTP access.  This information is needed for 
	uploading/installing the smarty v2.6.10 engine and for uploading
	the XoopsGallery2 module.
	
2.	MySQL database name, username and password.  If you have the ability, create
    a new database for the images, just in case you want to delete and start over.
    When installing the gallery2 portion, use a different table prefix than you used
    xoops.  Using a new or the same database as xoops works just as well and fast.
	
3.	Access rights (hopefully with the same FTP access info above) to
	create a directory outside the webserver's directories.  For 
	example if /var/www/xoops/index.php is accessible by 
	http://www.myxoopsinstall.org/index.php - the xoops directory is 
	the root directory for your webserver so create /var/www/xg2data 
	to store the gallery data. Xg2data would be outside the webserver�s 
	direct reach.  Get it?  You will need to allow the webserver�s �group� 
	write access to this directory. (775 permissions)
	
4.	Administrative rights to the Xoops installation.  
	If you don�t, stop now PLEASE!
	
5.	Any other information I forgot. This is an Alpha 4 release




Quick
This will be a three (3) part installation process.  
The three components to install are the new smarty engine, 
the gallery 2 application, and the XoopsGallery2 module. 
 
I.  SMARTY UPDATE 
Note: Xoops v. 2.0.14 has the latest version of Smarty
      You don't need to follow Step I if you are using Xoops v.2.0.14 or later
      The smarty files (for the others of you that dont update) can be obtained from the 
      xoopsgallery.org website.

1.	Update Smarty Engine to v 2.6.10
 a.	  Download xoopsgallery2 alpha file
 b.	  Extract the downloaded file
 c.	  Upload the smarty.xoops.new directory to /class/ (the class
          in the root of the xoops install)
 d.   	  Turn off your website to outsiders in the admin section
 e.	  Rename the /class/smarty directory to /class/smarty.old
 f.	  Rename /class/smarty.xoops.new to /class/smarty
 g.	  Delete the files in the template_c directory
 h.	  Engine update complete.

II. UPLOAD and CREATE PHOTO STORAGE DIRECTORY
2.	Expand the XoopsGallery2 module in the modules area and change to a name of your choice.
	(new feature initally it is xg2.1 but you can rename it to anything you like, 
	except pre-existing names, duh)
 a.	  This is done like every other installed module (dont initalize yet)
 b.	  Module in place. Time to initialize components... but...
 
3.	Prior to initializing Gallery2 create a directory for the gallery data.
 a.	  It is highly recommended that the directory be *outside* the website root
 b.	  Directory location example (*nix/*bsd):  
	   i.	/server/html/  <-- server root
	   ii.	/server/xg2data  <-- suggested location for gallery data
	   iii. Can be anywhere you want, really!
 c.	  Make the data storage directory accessible by the web server group
 d.	  Example (*nix/*bsd):  
	   i.	 Web server group is called 'apache'
	   ii.	 Your name is 'user'
	   iii. chown -R user:apache /server/xg2data
	   iv.	 chmod 774 /server/xg2data/*
 e.	  Gallery2 data directory is setup

III. INSTALL GALLERY 2
4.	Initialize Gallery2.
 a.	  Go to www.yourdomain.com/modules/yourgalleryname/engine/install:  
 b.	  Follow the instructions!
 c.	  You will need to upload an authorization text file to the gallery2 (aka engine) directory
	   i.	/server/path/to/html/modules/yourgalleryname/engine
 d.   You will need to make the empty engine/config.php file writable by the webserver.
 	   i.  change permissions to 777 for config.php or at least 666 for write ability.
 e.	  If you are not using the existing Xoops database, you will need to have one ready prior to the Gallery2 initialization
    	   i. you will need hostname (localhost if on same server), database name, user access name and password.
 e.	  Follow the Gallery2 install instructions, they work!
     	   i. the files are correct to version 2.1 RC2a but you may see 18 "issues".
 f.	  Gallery 2 is installed.

IV. INSTALL XoopsGallery MODULE
5.	Initialize XoopsGallery2 module
 a.	  Like any Xoops module (If you dont know, you aren't ready for this alpha)
      i. go to administration section and initilize the module
      ii. change the prefferences to fit your server settings (My guesses should be correct, *should*)
      iii. create at least the main menu block to show up on the gallery page.
      iv.  go to the admin menu of the gallery module and click on the Export me link
      v. done.
******************************************************************************************
*Updated Directions By Nathan "BadCase" Fluet http://badcase.net August 16, 2009         *
*                                                                                        *
*If you followed all of the above directions and you still see a blank page or if your   *
*debugging is on and you see a error with getvar() in xg2Blocks.php or class.inc:        *
*open "modules/xg2.1/blocks/xg2Blocks.php" find the code below                           *
******************************************************************************************
	if (empty($xoopsModule) || $xoopsModule->getVar('dirname') != $xg2_dirname) {	
		$module_handler =& xoops_gethandler('module');
		$module =& $module_handler->getByDirname($xg2_dirname);
		$config_handler =& xoops_gethandler('config');
		$config =& $config_handler->getConfigsByCat(0,$module->getVar('mid'));
	} else {
		$module =& $xoopsModule;
		$config =& $xoopsModuleConfig;
	}
******************************************************************************************
*replace that section of code with                                                       *
******************************************************************************************
		$module =& $xoopsModule;
		$config =& $xoopsModuleConfig;
******************************************************************************************
*save and close "modules/xg2.1/blocks/xg2Blocks.php" now you need to open                *
*"modules/xg2.1/class/class.inc" and again search for the code below                     *
******************************************************************************************
	if (empty($xoopsModule) || $xoopsModule->getVar('dirname') != $xg2_dirname) {	
		$module_handler =& xoops_gethandler('module');
		$module =& $module_handler->getByDirname($xg2_dirname);
		$config_handler =& xoops_gethandler('config');
		$config =& $config_handler->getConfigsByCat(0,$module->getVar('mid'));
	} else {
		$module =& $xoopsModule;
		$config =& $xoopsModuleConfig;
	}
******************************************************************************************
*and replace that section of code with                                                   *
******************************************************************************************
		$module =& $xoopsModule;
		$config =& $xoopsModuleConfig;
******************************************************************************************
*save and close "modules/xg2.1/class/class.inc"                                          *
*Installation is now complete                                                            *
*                                                                                        *
*NOTE: if you dont feel like trying to modify the code yourself you can try using the    *
*files in the "Updated_Files" directory of this archive, but i would back up your        *
*originals to be safe.                                                                   *
******************************************************************************************

6.	Go to the XoopsGallery2 module and see if you can admin the gallery.
 a.   I suggest useing the xoops theme, not perfect but works for me.  Also. edit the gallery2 xoops theme to suit your needs.
 b.	  If so then you have the option of changing the /module/yourgalleryname/engine/config.php file to be a embed only install
 c.	  This is recommended after everything works the way you want.
 d.   If something doesnt work correctly, you can login to gallery2 directly (if you didn't follow b above)
 	  i.	http://youweb.com/modules/yourgalleryname/engine

9.	Done. Yea!

Got it?  Good!  Works?