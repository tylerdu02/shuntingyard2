/* 
  * Tyler Du
  * 4/16/23
  * Shunting Yard. Create the prefix, infix, and postfix of an inputted equation.
  * Used https://en.wikipedia.org/wiki/Shunting_yard_algorithm for help
  * Used https://en.wikipedia.org/wiki/Binary_expression_tree for help
  */

#include <iostream>
#include <cstring>
#include <vector>
#include "Node.h"

using namespace std;

void postfixToBinaryTree(Node* queueHead, Node* &root);
void treetoInfix(Node* root);
void treetoPrefix(Node* root);
void treetoPostfix(Node* root);

void dequeue(Node* &headQueue);
void enqueue(Node* &headQueue, Node* & tailQueue, Node* input);
void push(Node* &tailStack, int operatorstack);
Node* pop(Node* &tailStack);
int peek(Node* tailStack);
int precedence(int character);

int main() {
  char expression[20];
  cout << "Input your mathematical expression with no spaces.";
  cin >> expression;

  Node* tailStack = NULL;
  Node* headQueue = NULL;
  Node* tailQueue = NULL;
  int i = 0;
  while (expression[i] != '\0') {
    Node* input = new Node(int(expression[i]), NULL);
    if (input->num > 47 && input->num < 58) {//asii table. checking if number is >0 & <9
      enqueue(headQueue, tailQueue, input);
    }
    else if (input->num == ')') {
      while(tailStack->num != '(') {
        if (tailStack->next == NULL) {
        }
        enqueue(headQueue, tailQueue, pop(tailStack));
        if (tailStack == NULL) {
          break;
        }
      }
      pop(tailStack);
    }
    else if (input->num == '(') {
      push(tailStack, int(expression[i]));
    }
    else if (input->num == '+' || input->num == '*' || input->num == '-' || input->num == '/' || input->num == '^') {//operators
      while ((tailStack != NULL) && (precedence(peek(tailStack)) >= precedence(peek(input)))) {
        enqueue(headQueue, tailQueue, pop(tailStack));
      }
      push(tailStack, input->num);
    }
    ++i;
  }
  while(tailStack != NULL) {
    enqueue(headQueue, tailQueue, pop(tailStack));
  }

  Node* root = NULL;
    postfixToBinaryTree(headQueue, root);

  bool cont = true;
  char notation[20];
  while (cont == true) {
    // prints
    cout << "Infix: ";
    treetoInfix(root);
    cout << endl;

    cout << "Prefix: ";
    treetoPrefix(root);
    cout << endl;

    cout << "Postfix: ";
    treetoPostfix(root);
    cout << endl;

    return 0;
    }
  }

void postfixToBinaryTree(Node* queueHead, Node* &root) { //binary expression tree
  Node* input = queueHead;
  vector<Node*>tree;
  while(input != NULL) {
    if (input->num > 47 && input->num < 58) {
    tree.push_back(input);
    }
    else {
      input->right = tree.back();
      tree.pop_back();
      input->left = tree.back();
      tree.pop_back();
      tree.push_back(input);
    }
    input = input->next;
  }
  root = tree[0];
}

void treetoInfix(Node* root) {//infix notation
  if (root != NULL) {
    if (root->num < 48) {//if operator
      cout << "(";
    }
    treetoInfix(root->left);
    cout << char(root->num);
    treetoInfix(root->right);
    if(root->num < 48) {
      cout << ")";
    }
  }
}


void treetoPrefix(Node* root) {//prefix notation
  if (root != NULL) {
    cout << char(root->num);
    treetoPrefix(root->left);
    treetoPrefix(root->right);
  }
}


void treetoPostfix(Node* root) {//postfix notation
  if (root != NULL) {
    treetoPostfix(root->left);
    treetoPostfix(root->right);
    cout << char(root->num);
  }
}

int precedence(int character) {
  if (character== '^') {
    return 3;
  }
  else if (character== '/' || character== '*') {
    return 2;
  }
  else if (character== '+' || character== '-') {
    return 1;
  }
  else {
    return 0;
  }
}

void dequeue(Node* &headQueue) { // deletes head
    if (headQueue == NULL) {
        cout << "Queue is empty" << endl;
    }
    else { // if queue is not empty
        Node* temp = headQueue;
        headQueue = headQueue->next;
        delete temp;
    }
}

void enqueue(Node* &headQueue, Node* &tailQueue, Node* newnode) {
  if (newnode == NULL) {
    return;
  }
  tailQueue = headQueue;
  if (tailQueue == NULL) {
    headQueue = newnode;
    tailQueue = headQueue;
  }
  else {
    while (tailQueue->next != NULL) {
      tailQueue = tailQueue->next;
    }
    tailQueue->next = newnode;
  }
  newnode->next = NULL;
}

void push(Node* &tailStack, int operatorstack) {
  Node* newnode = new Node(operatorstack, NULL);
  if (tailStack == NULL) {
    tailStack = newnode;
  }
  else {
    Node* temp = tailStack;
    tailStack = newnode;
    newnode->next = temp;
  }
}

Node* pop(Node* &tailStack) {//removes tail
   if (tailStack->next == NULL) {
    Node* returnvalue = tailStack;
    tailStack = NULL;
    return returnvalue;
  }
  Node* temp = tailStack->next;
  Node* move = tailStack;
  move->next = NULL;
  tailStack = temp;
  return move;
}

int peek(Node* tailStack) {
  if (tailStack == NULL) { // if stack is empty
        return 0;
    }
    return tailStack->num;
}