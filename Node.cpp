#include "Node.h"
#include <iostream>
#include <cstring>

Node:: Node(int newnum, Node* newnext) {
    num = newnum;
    next = newnext;
    left = nullptr;
    right = nullptr;
}
