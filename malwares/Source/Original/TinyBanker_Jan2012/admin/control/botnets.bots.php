<?php

	if (!BOT) exit();



	print "<table cellspacing=1 cellpadding=0 class=block>
<tr class=bothdr>
	<td width=15%>UID</td>
	<td width=4%>OS</td>
	<td width=10%>[ISO] Country</td>
	<td width=10%>IP</td>
	<td width=10%>Time</td>
	<td width=10%>Botnet</td>
	<td width=10%>Supplier (sub)</td>
	<td width=25%>Comment</td>
	<td width=6%>Control</td>
</tr>\n";


	$result  = mysql_query("SELECT * FROM `bots` LIMIT 50;") or die("Query failed : " . mysql_error());
	while ($row = mysql_fetch_array($result)) {
		print "<tr class=botstr>
	<td class=botleft><div style='width:180px;'>{$row['bot_uid']}</div></td>
	<td>{$row['bot_os']}</td>
	<td class=botleft><div style='width:119px;'>[{$row['bot_country']}] {$GeoIP->GEOIP_COUNTRY_NAMES[$GeoIP->GEOIP_COUNTRY_CODE_TO_NUMBER[$row['bot_country']]]}</div></td>
	<td>{$row['bot_ip']}</td>
	<td>".date("d/m/Y - H:i:s", $row['time_last'])."</td>
	<td><div style='width:119px;'>[ {$row['bot_net']} ]</div></td>
	<td><div style='width:119px;'>[ {$row['bot_supp']} ] ({$row['supp_sub']})</div></td>
	<td class=botleft><div style='width:303px;'>{$row['comment']}</div></td>
	<td>000</td>
</tr>\n";
	}




	print "</table>


<script>
</script>\n\n\n";

?>