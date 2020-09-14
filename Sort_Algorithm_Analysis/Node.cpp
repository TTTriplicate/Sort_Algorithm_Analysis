/*********************
Class: Node.cpp
Pupose: Nodes for a Linked List
*********************/

#include "Node.h"

//default and parameterized constructors
Node::Node() {
	Key = -1;
	Data = -1;
	Next = nullptr;
};

Node::Node(int key, int data) {
	Key = key;
	Data = data;
	Next = nullptr;
}

Node::Node(int key, int data, Node* next) {
	Key = key;
	Data = data;
	Next = next;
}

//destructor
Node::~Node() {
	Next = nullptr;
	delete Next;
}

int Node::getData() {
	return Data;
}

void Node::setData(int data) {
	Data = data;
}

int Node::getKey() {
	return Key;
}

Node* Node::getNext() {
	return Next;
}

void Node::setNext(Node* next) {
	Next = next;
}

//These overloads allow direct comparison
//makes the insertion code in LinkedList more readable
bool Node::operator<(const Node& a) {
	return Data < a.Data;
}

bool Node::operator>(const Node& a) {
	return Data > a.Data;
}

bool Node::operator==(const Node& a) {
	return Data == a.Data;
}