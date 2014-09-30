<?php

	if (!BOT) exit();


	$time = time();

	$totalbots  = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots`;"));
	$newbots24  = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_birth`>".($time-24*60*60)));
	$newbots1   = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_birth`>".($time-1*60*60)));

	$active24 = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_last`>".($time-24*60*60)));
	$active6  = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_last`>".($time-6*60*60)));
	$active1  = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_last`>".($time-1*60*60)));

	$inactive72 = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_last`<".($time-72*60*60)));
	$inactive48 = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_last`<".($time-48*60*60)));
	$inactive24 = mysql_fetch_array(mysql_query("SELECT COUNT(*) FROM `bots` WHERE `time_last`<".($time-24*60*60)));




	print "<table cellspacing=1 cellpadding=0 class=block>
<tr>
	<td width=15% class='title'>Total BOTs:</td>
	<td width=5% class='value'>{$totalbots[0]}</td>
	<td width=15% class='title'>Active BOTs within 24h:</td>
	<td width=5% class='value'>{$active24[0]}</td>
	<td width=15% class='title'>Inactive BOTs more 72h:</td>
	<td width=5% class='value'>{$inactive72[0]}</td>
	<td width=15% class='title'>Average BOTs activity:</td>
	<td width=5% class='value'>???</td>
	<td width=15% class='title'>!!!:</td>
	<td width=5% class='value'>???</td>
</tr>
<tr>
	<td class='title'>New BOTs 24h:</td>
	<td class='value'>{$newbots24[0]}</td>
	<td class='title'>Active BOTs within 6h:</td>
	<td class='value'>{$active6[0]}</td>
	<td class='title'>Inactive BOTs more 48h:</td>
	<td class='value'>{$inactive48[0]}</td>
	<td class='title'>Average BOTs lifetime:</td>
	<td class='value'>???</td>
	<td class='title'>!!!:</td>
	<td class='value'>???</td>
</tr>
<tr>
	<td class='title'>New BOTs 1h:</td>
	<td class='value'>{$newbots1[0]}</td>
	<td class='title'>Active BOTs within 1h:</td>
	<td class='value'>{$active1[0]}</td>
	<td class='title'>Inactive BOTs more 24h:</td>
	<td class='value'>{$inactive24[0]}</td>
	<td class='title'>!!!:</td>
	<td class='value'>???</td>
	<td class='title'>!!!:</td>
	<td class='value'>???</td>
</tr>
</table>





<table cellspacing=1 cellpadding=0 class='block'>
<tr>
	<td width=11% class='title'>Win 8 x32:</td>
	<td width=4% class='value'>???</td>
	<td width=10% class='title'>Win Seven x32:</td>
	<td width=4% class='value'>???</td>
	<td width=10% class='title'>Win 2k8 x32:</td>
	<td width=4% class='value'>???</td>
	<td width=10% class='title'>Win Vista x32:</td>
	<td width=4% class='value'>???</td>
	<td width=10% class='title'>Win 2k3 x32:</td>
	<td width=4% class='value'>???</td>
	<td width=9% class='title'>Win XP x32:</td>
	<td width=4% class='value'>???</td>
	<td width=11% class='title'>Total x32:</td>
	<td width=5% class='value'>???</td>
</tr>
<tr>
	<td class='title'>Win 8 x64:</td>
	<td class='value'>???</td>
	<td class='title'>Win Seven x64:</td>
	<td class='value'>???</td>
	<td class='title'>Win 2k8 x64:</td>
	<td class='value'>???</td>
	<td class='title'>Win Vista x64:</td>
	<td class='value'>???</td>
	<td class='title'>Win 2k3 x64:</td>
	<td class='value'>???</td>
	<td class='title'>Win XP x64:</td>
	<td class='value'>???</td>
	<td class='title'>Total x64:</td>
	<td class='value'>???</td>
</tr>
</table>";

?>