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
    else if (input->num == '+' || input->num == '*' || input->num == '-' || input->num == '/' || input->num == '^') {//operator
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
