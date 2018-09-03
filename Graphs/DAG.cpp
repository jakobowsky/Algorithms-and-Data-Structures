
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;


struct List
{
	List *next;
	int v;
};


struct Pair
{
	int a;
	int b;
};

int NumberOfEdges(int vertex)
{
	return int(0.3 * (vertex*vertex - vertex));
}

void generateDAG(int vertex,int numberOfFile)
{
	srand(time(NULL));
	ofstream output("Dag" + to_string(numberOfFile) + ".txt");
	int edges = NumberOfEdges(vertex);
	char ** tab = new char *[vertex];
	for (int i = 0; i < vertex; i++)
		tab[i] = new char[vertex];
	

	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < vertex; j++)
			tab[i][j] = 0;
	int it = 0;
	Pair * DAG = new Pair [edges];
	while (it < edges)
	{
		int i = rand() % vertex;
		int j = rand() % vertex;
		if (i < j && tab[i][j] == 0)
		{
			DAG[it].a = i;
			DAG[it].b = j;
			tab[i][j] = 1;
			it++;
		}
	}
	for (int i = 0; i < edges; i++)
		output << DAG[i].a << " " << DAG[i].b << endl;
	output.close();
	
}


bool DFSTopologicalSort(int *visited, List **tab, int v, vector <int>&stack)
{
	List *tmp;

	if (visited[v] == 1) //Sprawdzamy czy nie ma cyklu
	{
		return false;
	}
	if (visited[v] == 0) //jezeli wierzcholek jest nieodwiedzony to zaznaczmy na odwiedzonego
	{
		visited[v] = 1;
		for (tmp = tab[v]; tmp; tmp = tmp->next) //przegladamy jego wszystkich sasiadow rekurecyjnie
			if (!DFSTopologicalSort(visited, tab, tmp->v, stack)) return false; //reccuring
		visited[v] = 2; //przetwarzamy wierzcholek i umieszczamy na stosie
		stack.push_back(v);
	}
	return true;
}

double AdjacencyLists(int vertex, ifstream &input)
{

	int edges = NumberOfEdges(vertex);
	List ** tab;
	tab = new List *[vertex];
	List *p;
	List *r;
	for (int i = 0; i < vertex; i++)
	{
		tab[i] = NULL;
	}
	int v1, v2;
	for (int i = 0; i < edges-1; i++)
	{
		input >> v1 >> v2;
		p = new List;
		p->v = v2;
		p->next = tab[v1];
		tab[v1] = p;
	}

	// NotVisited = 0;
	// Visited = 1;
	// VisitedProcessed =2;
	int *visited = new int[vertex];
	for (int i = 0; i < vertex; i++) visited[i] = 0;
	vector <int> result;
	double timer = 0;
	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < vertex; i++)
	{
		if (visited[i] == 0)
		{
			if (!DFSTopologicalSort(visited, tab, i, result))
			{
				break;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	timer = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000;
	delete[] visited;

	for (int i = result.size()-1; i >= 0; i--) cout << result[i] << " ";

	
	cout << endl;

	//Wypisanie wartosc
	/*
	for (int i = 0; i < vertex; i++)
	{
	cout << "A[" << i << "] =";
	p = tab[i];
	while (p)
	{
	cout << p->v<<" ";
	p = p->next;
	}
	cout << endl;
	}
	*/

	//Delete list

	for (int i = 0; i < vertex; i++)
	{
		p = tab[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}
	delete[] tab;
	return  timer;	//Topological sort
	


}




double AdjacencyListsZALICZENIE(int vertex, ifstream &input)
{

	int edges = 12;
	List ** tab;
	tab = new List *[vertex];
	List *p;
	List *r;
	for (int i = 0; i < vertex; i++)
	{
		tab[i] = NULL;
	}
	int v1, v2;
	for (int i = 0; i < edges ; i++)
	{
		input >> v1 >> v2;
		v1--;
		v2--;
		p = new List;
		p->v = v2;
		p->next = tab[v1];
		tab[v1] = p;
	}

	// NotVisited = 0;
	// Visited = 1;
	// VisitedProcessed =2;
	int *visited = new int[vertex];
	for (int i = 0; i < vertex; i++) visited[i] = 0;
	vector <int> result;
	double timer = 0;
	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < vertex; i++)
	{
		if (visited[i] == 0)
		{
			if (!DFSTopologicalSort(visited, tab, i, result))
			{
				cout << "CYKLICZNY GRAF";
				break;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	timer = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000;
	delete[] visited;

	for (int i = result.size() - 1; i >= 0; i--) cout << result[i]+1 << " ";


	cout << endl;

	//Wypisanie wartosc
	
	for (int i = 0; i < vertex; i++)
	{
	cout << "A[" << i << "] =";
	p = tab[i];
	while (p)
	{
	cout << p->v<<" ";
	p = p->next;
	}
	cout << endl;
	}
	

	//Delete list

	for (int i = 0; i < vertex; i++)
	{
		p = tab[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}
	delete[] tab;
	return  timer;	//Topological sort



}



void CreateDAGs()
{
	int vertex = 100;
	for (int i = 1; i <= 15; i++)
	{
		generateDAG(vertex,i );
		cout << "Created Dag File: " << vertex << endl;
		vertex += 100;
	}
}

void TopologicalSortTime()
{
	ifstream file1;
	ofstream output("sortDAG.txt");
	int vertex = 100;
	for (int i = 1; i <= 15; i++)
	{
		file1.open("Dag" + to_string(i) + ".txt");
		output << vertex << "," << fixed << setprecision(7) << AdjacencyLists(vertex, file1) << endl;
		cout << vertex << "," << fixed << setprecision(7) << AdjacencyLists(vertex, file1) << endl;
		file1.close();
		vertex += 100;
	}
	output.close();
}


void Zaliczenie()
{
	ifstream file1;
	file1.open("dag2_test.txt"); // cale zmienic sorta
	double time;
	time = AdjacencyListsZALICZENIE(12, file1);
}

int main()
{
	//CreateDAGs();
	//TopologicalSortTime(); 
//	cout << NumberOfEdges(100);
	Zaliczenie();
	system("Pause");
	return 0;
}