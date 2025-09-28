# Week 5 Project: Longest Common Substring

## Overview
This project implements the **Longest Common Substring (LCS)** algorithm in C++ using dynamic programming. 
The program builds and displays the DP lookup table step by step and extracts the longest substring shared by two input strings. 
The assignment specification allowed hardcoding or user input; this solution uses **user-provided strings** to make it flexible.

## Compilation & Usage
1. Navigate to the `week-5` folder and compile the code:
   ```bash
   g++ lcs.cpp -o lcs
   ```

2. Run the executable:
   ```bash
   ./lcs
   ```

3. Enter two strings of equal length when prompted.  
   Example:
   ```text
   Enter first string: ABAB
   Enter second string: BABA
   ```

4. The program will display:
   - The dynamic programming table (step-by-step values).  
   - The longest common substring and its length.

## Example Output
Input:
```
Enter first string: ABAB
Enter second string: BABA
```
Output:
```
Dynamic Programming Table:
      B  A  B  A
    0  0  0  0  0
A   0  0  1  0  1
B   0  1  0  2  0
A   0  0  2  0  3
B   0  1  0  3  0

Longest Common Substring: ABA
Length: 3
```

## Tests
Sample input pairs are provided in `tests/test_cases.txt`.  
You can run multiple test cases by redirecting input from the file:
```bash
./lcs < ../tests/test_cases.txt
```

