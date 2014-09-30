<?php

	if (!BOT) exit();


	print "<table id='botnets' cellspacing=1 cellpadding=0 class='block'>
<tr class='bothdr'>
	<td width=15%>BotNET</td>
	<td width=15%>Password</td>
	<td width=10%>Bots</td>
	<td width=60%>Comment</td>
</tr>\n\n";


	reset($BOTNETS);
	while ($val = current($BOTNETS)) {
		$key = key($BOTNETS);
		print "<tr class='botstr'>
	<td align=left>[ <b>{$key}</b> ]</td>
	<td>{$val['password']}</td>
	<td>200000</td>
	<td>{$val['comment']}</td>
</tr>\n";
		next($BOTNETS);
	}


	print "</table>


<form id='newbotnet'>
<table cellspacing=1 cellpadding=0 class='block'>
	<tr>
		<td width=15%><input type='text' name='botnet' maxlength=12 id='botnet'></td>
		<td width=15%><input type='text' name='passwd' maxlength=16 id='passwd'></td>
		<td width=60%><input type='text' name='comment' maxlength=128 id='comment'></td>
		<td width=10%><input type='submit' value='Add new botnet' class='srchbtn'></td>
	</tr>
</table>
</form>


<script>
	$('#newbotnet').submit(function() {
		var frm = $(this);
		if ($(frm).find('#botnet').val() == '') { alert('Botnet name is not specified'); return false; }
		if ($(frm).find('#passwd').val() == '') { alert('Botnet password is not specified'); return false; }
		$(frm).find(':submit').attr('disabled', true);
		$.post('?botnets', $(frm).serialize(), function(data) {
			if (data == 'success') $('#botnets').append('<tr class=\'botstr\'><td align=left>[ <b>'+$(frm).find('#botnet').val()+'</b> ]</td><td>'+$(frm).find('#passwd').val()+'</td><td>200000</td><td>'+$(frm).find('#comment').val()+'</td></tr>');
			else alert(data);
			$(frm).find(':submit').attr('disabled', false);
		});
		return false;
	});
</script>\n\n\n";

?>