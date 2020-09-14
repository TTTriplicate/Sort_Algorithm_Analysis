#pragma once

#include "Node.h"

class LinkedList {
private:
	Node* Head;
	void insert(Node* newNode);
	Node* findPreceding(int key);
public:
	LinkedList();
	~LinkedList();
	void newNode(int key, int data);
	Node* search(int key);
	void remove(int key);
	void print();
};