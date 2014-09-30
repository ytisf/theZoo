<?php

	if (!BOT) exit();


	function GetHttpReqBrief ($data) {
		if (substr($data, 0, 4)=='GET ' || substr($data, 0, 5)=='POST ') {
			$headers = explode("\r\n", $data);

			if (substr($data, 4, 8)=="https://" || substr($data, 5, 8)=="https://" || substr($data, 4, 7)=="http://" || substr($data, 5, 7)=="http://") {
				$pieces = explode(" ", $headers[0]);
				$BRIEF = "<b>{$pieces[0]}</b> ";
				$pieces = explode("/", $pieces[1]);
				$BRIEF .= "{$pieces[0]}//<font class=highlight>{$pieces[2]}</font>/";
				array_splice($pieces, 0, 3);
				$resource = implode("/", $pieces);
				$BRIEF .= $resource;
			}
			else {
				$host = "unidentified";
				while ($header = next($headers)) {
					if (substr($header, 0, 6)=="Host: ") {
						$host = substr($header, 6);
						break;
					}
				}
				$pieces = explode(" ", $headers[0]);
				$BRIEF = "<b>{$pieces[0]}</b> https://<font class=highlight>{$host}</font>".$pieces[1];
			}
		}
		else $BRIEF = "<b>unidentified</b>";
		return $BRIEF;
	}


	function HighLight2 ($data) {
		$expl = explode("\r\n\r\n", $data);
		$headers  = $expl[0];
		$contents = $expl[1];


		$hdrs = explode("\r\n", $headers);
		$unit = explode(" ", $hdrs[0]);
		$unit[0] = "<font class=hdrslight>{$unit[0]}</font>";
		$hdrs[0] = implode(" ", $unit);
		for ($i=1; $i<count($hdrs);$i++) {
			$unit = explode(":", $hdrs[$i]);
			$unit[0]  = "<font class=hdrslight>{$unit[0]}</font>";
			$hdrs[$i] = implode(":", $unit);
		}
		$headers = implode("\r\n", $hdrs);
		$headers = str_replace("MSIE", "<font class=highlight>MSIE</font>", $headers);
		$headers = str_replace("Chrome", "<font class=highlight>Chrome</font>", $headers);
		$headers = str_replace("Firefox", "<font class=highlight>Firefox</font>", $headers);


		$vars = explode("&amp;", $contents);
		if (count($vars)>1) {
			$count = count($vars);
			for ($i=0; $i<$count;$i++) {
				if ($vars[$i]=='') {
					unset($vars[$i]);
					continue;
				}
				$unit = explode("=", $vars[$i]);
				$unit[1]  = urldecode($unit[1]);
				$vars[$i] = "<font class=varslight onclick='alert(\"{$unit[1]}\")'>{$unit[0]}=</font>".$unit[1];
			}
			$contents = implode("\n", $vars);
		}


		$data = $headers."\r\n\r\n".$contents;
		return $data;
	}

?>