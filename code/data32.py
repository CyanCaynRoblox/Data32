import base64

def encode_to_base32(data_string):
  stringized_data = tostring(data_string)  
  data_bytes = stringized_data.encode('utf-8')
    encoded_bytes = base64.b32encode(data_bytes)
    return encoded_bytes.decode('utf-8')
  
def decode_from_base32(base32_string):
    base32_bytes = base32_string.encode('utf-8')
    decoded_bytes = base64.b32decode(base32_bytes)
    return decoded_bytes.decode('utf-8')

# Example for encoding: data = encode_to_base32("rock your body by black eyed peas is overrated")
# print(data)

# Example for decoding: other_data = decode_from_base32("MJZG65DIMVZCA6LPOUQGI2LEEBVHK43UEBXG65BAONSWC4TDNAQHK4BAMEQGIZLDN5SGK4RANJ2XG5BAORXSA43FMUQHO2DBOQQHI2DJOMQGS4Y=)
# print(other_data)
