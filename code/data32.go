package main

import (
	"encoding/base32"
	"fmt"
	"os"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Println("Usage:")
		fmt.Println("  go run main.go encode <text_to_encode>")
		fmt.Println("  go run main.go decode <base32_string_to_decode>")
		return
	}

	operation := os.Args[1]
	data := os.Args[2]

	switch operation {
	case "encode":
		encoded := base32.StdEncoding.EncodeToString([]byte(data))
		fmt.Printf("Encoded: %s\n", encoded)
	case "decode":
		decoded, err := base32.StdEncoding.DecodeString(data)
		if err != nil {
			fmt.Printf("Error decoding: %v\n", err)
			return
		}
		fmt.Printf("Decoded: %s\n", string(decoded))
	default:
		fmt.Println("Invalid operation. Use 'encode' or 'decode'.")
	}
}
