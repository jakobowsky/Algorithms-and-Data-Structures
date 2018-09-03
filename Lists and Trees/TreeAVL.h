#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "List.h"

using namespace std;

struct BSTNodeAVL
{
	student osoba;
	BSTNodeAVL *left, *right, *top;
	int ratio;
};


class TreeAVL
{
public:
	BSTNodeAVL * root;
	TreeAVL();
	~TreeAVL();
	void leftLeft(BSTNodeAVL *n);
	void rightRight(BSTNodeAVL *n);
	void rightLeft(BSTNodeAVL *n);
	void leftRight(BSTNodeAVL *n);
	BSTNodeAVL * MaxBST(BSTNodeAVL *n);
	BSTNodeAVL * PredecessorBST(BSTNodeAVL *n);
	void insertBST(string imie, string nazwisko, unsigned int nr_indeksu);
	BSTNodeAVL * searchForStudent(int nr_indeksu);
	BSTNodeAVL * removeBST(BSTNodeAVL * n);
	void postorderDeletion(BSTNodeAVL *n);
	void inorder(BSTNodeAVL *n);
};

