/***
* Jasmeen Kaur 
* Arithmetic.cpp
***/ 

#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file(s)." << endl;
        return EXIT_FAILURE;
    }

    string A_str, B_str;
    getline(inFile, A_str);
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(inFile, B_str);

    BigInteger A(A_str);
    BigInteger B(B_str);

    outFile << A << "\n\n";
    outFile << B << "\n\n";

    outFile << (A + B) << "\n\n"; // A + B
    outFile << (A - B) << "\n\n"; // A - B
    outFile << (A - A) << "\n\n"; // A - A
    outFile << (BigInteger(3) * A - BigInteger(2) * B) << "\n\n"; // 3A - 2B
    outFile << (A * B) << "\n\n"; // A * B
    outFile << (A * A) << "\n\n"; // A^2
    outFile << (B * B) << "\n\n"; // B^2

    BigInteger A4 = A * A * A * A; // A^4
    BigInteger B5 = B * B * B * B * B; // B^5
    outFile << (BigInteger(9) * A4 + BigInteger(16) * B5) << "\n\n";

    inFile.close();
    outFile.close();

    return EXIT_SUCCESS;
}