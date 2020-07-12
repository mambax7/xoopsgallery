CREATE TABLE xg2_data (
  xg2_id mediumint(8) unsigned NOT NULL auto_increment,
  xg2_name varchar(100) NOT NULL default '',
  xg2_ext varchar(20) NOT NULL default '',
  xg2_type varchar(20) NOT NULL default '',
  xg2_albumdir varchar(50) NOT NULL default '',
  xg2_basedir varchar(255) NOT NULL default '',
  xg2_created int(10) unsigned NOT NULL default '0',
  xg2_comments smallint(5) unsigned NOT NULL default '0',
  PRIMARY KEY  (xg2_id)
) TYPE=MyISAM;
