#pragma once

class Node {
private:
	int Key;
	int Data;
	Node* Next;

public:
	Node();
	Node(int key, int data);
	Node(int key, int data, Node* next);
	~Node();
	int getData();
	void setData(int data);
	int getKey();
	Node* getNext();
	void setNext(Node* next);

	bool operator> (const Node& a);
	bool operator< (const Node& a);
	bool operator== (const Node& a);
};