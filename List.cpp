/***
* Jasmeen Kaur 
* List.cpp
***/ 

#include "List.h"
#include <iostream>
#include <string>
#include <stdexcept>


List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}


//constructor + destructor
List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) : List() {
    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        insertAfter(N->data);
        N = N->next;
    }
    moveFront();
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

//access funcs
int List::length() const { return num_elements; }

ListElement List::front() const {
    if (num_elements == 0) throw std::length_error("List is empty");
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (num_elements == 0) throw std::length_error("List is empty");
    return backDummy->prev->data;
}

int List::position() const { return pos_cursor; }

ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) throw std::range_error("No element after cursor");
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (pos_cursor <= 0) throw std::range_error("No element before cursor");
    return beforeCursor->data;
}

//manipulation procedures
void List::clear() {
    moveFront();
    while (num_elements > 0) eraseAfter();
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

ListElement List::moveNext() {
    if (pos_cursor >= num_elements) {
        return back();
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (pos_cursor <= 0) throw std::range_error("Cursor at front");
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor++;
    num_elements++;
}

void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements) throw std::range_error("No element after cursor");
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (pos_cursor <= 0) throw std::range_error("No element before cursor");
    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (pos_cursor >= num_elements) throw std::range_error("No element after cursor");
    Node* N = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    delete N;
    num_elements--;
}

void List::eraseBefore() {
    if (pos_cursor <= 0) throw std::range_error("No element before cursor");
    Node* N = beforeCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    delete N;
    num_elements--;
}

//other funcs
int List::findNext(ListElement x) {
    while (pos_cursor < num_elements) {
        if (moveNext() == x) return pos_cursor;
    }
    return -1;
}

int List::findPrev(ListElement x) {
    while (pos_cursor > 0) {
        if (movePrev() == x) return pos_cursor;
    }
    return -1;
}

void List::cleanup() {
    if (num_elements <= 1) return; 

    Node* current = frontDummy->next; //start w first
    int original_pos = pos_cursor;    

    for (int i = 0; i < num_elements; ++i) {
        Node* runner = current->next;
        int runner_pos = i + 1;  
        while (runner != backDummy) {
            if (runner->data == current->data) {
                runner->prev->next = runner->next;
                runner->next->prev = runner->prev;

                if (runner_pos < pos_cursor) {
                    pos_cursor--; 
                } else if (runner == afterCursor) {
                    afterCursor = runner->next; 
                }

                Node* to_delete = runner;
                runner = runner->next; 
                delete to_delete;
                num_elements--;  //update
            } else {
                runner = runner->next;  
            }
            runner_pos++;
        }
        current = current->next; //move to next
    }

    moveFront();
    for (int j = 0; j < original_pos; ++j) {
        moveNext();
    }
}

List List::concat(const List& L) const {
    List C;
    Node* N = frontDummy->next;
    while (N != backDummy) {
        C.insertAfter(N->data);
        C.moveNext(); 
        N = N->next;
    }
    N = L.frontDummy->next;
    while (N != L.backDummy) {
        C.insertAfter(N->data);
        C.moveNext(); 
        N = N->next;
    }
    C.moveFront();
    return C;
}

std::string List::to_string() const {
    std::string s = "(";
    Node* N = frontDummy->next;
    while (N != backDummy) {
        s += std::to_string(N->data);
        if (N->next != backDummy) s += ",";
        N = N->next;
    }
    s += ")";
    return s;
}

bool List::equals(const List& R) const {
    if (num_elements != R.num_elements) return false;
    Node* N = frontDummy->next;
    Node* M = R.frontDummy->next;
    while (N != backDummy) {
        if (N->data != M->data) return false;
        N = N->next;
        M = M->next;
    }
    return true;
}

//overriden operators
std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        clear();
        Node* N = L.frontDummy->next;
        while (N != L.backDummy) {
            insertAfter(N->data);
            N = N->next;
        }
        moveFront();
    }
    return *this;
}