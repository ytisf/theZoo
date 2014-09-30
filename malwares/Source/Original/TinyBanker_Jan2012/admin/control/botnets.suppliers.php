<?php

	if (!BOT) exit();


	print "<table id='suppliers' cellspacing=1 cellpadding=0 class='block'>
<tr class='bothdr'>
	<td width=15%>Supplier</td>
	<td width=10%>Bots</td>
	<td width=75%>Comment</td>
</tr>\n\n";



	reset($SUPPLIERS);
	while ($val = current($SUPPLIERS)) {
		$key = key($SUPPLIERS);
		print "<tr class='botstr'>
	<td align=left>[ <b>{$key}</b> ]</td>
	<td>200000</td>
	<td>{$val['comment']}</td>
</tr>\n";
		next($SUPPLIERS);
	}



	print "</table>


<form id='newsupplier'>
<table cellspacing=1 cellpadding=0 class='block'>
	<tr>
		<td width=15%><input type='text' name='supplier' maxlength=12 id='supplier'></td>
		<td width=75%><input type='text' name='comment' maxlength=128 id='comment'></td>
		<td width=10%><input type='submit' value='Add new supplier' class='srchbtn'></td>
	</tr>
</table>
</form>



<script>
	$('#newsupplier').submit(function() {
		var frm = $(this);
		if ($(frm).find('#supplier').val() == '') { alert('Supplier name is not specified'); return false; }
		$(frm).find(':submit').attr('disabled', true);
		$.post('?botnets', $(frm).serialize(), function(data) {
			if (data == 'success') $('#suppliers').append('<tr class=\'botstr\'><td align=left>[ <b>'+$(frm).find('#supplier').val()+'</b> ]</td><td>200000</td><td>'+$(frm).find('#comment').val()+'</td></tr>');
			else alert(data);
			$(frm).find(':submit').attr('disabled', false);
		});
		return false;
	});
</script>\n\n\n";

?>