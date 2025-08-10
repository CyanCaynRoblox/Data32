#include <iostream>
#include <string>
#include <vector>
#include <map>

// Function to encode a string to Base32, now named data32_encode
std::string data32_encode(const std::string& input) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    std::string encoded_string;
    int bits_left = 0;
    int current_byte = 0;

    for (char c : input) {
        current_byte = (current_byte << 8) | static_cast<unsigned char>(c);
        bits_left += 8;

        while (bits_left >= 5) {
            encoded_string += alphabet[(current_byte >> (bits_left - 5)) & 0x1F];
            bits_left -= 5;
        }
    }

    if (bits_left > 0) {
        encoded_string += alphabet[(current_byte << (5 - bits_left)) & 0x1F];
    }

    // Add padding if necessary (RFC 4648)
    while (encoded_string.length() % 8 != 0) {
        encoded_string += '=';
    }

    return encoded_string;
}

// Function to decode a Base32 string, now named data32_decode
std::string data32_decode(const std::string& input) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    std::map<char, int> char_to_val;
    for (int i = 0; i < alphabet.length(); ++i) {
        char_to_val[alphabet[i]] = i;
    }

    std::string decoded_string;
    int bits_left = 0;
    int current_bits = 0;

    for (char c : input) {
        if (c == '=') { // Padding character
            break;
        }

        if (char_to_val.count(c) == 0) {
            // Invalid Base32 character
            return "";
        }

        current_bits = (current_bits << 5) | char_to_val[c];
        bits_left += 5;

        if (bits_left >= 8) {
            decoded_string += static_cast<char>((current_bits >> (bits_left - 8)) & 0xFF);
            bits_left -= 8;
        }
    }
    return decoded_string;
}

/* EXAMPLE: int main() {
    std::string plain_text = "Hello, World!";
    
    encoding
    std::string encoded_text = data32_encode(plain_text);
    std::cout << "Original Text: " << plain_text << std::endl;
    std::cout << "Encoded Text: " << encoded_text << std::endl;
    
    decoding
    std::string decoded_text = data32_decode(encoded_text);
    std::cout << "Decoded Text: " << decoded_text << std::endl;
    
    return 0;
} */
