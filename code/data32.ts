// MAKE SURE YOU HAVE hi-base32 INSTALLED FOR TYPESCRIPT!!
import * as base32 from 'hi-base32';

export function DATA32encode(input: string): string {
  return base32.encode(input);
}

export function DATA32decode(encodedString: string): string {
  return base32.decode(encodedString);
}

/* Example Usage:
const originalData = "Hello, TypeScript!";
const encodedData = DATA32encode(originalData);
console.log(`Original Data: ${originalData}`);
console.log(`Encoded Data: ${encodedData}`);

const decodedData = DATA32decode(encodedData);
console.log(`Decoded Data: ${decodedData}`); */
