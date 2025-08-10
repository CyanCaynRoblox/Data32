using System;
using System.Text;

public static class Base32
{
    private const string Base32Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";


    public static string Encode(byte[] data)
    {
        if (data == null || data.Length == 0)
        {
            return string.Empty;
        }

        StringBuilder result = new StringBuilder();
        int bitsInBuffer = 0;
        int buffer = 0;

        foreach (byte b in data)
        {
            buffer = (buffer << 8) | b;
            bitsInBuffer += 8;

            while (bitsInBuffer >= 5)
            {
                bitsInBuffer -= 5;
                result.Append(Base32Alphabet[(buffer >> bitsInBuffer) & 0x1F]);
            }
        }

        if (bitsInBuffer > 0)
        {
            result.Append(Base32Alphabet[(buffer << (5 - bitsInBuffer)) & 0x1F]);
        }

        // Add padding if necessary (RFC 3548 compliant, but often omitted in practice)
        while (result.Length % 8 != 0)
        {
            result.Append('=');
        }

        return result.ToString();
    }

    public static byte[] Decode(string base32String)
    {
        if (string.IsNullOrEmpty(base32String))
        {
            return new byte[0];
        }

        base32String = base32String.TrimEnd('='); // Remove padding characters

        int bitsInBuffer = 0;
        int buffer = 0;
        byte[] decodedBytes = new byte[base32String.Length * 5 / 8]; // Max possible size
        int byteIndex = 0;

        foreach (char c in base32String)
        {
            int charValue = Base32Alphabet.IndexOf(char.ToUpper(c));
            if (charValue == -1)
            {
                throw new ArgumentException("Invalid Base32 character encountered.");
            }

            buffer = (buffer << 5) | charValue;
            bitsInBuffer += 5;

            if (bitsInBuffer >= 8)
            {
                bitsInBuffer -= 8;
                decodedBytes[byteIndex++] = (byte)(buffer >> bitsInBuffer);
            }
        }

        Array.Resize(ref decodedBytes, byteIndex); // Resize to actual length
        return decodedBytes;
    }
}
