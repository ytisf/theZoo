<?php

	if (!BOT) exit();


	if (IS_AJAX_REQUEST) include "system.act.php";


	print "<!-- TABS begin -->
<table width=100% cellspacing=0 cellpadding=0>
<tr>
	<td nowrap class=tab_psv id='tl_1'><a href='javascript:sel(1);'>Server</a></td>
	<td nowrap class=tab_psv id='tl_2'><a href='javascript:sel(2);'>Apache</a></td>
	<td nowrap class=tab_psv id='tl_3'><a href='javascript:sel(3);'>PHP</a></td>
	<td nowrap class=tab_psv id='tl_4'><a href='javascript:sel(4);'>MySQL</a></td>
	<td class=no_tab>&nbsp;</td>
</tr>
</table>
<!-- TABS end -->



<!-- TAB 1 begin -->
<table cellspacing=0 id='el_1' class=tabcont style='display:none'>
<tr>
	<td>
		<!-- TAB 1 tabcontent begin -->\n";
	include "system.server.php";
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
	include "system.apache.php";
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
	include "system.php.php";
	print "		<!-- TAB 3 tabcontent end -->
	</td>
</tr>
</table>
<!-- TAB 3 end -->



<!-- TAB 4 begin -->
<table cellspacing=0 id='el_4' class=tabcont style='display:none'>
<tr>
	<td>
		<!-- TAB 4 tabcontent begin -->\n";
	include "system.mysql.php";
	print "		<!-- TAB 4 tabcontent end -->
	</td>
</tr>
</table>
<!-- TAB 4 end -->";

?>