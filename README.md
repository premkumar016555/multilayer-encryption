# Multi-Layer Encryption and Decryption

This project provides a multi-layer encryption and decryption tool implemented in C++. It uses a combination of ciphers to provide a secure way of encrypting and decrypting data.

## Features

*   **Multi-Layer Encryption:** Uses a combination of Substitution, Caesar, and Rail Fence ciphers.
*   **Key-Based Encryption:** The encryption and decryption processes are based on a user-provided key.
*   **Random Padding:** Adds a layer of random padding to obscure the plaintext length.
*   **Brute-Force Decryption Tool:** Includes a tool to try and decrypt a message by trying a number of rounds from 0 to 100.

## How to Compile and Run

To compile the code, you will need a C++ compiler (like G++). You can compile each file separately.

**Encryption:**

```bash
g++ encryption.cpp -o encrypt
./encrypt
```

**Decryption:**

```bash
g++ decryption.cpp -o decrypt
./decrypt
```

**All-Round Decryption:**

```bash
g++ alldecryption.cpp -o alldecrypt
./alldecrypt
```

## Encryption Process

The encryption process consists of the following steps:

1.  **Key Processing:** The user-provided key is converted into a series of numbers that are used as shifts in the Caesar cipher.
2.  **Substitution Cipher:** The plaintext is first encrypted using a predefined substitution map.
3.  **Multi-Round Encryption:** The result of the substitution cipher is then passed through a series of encryption rounds. Each round consists of:
    *   **Caesar Cipher:** The text is encrypted using a Caesar cipher with a shift derived from the key.
    *   **Substitution Cipher:** The result is encrypted again with the same substitution map.
    *   **Rail Fence Cipher:** The result is then encrypted using a Rail Fence cipher.
4.  **Padding:** Finally, random padding is added to the encrypted text to obscure its length.

## Decryption Process

The decryption process reverses the encryption process:

1.  **Key Processing:** The same key used for encryption is processed to generate the same sequence of Caesar cipher shifts.
2.  **Padding Removal:** The random padding is removed from the encrypted text.
3.  **Multi-Round Decryption:** The decryption process is done in reverse order of the encryption rounds:
    *   **Rail Fence Cipher Decryption:** The text is decrypted using the Rail Fence cipher.
    *   **Substitution Cipher Decryption:** The result is decrypted using the reverse of the substitution map.
    *   **Caesar Cipher Decryption:** The result is decrypted using the Caesar cipher with the corresponding shift.
4.  **Final Substitution Decryption:** A final substitution decryption is performed to get the original plaintext.

## `alldecryption` Tool

The `alldecryption` tool attempts to decrypt a given ciphertext by trying a number of rounds from 0 to 100. This can be useful if the number of encryption rounds is unknown. It will output the decrypted text for each number of rounds.

## Contributing

Contributions to this project are welcome. Please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License.
