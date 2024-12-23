#include"AVLTree.h"

int main()
{
	Tree tree1;
	
	int i = 0;
	while (i!=9)
	{
		int key = 0;

		tree1.Menu();
		cin >> i;

		if (i==1)
		{
			cout << "\nEnter key To Insert:";
			cin >> key;
			tree1.Insert(key);
		}
		else if (i==2)
		{
			cout << "\nEnter key To Delete:";
			cin >> key;
			tree1.RemoveNode(key);
		}
		else if (i==3)
		{
			cout << "\n----- Tree -----" << endl;
			tree1.Display();
		}
		else if (i==4)
		{
			cout << "\nEnter Key To Search :";
			cin >> key;
			tree1.Search(key);
		}
		else if (i==9)
		{
			break;
		}
	}

	cout << endl;
	system("pause");
	return 0;
}