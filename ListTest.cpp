/***
* Jasmeen Kaur 
* ListTest.cpp
***/ 


#include "List.h"
#include <iostream>
#include <cassert>

void test_list_operations() {
    List A;

//test for insertstion
    A.moveFront(); 
    A.insertAfter(1);
    A.moveNext(); //move cursor
    A.insertAfter(2);
    A.moveNext();
    A.insertAfter(3);
    A.moveFront();
    assert(A.length() == 3);

//test for peekNext and moveNext
    assert(A.peekNext() == 1); 
    assert(A.moveNext() == 1); 
    assert(A.peekNext() == 2); 

//test for insertBefore and movePrev
    A.insertBefore(0);
    assert(A.movePrev() == 0);
    assert(A.peekNext() == 0);

    A.moveBack();
    assert(A.peekPrev() == 3);
    assert(A.length() == 4);   

//test for clear
    A.clear();
    assert(A.length() == 0); 
    std::cout << "Basic operations passed.\n";
//extra tests
    try {
        A.peekNext();
        assert(false);
    } catch (const std::range_error& e) {
        std::cout << "Exception has been caught: " << e.what() << "\n";
    }

//test for moveFront, moveBack w/ empty list
    A.moveFront();
    A.moveBack();
    assert(A.position() == 0);

    A.insertAfter(5);
    assert(A.peekNext() == 5);
    assert(A.length() == 1);

    List B;
    B.moveFront();
    B.insertAfter(6);
    B.moveNext();
    B.insertAfter(7);

    List C = A.concat(B);
    assert(C.length() == 3);
    C.moveFront();
    std::cout << "Contents of C after concatenation: " << C.to_string() << "\n";
    std::cout << "Position in C after moveFront(): " << C.position() << "\n";
    assert(C.peekNext() == 5);
    C.moveNext();
    assert(C.peekNext() == 6);
    C.moveNext();
    assert(C.peekNext() == 7);

    List D;
    D.moveFront();
    D.insertAfter(1);
    D.moveNext();
    D.insertAfter(2);
    D.moveNext();
    D.insertAfter(1); 
    D.moveNext();
    D.insertAfter(3);
    D.moveNext();
    D.insertAfter(2);
    D.cleanup();                  
    D.moveFront();
    assert(D.peekNext() == 1); 
    D.moveNext();
    assert(D.peekNext() == 2);
    D.moveNext();
    assert(D.peekNext() == 3);

    std::cout << "PASSED ALL TESTS!.\n";
}

int main() {
    test_list_operations();
    return 0;
}
