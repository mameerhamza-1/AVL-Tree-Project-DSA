#pragma once
#include<iostream>
using namespace std;

class Node
{
private:
	int Key;
	Node* Left;
	Node* Right;
	int Height;

public:
	// Constructors
	Node();
	Node(int);

	// Setters / Getters
	
	void setKey(int);
	int getKey();
	
	void setLeft(Node*);
	Node* getLeft();
	
	void setRight(Node*);
	Node* getRight();
	
	void setHeight(int);
	int getHeight();

};
