<?php
/*
 * Created on Feb 18, 2006
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
   $host  = $_SERVER['HTTP_HOST'];
   $page = $_SERVER['PHP_SELF'];
   $address = "http://$host$page";
   echo $host;
   echo '<br />';
   echo $page;
   echo '<br />';
   echo $address;
   echo '<br />';
   echo dirname($address);
   echo '<br />';
   echo dirname(dirname($address));
   echo '<br />';
   $address2 = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'];
   echo dirname(dirname($address2));
   echo '<br />';
   echo dirname(dirname('http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF']));
   $defaultURI = dirname(dirname('http://'. $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'])) . '/index.php';
   echo '<br />';
   echo '<br />';
   echo '<br />';
   echo $defaultURI;
?>
