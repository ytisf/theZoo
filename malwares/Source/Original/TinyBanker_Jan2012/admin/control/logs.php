<?php

	if (!BOT) exit();


	$LOGSTABLES = array();
	$res = mysql_query("SHOW TABLES LIKE 'logs_%'");
	while ($row = mysql_fetch_row($res)) $LOGSTABLES[] = $row[0];


	if (IS_AJAX_REQUEST) include "logs.act.php";


	print "<!-- TABS begin -->
<table width=100% cellspacing=0 cellpadding=0>
<tr>
	<td nowrap class=tab_psv id='tl_1'><a href='javascript:sel(1);'>Search</a></td>
	<td nowrap class=tab_psv id='tl_2'><a href='javascript:sel(2);'>Parser</a></td>
	<td nowrap class=tab_psv id='tl_3'><a href='javascript:sel(3);'>Patterns</a></td>
	<td class=no_tab>&nbsp;</td>
</tr>
</table>
<!-- TABS end -->



<!-- TAB 1 begin -->
<table cellspacing=0 id='el_1' class=tabcont style='display:none'>
<tr>
	<td>
		<!-- TAB 1 tabcontent begin -->\n";
	include "logs.search.php";
	print "		<!-- TAB 1 tabcontent end -->
	</td>
</tr>
</table>
<!-- TAB 1 end -->



<!-- TAB 2 begin -->
<table cellspacing=0 id='el_2' class=tabcont style='display:none'>
<tr>
	<td>
		<!-- TAB 2 tabcontent begin -->\n";
	include "logs.parser.php";
	print "		<!-- TAB 2 tabcontent end -->
	</td>
</tr>
</table>
<!-- TAB 2 end -->



<!-- TAB 3 begin -->
<table cellspacing=0 id='el_3' class=tabcont style='display:none'>
<tr>
	<td>
		<!-- TAB 3 tabcontent begin -->\n";
	include "logs.patterns.php";
	print "		<!-- TAB 3 tabcontent end -->
	</td>
</tr>
</table>
<!-- TAB 3 end -->";

?>