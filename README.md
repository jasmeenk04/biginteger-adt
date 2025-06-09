# BigInteger ADT

A custom Abstract Data Type in C++ for performing arithmetic operations on arbitrarily large integers.

🧮 **Features**
- Supports addition and subtraction of huge integers
- Full operator overloading (`==`, `<`, `<=`, `>`, `>=`, `+`, `-`)
- File I/O for reading and writing BigIntegers
- Handles negative numbers and zero correctly
- Includes unit testing with `BigIntegerTest.cpp` and `ListTest.cpp`

## 🛠 How to Run

1. **Clone the repo:**
```bash
git clone https://github.com/yourusername/biginteger-adt.git
cd biginteger-adt
```

2. **Compile everything:**
```bash
make
```

3. **Run the Tests:**
```bash 
./BigIntegerTest
```

4. **Run your own input:**
Run the Arithmetic program using input.txt and redirect output to output.txt

Expected Setup


input.txt: should contain two large integers (and a blank line between them) like:
12345678901234567890

98765432109876543210

output.txt: will be created or overwritten with the results of your arithmetic operations.

# Run it!
```bash 
./Arithmetic < input.txt > output.txt
```