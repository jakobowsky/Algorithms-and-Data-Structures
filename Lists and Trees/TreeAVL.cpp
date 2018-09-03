#include "TreeAVL.h"

TreeAVL::TreeAVL()
{
	root = NULL;
}

TreeAVL::~TreeAVL()
{
	postorderDeletion(this->root);
}

void TreeAVL::leftLeft(BSTNodeAVL * n)
{
	BSTNodeAVL * x = n->left;
	BSTNodeAVL * y = n->top;
	n->left = x->right;
	if (n->left != NULL) n->left->top = n;
	x->right = n;
	x->top = y;
	n->top = x;
	if (y == NULL) root = x;
	else
	{
		if (y->left == n) y->left = x;
		else y->right = x;
	}
	if (x->ratio == 1)
	{
		n->ratio = 0;
		x->ratio = 0;
	}
	else
	{
		n->ratio = 1;
		x->ratio = -1;
	}

}

void TreeAVL::rightRight(BSTNodeAVL * n)
{
	BSTNodeAVL * x = n->right;
	BSTNodeAVL * y = n->top;
	n->right = x->left;
	if (n->right != NULL) n->right->top = n;
	x->left = n;
	x->top = y;
	n->top = x;
	if (y == NULL) root = x;
	else
	{
		if (y->right == n) y->right = x;
		else y->left = x;
	}
	if (x->ratio == -1)
	{
		n->ratio = 0;
		x->ratio = 0;
	}
	else
	{
		n->ratio = -1;
		x->ratio = 1;
	}
}

void TreeAVL::rightLeft(BSTNodeAVL * n)
{
	BSTNodeAVL * x = n->right;
	BSTNodeAVL * y = x->left;
	BSTNodeAVL * z = n->top;
	x->left = y->right;
	if (x->left != NULL) x->left->top = x;
	n->right = y->left;
	if (n->right != NULL) n->right->top = n;
	y->left = n;
	y->right = x;
	n->top = y;
	x->top = y;
	y->top = z;
	if (z == NULL) root = y;
	else
	{
		if (z->left == n) z->left = y;
		else z->right = y;
	}
	if (y->ratio == -1) n->ratio = 1;
	else n->ratio = 0;
	if (y->ratio == 1) x->ratio = -1;
	else x->ratio = 0;
	y->ratio = 0;
}

void TreeAVL::leftRight(BSTNodeAVL * n)
{
	BSTNodeAVL * x = n->left;
	BSTNodeAVL * y = x->right;
	BSTNodeAVL * z = n->top;
	x->right = y->left;
	if (x->right != NULL) x->right->top = x;
	n->left = y->right;
	if (n->left != NULL) n->left->top = n;
	y->right = n;
	y->left = x;
	n->top = y;
	x->top = y;
	y->top = z;
	if (z == NULL) root = y;
	else
	{
		if (z->left == n) z->left = y;
		else z->right = y;
	}
	if (y->ratio == 1) n->ratio = -1;
	else n->ratio = 0;
	if (y->ratio == -1) x->ratio = 1;
	else x->ratio = 0;
	y->ratio = 0;
}

BSTNodeAVL * TreeAVL::MaxBST(BSTNodeAVL * n)
{
	while (n->right) n = n->right;
	return n;
}

BSTNodeAVL * TreeAVL::PredecessorBST(BSTNodeAVL * n)
{
	BSTNodeAVL * x = NULL;
	if (n->left != NULL) return MaxBST(n->left);
	else
	{
		x = n->top;
		while (x != NULL && n == x->left)
		{
			n = x;
			x = x->top;
		}
		return x;
	}
}

void TreeAVL::insertBST(string imie, string nazwisko, unsigned int nr_indeksu)
{
	BSTNodeAVL * cur, *tmp, *prev;
	bool isNotBalanced;
	cur = new BSTNodeAVL;
	cur->left = NULL;
	cur->right = NULL;
	cur->top = NULL;
	cur->ratio = 0;
	cur->osoba.imie = imie;
	cur->osoba.nazwisko = nazwisko;
	cur->osoba.nr_indeksu = nr_indeksu;
	tmp = root;
	//////////////////// Wstawianie wezla do drzewa avl
	if (!tmp) root = cur; //jezeli drzewo puste to nowy bedzie rootem
	else
	{
		while (true)
		{
			if (nr_indeksu < tmp->osoba.nr_indeksu)
			{
				if (tmp->left == NULL)
				{
					tmp->left = cur;
					break;
				}
				tmp = tmp->left;
			}
			else
			{
				if (tmp->right == NULL)
				{
					tmp->right = cur;
					break;
				}
				tmp = tmp->right;
			}
		}

		cur->top = tmp;

		if (tmp->ratio != 0) tmp->ratio = 0;
		else
		{
			tmp->left == cur ? tmp->ratio = 1 : tmp->ratio = -1;
			prev = tmp->top;
			isNotBalanced = false;
			while (prev)
			{
				if (prev->ratio != 0)
				{
					isNotBalanced = true;
					break;
				}
				prev->left == tmp ? prev->ratio = 1 : prev->ratio = -1;
				tmp = prev;
				prev = prev->top;
			}

			if (isNotBalanced == true)
			{
				if (prev->ratio == 1)
				{
					if (prev->right == tmp) prev->ratio = 0;
					else if (tmp->ratio == -1) leftRight(prev);
					else leftLeft(prev);
				}
				else
				{
					if (prev->left == tmp) prev->ratio = 0;
					else if (tmp->ratio == 1) rightLeft(prev);
					else rightRight(prev);
				}
			}


		}

	}
}

BSTNodeAVL * TreeAVL::searchForStudent(int nr_indeksu)
{
	BSTNodeAVL * temp = root;
	while (temp->osoba.nr_indeksu != nr_indeksu)
	{
		//cout << "Test " << temp->osoba.nr_indeksu << endl;
		if (nr_indeksu < temp->osoba.nr_indeksu)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

BSTNodeAVL * TreeAVL::removeBST(BSTNodeAVL * n)
{
	BSTNodeAVL  *tmp, *child, *prev;
	bool rotation;

	if (n->left != NULL && n->right != NULL)
	{
		child = removeBST(PredecessorBST(n));
		rotation = false;
	}
	else
	{
		if (n->left != NULL)
		{
			child = n->left;
			n->left = NULL;
		}
		else
		{
			child = n->right;
			n->right = NULL;
		}
		n->ratio = 0;
		rotation = true;
	}

	if (child != NULL)
	{
		child->top = n->top;
		child->left = n->left;
		if (child->left != NULL)  child->left->top = child;
		child->right = n->right;
		if (child->right != NULL)  child->right->top = child;
		child->ratio = n->ratio;
	}

	if (n->top != NULL) n->top->left == n ? n->top->left = child : n->top->right = child;
	else root = child;

	if (rotation == true)
	{
		prev = child;
		child = n->top;
		while (child != NULL)
		{
			if (child->ratio == 0)
			{
				child->left == prev ? child->ratio = -1 : child->ratio = 1;
				break;
			}
			else
			{
				if (((child->ratio == 1) && (child->left == prev)) || ((child->ratio == -1) && (child->right == prev)))
				{
					child->ratio = 0;
					prev = child;
					child = child->top;
				}
				else
				{
					child->left == prev ? tmp = child->right : tmp = child->left;
					if (tmp->ratio == 0)
					{
						child->ratio == 1 ? leftLeft(child) : rightRight(child);
						break;
					}
					else if (child->ratio == tmp->ratio)
					{
						child->ratio == 1 ? leftLeft(child) : rightRight(child);
						prev = tmp;
						child = tmp->top;
					}
					else
					{
						child->ratio == 1 ? leftRight(child) : rightLeft(child);
						prev = child->top;
						child = prev->top;
					}
				}
			}
		}
	}
	return n;
}

void TreeAVL::postorderDeletion(BSTNodeAVL * n)
{
	if (n)
	{
		postorderDeletion(n->left);
		postorderDeletion(n->right);
		if (n != root) delete n;
		else root = NULL;
	}

}

void TreeAVL::inorder(BSTNodeAVL * n)
{
	if (n)
	{
		inorder(n->left);
		cout << n->osoba.imie << " " << n->osoba.nazwisko << " " << n->osoba.nr_indeksu << endl;
		inorder(n->right);
	}
}
