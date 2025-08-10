// Data32, data encoding and decoding for base32. (JavaScript)


function base32Encode(input) {
  const base32Chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ234567';
  let binaryString = '';
  let base32String = '';

  // Convert input string to a binary string representation
  for (let i = 0; i < input.length; i++) {
    binaryString += input.charCodeAt(i).toString(2).padStart(8, '0');
  }

  // Pad the binary string with zeros to ensure its length is a multiple of 5
  while (binaryString.length % 5 !== 0) {
    binaryString += '0';
  }

  for (let i = 0; i < binaryString.length; i += 5) {
    const fiveBitChunk = binaryString.substring(i, i + 5);
    const charIndex = parseInt(fiveBitChunk, 2);
    base32String += base32Chars[charIndex];
  }

  // Add padding characters ('=') to the end of the Base32 string
  const paddingNeeded = (8 - (base32String.length % 8)) % 8;
  for (let i = 0; i < paddingNeeded; i++) {
    base32String += '=';
  }

  return base32String;
}

/* Example usage
const dataToEncode = "Hello, Base32!";
const encodedData = base32Encode(dataToEncode);
console.log(`Original: "${dataToEncode}"`);
console.log(`Encoded: "${encodedData}"`); */

function base32Decode(input) {
  const base32Chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ234567';
  let DECODINGbinaryString = '';
  let DECODEoutput = '';

  // Remove padding characters and convert to uppercase for case-insensitivity
  input = input.replace(/=+$/, '').toUpperCase();

  // Convert each Base32 character to its 5-bit binary representation
  for (let i = 0; i < input.length; i++) {
    const char = input[i];
    const index = base32Chars.indexOf(char);

    if (index === -1) {
      // Handle invalid characters if necessary, or throw an error
      console.warn(`Invalid Base32 character: ${char}`);
      continue;
    }
    DECODINGbinaryString += index.toString(2).padStart(5, '0');
  }

  // Convert the concatenated binary string into 8-bit bytes
  for (let i = 0; i < DECODINGbinaryString.length; i += 8) {
    const byte = DECODINGbinaryString.substring(i, i + 8);
    // Only convert if a full 8-bit byte is available
    if (byte.length === 8) {
      DECODEoutput += String.fromCharCode(parseInt(byte, 2));
    }
  }

  return DECODEoutput;
}
