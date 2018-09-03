#pragma once
#include <iostream>
#include <string>
#include "List.h"
using namespace std;


struct BSTNode
{
	student osoba;
	BSTNode* Left;
	BSTNode* Right;
	BSTNode* Up;
};


class Tree
{
public:

	BSTNode * root;
	Tree();
	~Tree();
	void insertStudent(string imie, string nazwisko, unsigned int nr_indeksu);
	void deleteStudent(unsigned int nr_indeksu); //do zrobienia
	void deleteTree(BSTNode *root);
	void inorder(BSTNode *n);
	void preorder(BSTNode *n);
	void postorder(BSTNode *n);
	BSTNode * searchForStudent(int nr_indeksu);
	BSTNode * minBST(BSTNode *p);
	BSTNode * succesor(BSTNode *p);
	void rotL(BSTNode *A);
	void rotR(BSTNode *A);
	int log2BST(int x);
	void rebalanceTree();
	//void wyswietlDrzewo(string sp, string sn, BSTNode * v);
	

};

