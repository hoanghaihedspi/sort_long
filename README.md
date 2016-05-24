# Input
Input file "input.txt".\\
First line: Number of integers: n (n = 1000000)\\
Second line: n signed 32-bit integers, separated by single spaces.

# Output
Output file "output.txt".\\
First line: Number of integers: n (n = 1000000)\\
Second line: n signed 32-bit integers were sorted by non decrease and separated by single spaces.

# Run
Run program in a Unix-like system.

# Create input file "input.txt" with random data
```bash
$ gcc -w -o run creatTest.c -std=c11; ./run
```

# Run program to sort data in file "input.txt" and write resuilt to file "output.txt"
```bash
$ g++ -w -o2 -o run sort.cpp -std=c++11; ./run
```