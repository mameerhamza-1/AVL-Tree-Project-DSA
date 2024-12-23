#include"AVLTree.h"

//........................... Node Implementation .........................

// Constructors
Node::Node()
{
	this->Key = 0;
	this->Left = NULL;
	this->Right = NULL;
	this->Height = 1;
}
Node::Node(int key)
{
	this->Key = key;
	this->Left = NULL;
	this->Right = NULL;
	this->Height = 1;
}

// Setters / Getters
void Node::setKey(int key)
{
	this->Key = key;
}
int Node::getKey()
{
	return this->Key;
}

void Node::setLeft(Node* left)
{
	this->Left = left;
}
Node* Node::getLeft()
{
	return this->Left;
}

void Node::setRight(Node* Right)
{
	this->Right = Right;
}
Node* Node::getRight()
{
	return this->Right;
}

void Node::setHeight(int height)
{
	this->Height = height;
}
int Node::getHeight()
{
	return this->Height;
}


// ................................ AVL Tree Implementation ..............................


Tree::Tree()
{
	Root = NULL;
}

bool Tree::isEmpty()
{
	if (Root == NULL)
	{
		return true;
	}
	return false;
}

void Tree::Insert(int key)
{
	if (isEmpty())
	{
		Node* temp = new Node(key);
		Root = temp;
		Root->setHeight(0);
	}
	else
	{
		Node* parent = ToFind(key);
		if (parent == NULL)
		{
			cout << "Duplication is not allowed!\n";
			return;
		}
		else
		{
			Node* temp = new Node(key);
			if (key < parent->getKey())
			{
				parent->setLeft(temp);
				parent->setHeight(UpdateHeight(parent));
				Root = checkFactors(Root, key);
			}
			else if (key > parent->getKey())
			{
				parent->setRight(temp);
				parent->setHeight(UpdateHeight(parent));
				Root = checkFactors(Root, key);
			}
		}
	}
}

Node* Tree::ToFind(int key)
{
	Node* parent = NULL;
	Node* temp = Root;

	while (temp != NULL)
	{
		if (temp->getKey() == key)
		{
			return NULL;
		}
		else
		{
			if (temp->getKey() > key)
			{
				parent = temp;
				temp = temp->getLeft();
			}
			else if (temp->getKey() < key)
			{
				parent = temp;
				temp = temp->getRight();
			}
		}
	}
	return parent;
}

int Tree::getHeight(Node* temp)
{
	int height = 0;
	if (temp == NULL)
	{
		return 0;
	}
	else
	{
		height = temp->getHeight();
	}
	return height;
}

int Tree::Factor(Node* temp)
{
	if (temp==NULL)
	{
		return 0;
	}
	return getHeight(temp->getLeft()) - getHeight(temp->getRight());
}


// CASES

//Right Rotation
Node* Tree::RightRotation(Node* root)
{
	Node* rootLeft = root->getLeft();		// Root - Right Child
	Node* temp = rootLeft->getRight();		// root - left - right Child

	rootLeft->setRight(root);
	root->setLeft(temp);

	rootLeft->setHeight(UpdateHeight(rootLeft));
	root->setHeight(UpdateHeight(root));

	return rootLeft;
}

//left rotation
Node* Tree::LeftRotation(Node* root)
{
	Node* rootRight = root->getRight();				// Root - Right child
	Node* temp = rootRight->getLeft();		// Root - Right - Left child

	rootRight->setLeft(root);
	root->setRight(temp);

	root->setHeight(UpdateHeight(root));
	rootRight->setHeight(UpdateHeight(rootRight));

	return rootRight;
}

Node* Tree::LeftRightRotation(Node* root)
{
	Node* Root = root->getLeft();

	// Left Rotation
	root->setLeft(LeftRotation(Root));

	//Right Rotation
	root = RightRotation(root);
	return root;
}

Node* Tree::RightLeftRotation(Node* root)
{
	Node* Root = root->getRight();

	//Right Rotation
	root->setRight(RightRotation(Root));

	//Left Rotation
	root = LeftRotation(root);

	return root;
}


Node* Tree::checkFactors(Node* n, int key)
{
	if (n != NULL)
	{
		if (key < n->getKey())
		{
			checkFactors(n->getLeft(), key);
		}
		else if (key > n->getKey())
		{
			checkFactors(n->getRight(), key);
		}
		int factor = Factor(n);
		n = BalanceTree(n, factor);
	}
	return n;
}

Node* Tree::BalanceTree(Node* root, int factor)
{
	Node* left = root->getLeft();
	Node* right = root->getRight();

	//Left Left Case
	if (factor > 1 && left->getLeft() != NULL)
	{
		root = RightRotation(root);
	}

	// Right Right Case
	else if (factor < -1 && right->getRight() != NULL)
	{
		root = LeftRotation(root);
	}

	// Left Right Case
	else if (factor > 1 && left->getRight() != NULL)
	{
		root = LeftRightRotation(root);
	}

	// Right Left Case
	else if (factor < -1 && right->getLeft() != NULL)
	{
		root = RightLeftRotation(root);
	}
	else
	{
		return root;
	}
	return root;
}


void Tree::Inorder(Node* n)
{
	if (n != NULL)
	{
		Inorder(n->getLeft());
		cout << "\nkey: " << n->getKey();
		//cout << "Height: " << n->getHeight() << endl;
		Inorder(n->getRight());
	}
}

void Tree::Display()
{
	Inorder(Root);
}

int Tree::Maximum(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

int Tree::UpdateHeight(Node* parent)
{
	parent->setHeight(Maximum(getHeight(parent->getLeft()), getHeight(parent->getRight())) +1 );
	return parent->getHeight();
}

Node* Tree::Search(int key)
{
	Node* temp = Root;

	while (temp != NULL)
	{
		if (key == temp->getKey())
		{
			return temp;
		}
		else if (key < temp->getKey())
		{
			temp = temp->getLeft();
		}
		else if (key > temp->getKey())
		{
			temp = temp->getRight();
		}
	}
	return NULL;
}


void Tree::RemoveNode(int key)
{
	Node* temp = Root;
	Node* parent = NULL;

	while (temp != NULL)
	{
		if (key == temp->getKey())
		{
			break;
		}
		else if (key < temp->getKey())
		{
			parent = temp;
			temp = temp->getLeft();
		}
		else if (key > temp->getKey())
		{
			parent = temp;
			temp = temp->getRight();
		}
	}

	if (temp == NULL)
	{
		return;
	}
	else
	{
		if (temp->getRight() == NULL && temp->getLeft() == NULL)	// No Child
		{
			if (parent->getRight() != NULL)
			{
				parent->setRight(NULL);
			}
			else
			{
				parent->setLeft(NULL);
			}
			delete temp;
		}
		else if (temp->getRight() == NULL || temp->getLeft() == NULL)	// One Child
		{
			if (parent->getRight()==temp)
			{
				if (temp->getRight()!=NULL)
				{
					parent->setRight(temp->getRight());
				}
				else
				{
					parent->setRight(temp->getLeft());
				}
					delete temp;
			}
			else if (parent->getLeft()==temp)
			{
				if (temp->getLeft()!=NULL)
				{
					parent->setLeft(temp->getLeft());
				}
				else
				{
					parent->setLeft(temp->getRight());
				}
				delete temp;
			}
		}
		else if (temp->getRight() != NULL && temp->getLeft() != NULL)  // Two Children
		{
			// Find the minimum node in the right subtree (in-order successor)
			Node* successorParent = temp;
			Node* successor = temp->getRight();
			while (successor->getLeft() != NULL)
			{
				successorParent = successor;
				successor = successor->getLeft();
			}

			// Replace value
			temp->setKey(successor->getKey());

			// Remove Node
			if (successorParent->getLeft() == successor)
			{
				successorParent->setLeft(successor->getRight());
			}
			else
			{
				successorParent->setRight(successor->getRight());
			}
			delete successor;
		}
	}
}

void Tree::Menu()
{
	cout << "\n\n-----AVL TREE-----" << endl;
	cout << "Press 1 to Insert :" << endl;
	cout << "Press 2 to Delete :" << endl;
	cout << "Press 3 to Display :" << endl;
	cout << "Press 4 to Search :" << endl;
	cout << "Press 9 to Exit :";
}
