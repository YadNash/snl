#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

// Function to generate a random AES key
void generate_aes_key(unsigned char *key, int key_length) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(key, 1, key_length, urandom);
    fclose(urandom);
}

// Function to encrypt plaintext using AES
void aes_encrypt(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_encrypt(plaintext, ciphertext, &aes_key);
}

// Function to decrypt ciphertext using AES
void aes_decrypt(unsigned char *ciphertext, unsigned char *decryptedtext, unsigned char *key) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    AES_decrypt(ciphertext, decryptedtext, &aes_key);
}

int main() {
    unsigned char plaintext[100]; // Assuming maximum plaintext length of 100 characters
    unsigned char key[AES_BLOCK_SIZE]; // AES block size is 128 bits
    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char decryptedtext[AES_BLOCK_SIZE];

    // Generate a random AES key
    generate_aes_key(key, AES_BLOCK_SIZE);

    // Prompt user to input the plaintext
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    // Remove the newline character from fgets
    plaintext[strcspn(plaintext, "\n")] = '\0';

    // Encrypt the plaintext
    aes_encrypt(plaintext, ciphertext, key);

    // Decrypt the ciphertext
    aes_decrypt(ciphertext, decryptedtext, key);

    printf("Original message: %s\n", plaintext);
    printf("Encrypted message: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted message: %s\n", decryptedtext);

    return 0;
}
//  gcc -o aes aes.c -lssl -lcrypto
//  ./aes