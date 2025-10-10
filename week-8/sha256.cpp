/*
 * Project: Week 8 - SHA-256 Implementation
 * Course: CSC-6200 Advanced Algorithms
 * Author: Mohammed Anas
 * Date: October 2025
 * 
 * Description:
 * ------------
 * This program implements the SHA-256 hashing algorithm in C++.
 * It follows the pseudocode from the official NIST FIPS 180-4 specification
 * and the Wikipedia entry for SHA-2.
 * 
 * The program reads an input text file (e.g., the Book of Mark from the Bible),
 * processes its content through the SHA-256 hashing pipeline, and produces a
 * fixed-length 256-bit hash value as output.
 * 
 * SHA-256 is a one-way cryptographic function used for data integrity,
 * authentication, and digital signatures. It ensures that even a one-bit
 * change in input drastically changes the output hash.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

// ---------------- SHA-256 Helper Macros ----------------

// Bitwise rotation right (32-bit)
#define ROTRIGHT(word, bits) (((word) >> (bits)) | ((word) << (32 - (bits))))

// Logical functions defined by SHA-256 specification
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

// Sigma and sigma transformations (bit mixing functions)
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

// SHA-256 round constants (first 32 bits of the fractional parts of cube roots of primes 2–311)
static const unsigned int K[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

// ---------------- SHA-256 Class Definition ----------------

class SHA256 {
public:
    SHA256() { reset(); }

    // Feed input data into the algorithm
    void update(const unsigned char *data, size_t len);

    // Perform final padding and process remaining data
    void finalize();

    // Return final hash value in hexadecimal format
    string digest() const;

private:
    // Reset to initial state
    void reset();

    // Core SHA-256 compression function
    void transform(const unsigned char *data);

    unsigned int state[8];      // Hash state registers
    unsigned char buffer[64];   // 512-bit message block buffer
    unsigned long long bitlen;  // Total bits processed
    unsigned int datalen;       // Length of data currently in buffer
};

// ---------------- SHA-256 Class Implementation ----------------

// Initialize hash values (first 32 bits of square roots of primes 2–19)
void SHA256::reset() {
    state[0] = 0x6a09e667;
    state[1] = 0xbb67ae85;
    state[2] = 0x3c6ef372;
    state[3] = 0xa54ff53a;
    state[4] = 0x510e527f;
    state[5] = 0x9b05688c;
    state[6] = 0x1f83d9ab;
    state[7] = 0x5be0cd19;
    datalen = 0;
    bitlen = 0;
}

// Core transformation function: operates on 512-bit blocks
void SHA256::transform(const unsigned char *data) {
    unsigned int m[64], a, b, c, d, e, f, g, h, t1, t2;

    // Message schedule array (first 16 words from data, remaining from transformations)
    for (unsigned int i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j+1] << 16) | (data[j+2] << 8) | data[j+3];
    for (unsigned int i = 16; i < 64; ++i)
        m[i] = SIG1(m[i-2]) + m[i-7] + SIG0(m[i-15]) + m[i-16];

    // Initialize working variables with current hash state
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    // Main compression loop (64 rounds)
    for (unsigned int i = 0; i < 64; ++i) {
        t1 = h + EP1(e) + CH(e,f,g) + K[i] + m[i];
        t2 = EP0(a) + MAJ(a,b,c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    // Add this chunk's hash to the final result
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

// Feed message into buffer and process chunks as needed
void SHA256::update(const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        buffer[datalen] = data[i];
        datalen++;
        if (datalen == 64) {
            transform(buffer);
            bitlen += 512;
            datalen = 0;
        }
    }
}

// Final padding and length encoding
void SHA256::finalize() {
    unsigned int i = datalen;

    // Append the bit '1' (0x80)
    if (datalen < 56) {
        buffer[i++] = 0x80;
        while (i < 56)
            buffer[i++] = 0x00;
    } else {
        buffer[i++] = 0x80;
        while (i < 64)
            buffer[i++] = 0x00;
        transform(buffer);
        memset(buffer, 0, 56);
    }

    // Append total message length (big endian)
    bitlen += datalen * 8;
    buffer[63] = bitlen;
    buffer[62] = bitlen >> 8;
    buffer[61] = bitlen >> 16;
    buffer[60] = bitlen >> 24;
    buffer[59] = bitlen >> 32;
    buffer[58] = bitlen >> 40;
    buffer[57] = bitlen >> 48;
    buffer[56] = bitlen >> 56;
    transform(buffer);
}

// Return final hash as hexadecimal string
string SHA256::digest() const {
    stringstream ss;
    for (int i = 0; i < 8; ++i)
        ss << hex << setw(8) << setfill('0') << state[i];
    return ss.str();
}

// ---------------- Utility Function ----------------

// Compute SHA-256 hash from a given file
string sha256FromFile(const string &filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return "";
    }

    SHA256 sha;
    string line;
    while (getline(file, line)) {
        sha.update(reinterpret_cast<const unsigned char*>(line.c_str()), line.size());
    }
    sha.finalize();
    return sha.digest();
}

// ---------------- Main Function ----------------

int main() {
    string filepath;
    cout << "Enter path to Book of Mark text file: ";
    getline(cin, filepath);

    string hash = sha256FromFile(filepath);
    if (!hash.empty())
        cout << "\nSHA-256 Hash of the Book of Mark:\n" << hash << endl;

    return 0;
}
