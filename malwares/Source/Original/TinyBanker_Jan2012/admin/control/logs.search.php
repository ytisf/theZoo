<?php

	if (!BOT) exit();


	print "<!-- Search form begin -->
<div id='searchformdiv'>
<form>
<table cellspacing=1 cellpadding=0 class='block'>

	<tr>
		<td class='srchopt'>Logs IDs:</td>
		<td colspan=3><input type='text' name='logs_ids'></td>
		<td rowspan=7 width=250px class='srchbox' onclick=\"$(this).find('div').hide();$(this).find('select').fadeIn();\"><div>Geolocation</div>
			<select name='geolocation[]' multiple style='height:125px;display:none;'><optgroup label='CONTINENTS'>";
	reset($GEOIP_CONTINENT_NAMES);
	while ($val = current($GEOIP_CONTINENT_NAMES)) {
		$key = key($GEOIP_CONTINENT_NAMES);
		print "<option value=X{$key}>[{$key}] {$val}</option>";
		next($GEOIP_CONTINENT_NAMES);
	}
	print "</optgroup><optgroup label='COUNTRIES'>";
	for ($i=0; $i<count($GeoIP->GEOIP_COUNTRY_CODES); $i++) print "<option value={$GeoIP->GEOIP_COUNTRY_CODES[$i]}>[{$GeoIP->GEOIP_COUNTRY_CODES[$i]}] {$GeoIP->GEOIP_COUNTRY_NAMES[$i]}</option>";
	print "</optgroup></select>
		</td>
		<td rowspan=7 width=200px class='srchbox' onclick=\"$(this).find('div').hide();$(this).find('select').fadeIn();\"><div>Data types</div>
			<select name='datatypes[]' multiple style='height:125px;display:none;'>";
	for ($i=1; $i<count($DATA_TYPES); $i++) print "<option value={$i}>{$DATA_TYPES[$i]}</option>";
	print "</select>
		</td>
		<td rowspan=7 width=200px class='srchbox' onclick=\"$(this).find('div').hide();$(this).find('select').fadeIn();\"><div>Botnets</div>
			<select name='botnets[]' multiple style='height:125px;display:none;'>";
	reset($BOTNETS);
	while ($val = current($BOTNETS)) {
		$key = key($BOTNETS);
		print "<option value={$key}>[ {$key} ]</option>";
		next($BOTNETS);
	}
	print "</select>
		</td>
		<td rowspan=7 width=200px class='srchbox' onclick=\"$(this).find('div').hide();$(this).find('select').fadeIn();\"><div>Suppliers</div>
			<select name='suppliers[]' multiple style='height:125px;display:none;'>";
	reset($SUPPLIERS);
	while ($val = current($SUPPLIERS)) {
		$key = key($SUPPLIERS);
		print "<option value={$key}>[ {$key} ]</option>";
		next($SUPPLIERS);
	}
	print "</select>
		</td>
	</tr>

	<tr>
		<td class='srchopt'>Bots UIDs:</td>
		<td colspan=3><input type='text' name='bots_uids'></td>
	</tr>\n\n";


	$OPTIONS = '';
	rsort($LOGSTABLES);
	reset($LOGSTABLES);
	while ($val = current($LOGSTABLES)) {
		$dispval  = $val{9}.$val{10}.'.'.$val{7}.$val{8}.'.20'.$val{5}.$val{6};
		$OPTIONS .= "<option value='{$val}'>{$dispval}</option>";
		next($LOGSTABLES);
	}
	print "	<tr>
		<td class='srchopt' width=70px>From date:</td>
		<td><select name='from_date'>{$OPTIONS}</select></td>
		<td class='srchopt' width=50px>To date:</td>
		<td><select name='to_date'>{$OPTIONS}</select></td>
	</tr>
	<tr>
		<td class='srchopt'>From time:</td>
		<td><input type='text' name='from_time'></td>
		<td class='srchopt'>To time:</td>
		<td><input type='text' name='to_time'></td>
	</tr>

	<tr>
		<td class='srchopt'>IP mask:</td>
		<td colspan=3><input type='text' name='ip_mask[]' maxlength=3 class='srchnum'>.<input type='text' name='ip_mask[]' maxlength=3 class='srchnum'>.<input type='text' name='ip_mask[]' maxlength=3 class='srchnum'>.<input type='text' name='ip_mask[]' maxlength=3 class='srchnum'></td>
	</tr>

	<tr>
		<td class='srchopt'>Phrase:</td>
		<td colspan=3><input type='text' name='phrase'></td>
	</tr>

	<tr>
		<td class='srchopt'>Limit:</td>
		<td colspan=2>
			<input type='text' name='limit' value='999' maxlength=3 class='srchnum'>
		</td>
		<td>
			<input type='submit' value='Search &raquo;&raquo;&raquo;' class='srchbtn'>
		</td>
	</tr>

</table>
</form>
</div>
<!-- Search form end -->


<div id='searchresultdiv'></div>


<script>
	$('#searchformdiv form').submit(function() {
		var zis = $(this);
		$(zis).find(':submit').attr('disabled', true);
		$('#searchresultdiv').empty().html('<center><img src=\"images/loading.gif\"></center>');

		$.post('?logs', $(zis).serialize(), function(data){
			$(zis).find(':submit').attr('disabled', false);
			$('#searchresultdiv').css({'display':'none'}).empty().html(data).fadeIn();
		});

		return false;
	});
</script>\n\n\n";

?>