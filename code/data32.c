#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* base32_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

// Function to encode data into Base32
char* base32_encode(const char* input) {
    size_t input_len = strlen(input);
    size_t output_len = (input_len * 8 + 4) / 5;
    size_t padded_len = (output_len + 7) / 8 * 8;
    char* output = (char*)malloc(padded_len + 1);

    int bits_left = 0;
    int current_byte = 0;
    int output_index = 0;

    for (size_t i = 0; i < input_len; ++i) {
        current_byte = (current_byte << 8) | (unsigned char)input[i];
        bits_left += 8;

        while (bits_left >= 5) {
            output[output_index++] = base32_alphabet[(current_byte >> (bits_left - 5)) & 0x1F];
            bits_left -= 5;
        }
    }

    if (bits_left > 0) {
        output[output_index++] = base32_alphabet[(current_byte << (5 - bits_left)) & 0x1F];
    }

    while (output_index < padded_len) {
        output[output_index++] = '=';
    }

    output[padded_len] = '\0';
    return output;
}

// Function to decode Base32 data
char* base32_decode(const char* input) {
    size_t input_len = strlen(input);
    int output_len_estimate = (input_len * 5) / 8;
    char* output = (char*)malloc(output_len_estimate + 1);
    int output_index = 0;

    int bits_left = 0;
    int current_bits = 0;

    for (size_t i = 0; i < input_len; ++i) {
        char c = input[i];

        if (c == '=') {
            break;
        }

        int value = -1;
        for (int j = 0; j < 32; ++j) {
            if (base32_alphabet[j] == c) {
                value = j;
                break;
            }
        }
        
        if (value == -1) {
            free(output);
            return NULL; // Invalid character
        }

        current_bits = (current_bits << 5) | value;
        bits_left += 5;

        if (bits_left >= 8) {
            output[output_index++] = (char)((current_bits >> (bits_left - 8)) & 0xFF);
            bits_left -= 8;
        }
    }

    output[output_index] = '\0';
    return output;
}

int main() {
    const char* plain_text = "Hello, World!";
    
    char* encoded_text = base32_encode(plain_text);
    if (encoded_text) {
        printf("Original Text: %s\n", plain_text);
        printf("Encoded Text: %s\n", encoded_text);
    
        char* decoded_text = base32_decode(encoded_text);
        if (decoded_text) {
            printf("Decoded Text: %s\n", decoded_text);
            free(decoded_text);
        } else {
            printf("Decoding failed.\n");
        }
        
        free(encoded_text);
    } else {
        printf("Encoding failed.\n");
    }
    
    return 0;
}
