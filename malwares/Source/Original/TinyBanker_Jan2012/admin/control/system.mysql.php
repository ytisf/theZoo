<?php

	if (!BOT) exit();





	$result = mysql_query("SHOW TABLE STATUS");
	print "<form id='dbact'>
<table cellspacing=1 cellpadding=0 class='block'>
	<tr class='bothdr'>
		<td></td>
		<td>Name</td>
		<td>Rows</td>
		<td>Data Length</td>
		<td>Index Length</td>
		<td>Trash</td>
	</tr>";

	while($row = mysql_fetch_array($result)){
		print "	<tr class='botstr'>
		<td width=14px><input type='checkbox' name='manage_name[]' value='{$row['Name']}'></td>
		<td>{$row['Name']}</td>
		<td>{$row['Rows']}</td>
		<td>".round($row['Data_length']/1024/1024, 2)." MB / ".round($row['Max_data_length']/1024/1024/1024, 2)." GB</td>
		<td>".round($row['Index_length']/1024/1024, 2)." MB</td>
		<td>".round($row['Data_free']/1024/1024, 2)." MB</td>
	</tr>";
	}

	print "</table>
<select name='action' class='button'>
<option value='optimize'>Optimize</option><option value='truncate'>Truncate</option><option value='drop'>Drop</option>
</select><input type='submit' class='button' value='Go'>
</form>


<script>
	$('#dbact').submit(function() {
		var frm = $(this);
		var req = $(frm).serialize();
		if (req == '') { alert('Select something first'); return false; }
		$(frm).find(':submit').attr('disabled', true);
		$.post('?system', 'dbact=&' + req, function(data) {
			alert(data);
			$(frm).find(':submit').attr('disabled', false);
		});
		return false;
	});
</script>";






	$result = mysql_query("SHOW PROCESSLIST");
	print "<form id='killproc'>
<table cellspacing=1 cellpadding=0 class='block'>
	<tr class='bothdr'>
		<td></td>
		<td>ID</td>
		<td>User</td>
		<td>Host</td>
		<td>DB</td>
		<td>Command</td>
		<td>Time</td>
		<td>State</td>
		<td>Info</td>
	</tr>\n\n";


	while($row = mysql_fetch_array($result)){
		print "	<tr class='botstr'>
		<td width=14px><input type='checkbox' name='kill_id[]' value='$row[Id]'></td>
		<td>$row[Id]</td>
		<td>$row[User]</td>
		<td>$row[Host]</td>
		<td>$row[db]</td>
		<td>$row[Command]</td>
		<td>".date('H:i:s',$row['Time'])."</td>
		<td>$row[State]</td>
		<td>$row[Info]</td>
	</tr>";
	};
	print "</table>
<input type='submit' class='button' value='Kill Threads'>
</form>


<script>
	$('#killproc').submit(function() {
		var frm = $(this);
		var req = $(frm).serialize();
		if (req == '') { alert('Select something first'); return false; }
		$(frm).find(':submit').attr('disabled', true);
		$.post('?system', 'killproc=&' + req, function(data) {
			if (data == 'success') $(frm).find('input:checked').parent().parent().remove();
			else alert(data);
			$(frm).find(':submit').attr('disabled', false);
		});
		return false;
	});
</script>";


?>