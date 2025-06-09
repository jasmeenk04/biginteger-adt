/***
* Jasmeen Kaur 
* BigInteger.cpp
***/ 

#include "BigInteger.h"
#include <stdexcept>
#include <cctype>
#include <algorithm>

const int power = 9;
const long base = 1000000000;

//helper funcs
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(-L.peekNext());
        L.moveNext();
    }
}

void sumList(List& S, List A, List B, int sgn) {
    A.moveBack();
    B.moveBack();
    S.clear();
    long carry = 0;
    while (A.position() > 0 || B.position() > 0 || carry != 0) {
        long a = (A.position() > 0) ? A.movePrev() : 0;
        long b = (B.position() > 0) ? B.movePrev() : 0;
        long sum = a + sgn * b + carry;
        carry = sum / base;
        sum %= base;
        S.insertBefore(sum);
    }
}

int normalizeList(List& L) {
    if (L.length() == 0) return 0;
    L.moveFront();
    while (L.position() < L.length() && L.peekNext() == 0) {
        L.eraseAfter();
    }
    if (L.length() == 0) return 0;

    int sign = (L.front() < 0) ? -1 : 1;

    if (sign == -1) {
        negateList(L);
    }
    return sign;
}

void shiftList(List& L, int p) {
    L.moveFront();
    for (int i = 0; i < p; i++) {
        L.insertBefore(0);
    }
}

void scalarMultList(List& L, ListElement m) {
    L.moveBack();
    long carry = 0;
    while (L.position() > 0) {
        long val = L.movePrev() * m + carry;
        carry = val / base;
        val %= base;
        L.setAfter(val);
    }
    if (carry > 0) {
        L.insertBefore(carry);
    }
}

//constructors
BigInteger::BigInteger() : signum(0) {}

BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
    } else {
        signum = (x > 0) ? 1 : -1;
        long num = std::abs(x);
        while (num > 0) {
            digits.insertAfter(num % base);
            num /= base;
        }
    }
}

BigInteger::BigInteger(std::string s) {
    if (s.empty()) throw std::invalid_argument("BigInteger: The constructor is an empty string");
    
    bool isNegative = false;

    if (s[0] == '-') {
        isNegative = true;
        s = s.substr(1);
    } else if (s[0] == '+') {
        s = s.substr(1);
    } 
    
    s.erase(0, s.find_first_not_of('0'));
    
    if (s.empty()) {
        digits.insertBefore(0);
        signum = 0;
        return;
    }
    
    if (s.empty() || !std::all_of(s.begin(), s.end(), ::isdigit))
        throw std::invalid_argument("BigInteger: The constructor is a non numeric string");
    
    for (int i = s.length(); i > 0; i -= power) {
        int start = std::max(0, i - power);
        digits.insertBefore(std::stol(s.substr(start, i - start)));
    }
    signum = isNegative ? -1 : 1;
}

BigInteger::BigInteger(const BigInteger& N) : signum(N.signum), digits(N.digits) {}

// Access functions
int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum != N.signum) return (signum < N.signum) ? -1 : 1;
    if (digits.length() != N.digits.length())
        return (digits.length() < N.digits.length()) ? -1 * signum : 1 * signum;
    List A = digits, B = N.digits;
    A.moveFront();
    B.moveFront();
    while (A.position() < A.length()) {
        long a = A.moveNext(), b = B.moveNext();
        if (a != b) return (a < b) ? -1 * signum : 1 * signum;
    }
    return 0;
}

//manip. procedures
void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    if (signum != 0) signum = -signum;
}

//arithmetic ops.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger sum;
    sumList(sum.digits, digits, N.digits, 1);
    sum.signum = normalizeList(sum.digits);
    return sum;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger diff;
    sumList(diff.digits, digits, N.digits, -1);
    diff.signum = normalizeList(diff.digits);
    return diff;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger product;
    List temp = digits;
    List multiplier = N.digits;
    multiplier.moveBack();
    int shift = 0;
    while (multiplier.position() > 0) {
        List tempCopy = temp;
        scalarMultList(tempCopy, multiplier.movePrev());
        shiftList(tempCopy, shift++);
        sumList(product.digits, product.digits, tempCopy, 1);
    }
    product.signum = signum * N.signum;
    return product;
}

//other
std::string BigInteger::to_string() {
    if (signum == 0) return "0";
    std::string result = (signum == -1) ? "-" : "";
    digits.moveFront();
    result += std::to_string(digits.moveNext());
    while (digits.position() < digits.length()) {
        std::string part = std::to_string(digits.moveNext());
        while (part.length() < power) part = "0" + part;
        result += part;
    }
    return result;
}

//overload ops
std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) <= 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 1;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) >= 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return A;
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}
bool operator!=(const BigInteger& A, const BigInteger& B) {
    return !(A == B);
}


