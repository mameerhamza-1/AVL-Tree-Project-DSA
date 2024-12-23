#pragma once
#pragma once
#include"Node.h"
using namespace std;

class Tree
{
private:
	Node* Root;

public:
	// Constructors
	Tree();

	// Methods
	bool isEmpty();
	Node* ToFind(int);
	void Insert(int);

	Node* checkFactors(Node*, int);
	Node* BalanceTree(Node*, int);
	int Factor(Node*);

	int getHeight(Node*);
	int UpdateHeight(Node*);
	int Maximum(int, int);

	void Inorder(Node*);
	void Display();

	Node* Search(int);
	void RemoveNode(int);
	void Menu();

	// CASES
	Node* RightRotation(Node*);
	Node* LeftRotation(Node*);
	Node* LeftRightRotation(Node*);
	Node* RightLeftRotation(Node*);
};