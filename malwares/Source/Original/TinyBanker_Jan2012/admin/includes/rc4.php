<?php

function encrypt ($pwd, $data, $ispwdHex = 0) {
	if ($ispwdHex) $pwd = @pack('H*', $pwd); // valid input, please!

	$key[] = '';
	$box[] = '';
	$cipher = '';

	$pwd_length = strlen($pwd);
	$data_length = strlen($data);

	for ($i = 0; $i < 256; $i++) {
		$key[$i] = ord($pwd[$i % $pwd_length]);
		$box[$i] = $i;
	}
	for ($j = $i = 0; $i < 256; $i++) {
		$j = ($j + $box[$i] + $key[$i]) % 256;
		$tmp = $box[$i];
		$box[$i] = $box[$j];
		$box[$j] = $tmp;
	}
	for ($a = $j = $i = 0; $i < $data_length; $i++) {
		$a = ($a + 1) % 256;
		$j = ($j + $box[$a]) % 256;
		$tmp = $box[$a];
		$box[$a] = $box[$j];
		$box[$j] = $tmp;
		$k = $box[(($box[$a] + $box[$j]) % 256)];
		$cipher .= chr(ord($data[$i]) ^ $k);
	}
	return $cipher;
}

?>