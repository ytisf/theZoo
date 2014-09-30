<?php

	if (!BOT) exit();


if (isset($_POST['killproc'])) {
	foreach($_POST['kill_id'] as $id) mysql_query("KILL ".intval($id));
	exit('success');
}


if (isset($_POST['dbact'])) {
	exit(file_get_contents('php://input'));
}


	exit();

?>