<?php

	if (!BOT) exit();


	if (IS_AJAX_REQUEST) include "tasks.act.php";


	print "<!-- TABS begin -->
<table width=100% cellspacing=0 cellpadding=0>
<tr>
	<td nowrap class=tab_psv id='tl_1'><a href='javascript:sel(1);'>Update</a></td>
	<td nowrap class=tab_psv id='tl_2'><a href='javascript:sel(2);'>tasks2</a></td>
	<td nowrap class=tab_psv id='tl_3'><a href='javascript:sel(3);'>tasks3</a></td>
	<td class=no_tab>&nbsp;</td>
</tr>
</table>
<!-- TABS end -->



<!-- TAB 1 begin -->
<table cellspacing=0 id='el_1' class=tabcont style='display:none'>
<tr>
	<td>
		<!-- TAB 1 tabcontent begin -->\n";
	include "tasks.update.php";
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
	include "tasks.tasks2.php";
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
	include "tasks.tasks3.php";
	print "		<!-- TAB 3 tabcontent end -->
	</td>
</tr>
</table>
<!-- TAB 3 end -->";

?>