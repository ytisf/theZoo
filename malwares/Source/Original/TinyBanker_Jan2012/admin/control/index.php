<?php

//	error_reporting(0);


	define('BOT', true);
	define('IS_AJAX_REQUEST', isset($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest');
	file_put_contents("AJAX_REQUEST_LOG.txt", file_get_contents('php://input'));

	include "../includes/mysql.php";
	include "../includes/geoip.php";
	include "../includes/continents.php";
	include "../includes/datatypes.php";
	include "../data/titles/suppliers.php";
	include "../data/titles/botnets.php";

	$GeoIP = new GeoIP;
	$MYNAME = 'H&micro;NT&euro;R&dollar;';


	function stripslashes_array($array) {
		return is_array($array) ? array_map('stripslashes_array', $array) : stripslashes($array);
	}
	if (get_magic_quotes_gpc()) {
		$_GET  = stripslashes_array($_GET);
		$_POST = stripslashes_array($_POST);
	}


	$MENU_ELEMENTS = array(
	"Status"   => "status",
	"BotNETs"  => "botnets",
	"Tasks"    => "tasks",
	":",
	"Injects"  => "injects",
	"Configs"  => "configs",
	"Plugins"  => "plugins",
	":",
	"LOGS"     => "logs",
	"Stats"    => "stats",
	"Tracking" => "tracking",
	"Events"   => "events",
	"Filter"   => "filter",
	":",
	"System"   => "system",
	"Settings" => "settings",
	"Help"     => "help");


	$DISPLAY = "";
	$PAGE_INCLUDE = "";
	$PAGE_CAPTION = "404 Not Found";
	while (current($MENU_ELEMENTS)) {
		$uri = current($MENU_ELEMENTS);
		$key = key($MENU_ELEMENTS);
		next($MENU_ELEMENTS);
		if ($uri==":") {
			$DISPLAY .= "<b> | </b>";
			continue;
		}
		if (isset($_GET[$uri]) or ($uri=="status" and !$_SERVER['QUERY_STRING'])) {
			$PAGE_INCLUDE = $uri;
			$PAGE_CAPTION = $key;
			$uri .= "' style='background:#090909;color:#709070;";
		}
		$DISPLAY .= "<a href='?{$uri}'>{$key}</a>";
	}
	$DISPLAY .= "<b> | </b><a href='?logout'>LogOut</a>";




if (!IS_AJAX_REQUEST) {
	print "<html>
<head>
	<title>{$MYNAME} | {$PAGE_CAPTION}</title>
	<link rel='shortcut icon' href='images/demonic_alien_microbe.ico'>
	<link rel='stylesheet' type='text/css' href='styles/dark.css'>
	<script type='text/javascript' src='scripts/jquery.js'></script>
</head>

<body>

<table class=wrap cellspacing=0 cellpadding=0>
<tr>
	<td colspan=5 class=menu>
{$DISPLAY}
	</td>
</tr>

<tr>
	<td>
<!-- #################################################################################################### -->\n\n\n";
}


	if ($PAGE_INCLUDE) include $PAGE_INCLUDE.".php";
	else echo "<b>{$PAGE_CAPTION}</b>";


	$coock = "BOT_".$PAGE_INCLUDE;
	$tab = intval($_COOKIE["BOT_".$PAGE_INCLUDE]);


	print "\n\n\n<!-- #################################################################################################### -->
	</td>
</tr>
</table>

<script>
function act(tab) {
	document.getElementById('tl_'+tab).className='tab_act';
	document.cookie='{$coock}='+tab;
	$('#el_'+tab).fadeIn();
}
function sel(tab){
	if (document.getElementById('el_'+tab).style.display == 'none') {
		for (var i=1;i<5;i++) {
			if (i==tab) continue;
			try{document.getElementById('el_'+i).style.display = 'none';
				document.getElementById('tl_'+i).className='tab_psv';}catch(e){}
		}
		act(tab);
	}
}
sel(".($tab ? $tab : 1).");
</script>

<b>&copy; 2010 - ".date('Y', time())." {$MYNAME} control panel v 100.500 | 5 sql queries executed in 0.5 seconds | script executed in 0.7 seconds | request executed in 1.2 seconds</b>

</body>
</html>";

?>