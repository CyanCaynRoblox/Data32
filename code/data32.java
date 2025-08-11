public class Base32Codec {

    private static final String BASE32_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    public static String encodeBase32(byte[] data) {
        StringBuilder binaryString = new StringBuilder();
        for (byte b : data) {
            
            binaryString.append(String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0'));
        }

        int paddingBits = 5 - (binaryString.length() % 5);
        if (paddingBits != 5) { 
            binaryString.append("0".repeat(paddingBits));
        }

        StringBuilder encoded = new StringBuilder();
        for (int i = 0; i < binaryString.length(); i += 5) {
            String fiveBits = binaryString.substring(i, i + 5);
            int index = Integer.parseInt(fiveBits, 2);
            encoded.append(BASE32_ALPHABET.charAt(index));
        }

        
        while (encoded.length() % 8 != 0) {
            encoded.append('=');
        }

        return encoded.toString();
    }

    
    public static byte[] decodeBase32(String data) {
        
        data = data.replace("=", "");

        StringBuilder binaryString = new StringBuilder();
        for (char c : data.toCharArray()) {
            int index = BASE32_ALPHABET.indexOf(c);
            if (index == -1) {
                throw new IllegalArgumentException("Invalid Base32 character: " + c);
            }
           
            binaryString.append(String.format("%5s", Integer.toBinaryString(index)).replace(' ', '0'));
        }

        
        int paddingBits = binaryString.length() % 8;
        if (paddingBits != 0) {
            binaryString.setLength(binaryString.length() - paddingBits);
        }

        byte[] decoded = new byte[binaryString.length() / 8];
        for (int i = 0; i < binaryString.length(); i += 8) {
            String eightBits = binaryString.substring(i, i + 8);
            decoded[i / 8] = (byte) Integer.parseInt(eightBits, 2);
        }

        return decoded;
    }

    public static void main(String[] args) {
        String originalText = "Hello, Base32!";
        byte[] originalBytes = originalText.getBytes();
    /*Examples (REMOVE IF NOT WANTED)
        // Encode
        String encodedText = encodeBase32(originalBytes);
        System.out.println("Original Text: " + originalText);
        System.out.println("Encoded Base32: " + encodedText);

        // Decode
        byte[] decodedBytes = decodeBase32(encodedText);
        String decodedText = new String(decodedBytes);
        System.out.println("Decoded Text: " + decodedText); */
    }
}
