# Week 8 Project: SHA-256 Algorithm Implementation

## Overview
This project implements the **SHA-256 algorithm** in C++ following the official NIST FIPS 180-4 specification. It reads a plain text file (such as the *Book of Mark*), processes the input data through the SHA-256 hashing pipeline, and outputs a fixed-length 256-bit hash value.

The algorithm uses bitwise operations, message scheduling, and nonlinear functions to ensure data integrity and cryptographic security. The implementation adheres to pseudocode from the [Wikipedia SHA-2 documentation](https://en.wikipedia.org/wiki/SHA-2).

---

## Compilation and Usage
### **Compile the program**
```bash
g++ sha256.cpp -o sha256


Enter path to Book of Mark text file: Bible Revised Standard Version.txt

SHA-256 Hash of the Book of Mark:
a6d422d6b712632110abcbc7256f7c9accf3b4bdb82914ba72a9e0961b8e919a