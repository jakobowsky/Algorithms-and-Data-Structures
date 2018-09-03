#include "Tree.h"



Tree::Tree()
{
	root = NULL;
}

Tree::~Tree()
{
	deleteTree(this->root);
}

void Tree::insertStudent(string imie, string nazwisko, unsigned int nr_indeksu)
{
	BSTNode * newGuy = new BSTNode;
	newGuy->Left = NULL;
	newGuy->Right = NULL;

	newGuy->osoba.imie = imie;
	newGuy->osoba.nazwisko = nazwisko;
	newGuy->osoba.nr_indeksu = nr_indeksu;

	BSTNode * temp = root;
	if (!temp) //jezeli drzewo jest puste to nowy student staje sie jego korzeniem
		root = newGuy;
	else
	{
		while (1)
		{
			if (nr_indeksu < temp->osoba.nr_indeksu) //jezeli wartos jest mniejsza to idziemy w lewo
			{
				if (!temp->Left) //jezeli nie ma lewego syna no to nowy student sie staje nim
				{
					temp->Left = newGuy;
					break;
				}
				else //w przeciwnym wypadku zjezdza nizej
				{
					temp = temp->Left;
				}
			}
			else
			{
				if (!temp->Right)
				{
					temp->Right = newGuy;
					break;
				}
				else
				{
					temp = temp->Right;
				}
			}
		}
	}
	newGuy->Up = temp;

}

void Tree::deleteStudent(unsigned int nr_indeksu)
{

	BSTNode * toDelete = searchForStudent(nr_indeksu);
	BSTNode * Y, *Z;
	if (toDelete)
	{
		// Jeœli toDelete nie ma synów lub ma tylko jednego, to Y wskazuje toDelete
		// Inaczej Y wskazuje nastêpnik toDelete
		if ((!toDelete->Left) || (!toDelete->Right))
			Y = toDelete;
		else Y = succesor(toDelete);

		// Z wskazuje syna Y lub NULL
		if (Y->Left)
			Z = Y->Left;
		else Z = Y->Right;

		//Jezeli syn Y istnieje to zastapi Y w drzewie
		if (Z) Z->Up = Y->Up;

		//Y zostaje zastapione przez Z w drzewie
		if (!Y->Up) root = Z;
		else if (Y == Y->Up->Left) Y->Up->Left = Z;
		else Y->Up->Right = Z;
		
		if (Y != toDelete) toDelete->osoba = Y->osoba;

		delete Y;
	}


}

void Tree::deleteTree(BSTNode *root)
{
	if (root)
	{
		deleteTree(root->Left);
		deleteTree(root->Right);
		//delete root;
		
		if (root != this->root)
			delete root;
		else this->root = NULL;
		
	}
}

void Tree::inorder(BSTNode * n)
{
	if (n)
	{
		inorder(n->Left);
		//cout << n->osoba.imie << " " << n->osoba.nazwisko << " " << n->osoba.nr_indeksu << endl;
		cout << n->osoba.nr_indeksu << endl;
		inorder(n->Right);
	}
}

void Tree::preorder(BSTNode * n)
{
	if (n)
	{
		cout << n->osoba.nr_indeksu << endl;
		//cout << n->osoba.imie << " " << n->osoba.nazwisko << " " << n->osoba.nr_indeksu << endl;
		preorder(n->Left);
		preorder(n->Right);
	}
}

void Tree::postorder(BSTNode * n)
{
	if (n)
	{
		postorder(n->Left);
		postorder(n->Right);
		//cout << n->osoba.imie << " " << n->osoba.nazwisko << " " << n->osoba.nr_indeksu << endl;
		cout <<n->osoba.nr_indeksu << endl;
	}
}

BSTNode * Tree::searchForStudent(int nr_indeksu)
{
	BSTNode * temp = root;
	while (temp->osoba.nr_indeksu!=nr_indeksu)
	{
		//cout << "Test " << temp->osoba.nr_indeksu << endl;
		if (nr_indeksu < temp->osoba.nr_indeksu)
			temp = temp->Left;
		else
			temp = temp->Right;
	}
	return temp;
}

BSTNode * Tree::minBST(BSTNode * p)
{
	if (p)
	{
		while (p->Left) 
		{
			p = p->Left;
		}
	}
	return p;
}

BSTNode * Tree::succesor(BSTNode * p) //szuka nastepnika
{
	BSTNode * temp;
	if (p)
	{
		if (p->Right)
			return minBST(p->Right);
		else
		{
			temp = p->Up;
			while (temp && (p==temp->Right))
			{
				p = temp;
				temp = temp->Up;
			}
			return temp;
		}
	}
	return p;
}

void Tree::rotL(BSTNode * A)
{
	BSTNode * B = A->Right;
	BSTNode *temp = A->Up;

	if (B)
	{
		A->Right = B->Left;
		if (A->Right)
			A->Right->Up = A;
		B->Left = A;
		B->Up = temp;
		A->Up = B;
		if (temp)
		{
			if (temp->Left == A)
				temp->Left = B;
			else
				temp->Right = B;
		}
		else root = B;
	}


}

void Tree::rotR(BSTNode * A)
{
	BSTNode * B = A->Left;
	BSTNode * temp = A->Up;

	if (B)
	{
		A->Left = B->Right;
		if (A->Left) A->Left->Up = A;

		B->Right = A;
		B->Up = temp;
		A->Up = B;
		if (temp)
		{
			if (temp->Left == A)
				temp->Left = B;
			else temp->Right = B;
		}
		else root = B;

	}


}

int Tree::log2BST(int x)
{
	{
		int y = 1;
		while ((x >>= 1) > 0) y <<= 1;

		return y;
	}
}

void Tree::rebalanceTree()
{
	int n, s;
	BSTNode * temp;
	n = 0;
	temp = root;
	while (temp)
	{ // najpierw tworzymy liste liniowa 
		if (temp->Left)
		{
			rotR(temp);
			temp = temp->Up;
		}
		else
		{
			n++;
			temp = temp->Right;
		}
	}
	//teraz tworzymy drzewo BST zrownowazone

	s = n + 1 - log2BST(n + 1);
	temp = root;
	for (int i = 0; i < s; i++)
	{
		rotL(temp);
		temp = temp->Up->Right;
	}
	n = n - s;

	while (n > 1)
	{
		n >>= 1;
		temp = root;
		for (int i = 0; i < n; i++)
		{
			rotL(temp);
			temp = temp->Up->Right;
		}
	}
	
}










