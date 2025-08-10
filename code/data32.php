<?php

function base32_encode($input) {
    $alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ234567';
    $output = '';
    $buffer = 0;
    $bufferLength = 0;

    foreach (str_split($input) as $char) {
        $buffer = ($buffer << 8) | ord($char);
        $bufferLength += 8;

        while ($bufferLength >= 5) {
            $output .= $alphabet[($buffer >> ($bufferLength - 5)) & 31];
            $bufferLength -= 5;
        }
    }

    if ($bufferLength > 0) {
        $output .= $alphabet[($buffer << (5 - $bufferLength)) & 31];
    }

    // Add padding if necessary
    $padding = '';
    $remainder = strlen($output) % 8;
    if ($remainder > 0) {
        $padding = str_repeat('=', 8 - $remainder);
    }

    return $output . $padding;
}

/* Example usage:
$data_to_encode = "Hello World!";
$encoded_data = base32_encode($data_to_encode);
echo "Original: " . $data_to_encode . PHP_EOL;
echo "Encoded (Base32): " . $encoded_data . PHP_EOL;
*/

function base32_decode($input) {
    $alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ234567';
    $input = rtrim($input, '='); // Remove padding characters
    $input = strtoupper($input); // Convert to uppercase for case-insensitivity

    $output = '';
    $buffer = 0;
    $bufferLength = 0;

    foreach (str_split($input) as $char) {
        $char_value = strpos($alphabet, $char);
        if ($char_value === false) {
            // Invalid Base32 character
            return false; 
        }

        $buffer = ($buffer << 5) | $char_value;
        $bufferLength += 5;

        if ($bufferLength >= 8) {
            $bufferLength -= 8;
            $output .= chr(($buffer >> $bufferLength) & 0xFF);
        }
    }

    return $output;
}

/* Example usage:
$data_to_decode = "JBSWY3DPEBLW64TMMQQQ====";
$decoded_data = base32_decode($data_to_decode);

if ($decoded_data !== false) {
    echo "Encoded (Base32): " . $data_to_decode . PHP_EOL;
    echo "Decoded: " . $decoded_data . PHP_EOL;
} else {
    echo "Error: Invalid Base32 input." . PHP_EOL;
} */

?>
