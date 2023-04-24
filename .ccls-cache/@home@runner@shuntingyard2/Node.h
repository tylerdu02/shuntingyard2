#include <cstring>
#pragma once

class Node {
 public:
 int num;
 Node* next;
 Node* left;
 Node* right;
 Node(int newnum, Node* newnext);
};