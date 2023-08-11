# RSA-Using-OOP
RSA Encryption and Decryption
This program demonstrates the RSA encryption and decryption process using public and private keys. It includes two classes: sender and receiver.

sender Class
The sender class is responsible for reading the message and the public key from files, encrypting the message, and encoding it into a vector.

Methods:
read_message(): Reads the message from the console input and stores it in the message variable.
get_message(): Returns the stored message.
get_public_key(): Returns the stored public key.
read_public_key(): Reads the public key from the file "shared_public_key.txt" and stores it in the public_key variable.
encrypt(int mess, int e, int n): Encrypts a given message using the provided public key values e and n.
encoder(int e, int n): Encodes the message into a vector of integers using the encrypt method.
receiver Class
The receiver class is responsible for generating the keys, sharing the public key, decrypting the encrypted message, and decoding it into a string.

Methods:
gcd(int a, int h): Calculates the greatest common divisor between two numbers.
decrypt(int c, int n, int d): Decrypts a given encrypted message using the provided values n and d.
decoder(vector<int> encoded, int n, int d): Decodes the encrypted message into a string using the decrypt method.
get_n(): Returns the stored value of n.
get_d(): Returns the stored value of d.
generate_keys_and_share_public_key(): Generates the keys, shares the public key by writing it to the file "shared_public_key.txt".
Main Function
The main function repeatedly performs the following steps:

Creates instances of the receiver and sender classes.
Generates the keys and shares the public key.
Reads the public key and the message from the appropriate files.
Encrypts the message using the public key.
Encodes the encrypted message into a vector of integers.
Decrypts the encrypted message using the private key.
Decodes the decrypted message into a string.
Writes both the encrypted and original messages to the "output.txt" file using the display_in_receiver method.
The process continues indefinitely unless terminated.
