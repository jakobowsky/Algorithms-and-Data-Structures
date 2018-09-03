
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

void inc_listAdams(int vertex, int edges)
{
	vector<int> *ZA = new vector <int>[vertex];
	ifstream wejscie;
	wejscie.open("dane.txt");
	ifstream searching;
	searching.open("szukanie.txt");
	ofstream wynik;
	wynik.open("szukanie_inc_list.txt", ios::app);
	for (int i = 0; i < edges; i++)
	{
		int a, b;
		wejscie >> a;
		wejscie >> b;
		if (a == b)
		{
			ZA[a].push_back(b);
		}
		else
		{
			ZA[a].push_back(b);
			ZA[b].push_back(a);
		}

	}

	int timer = 0;
	int vert1, vert2;
	int time = 0;
	for (int i = 0; i < edges; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		searching >> vert1;
		searching >> vert2;
		int cond = 1;
		for (int j = 0; j < vertex; j++)
		{
			for (vector<int>::iterator it = ZA[vert1].begin(); it != ZA[vert1].end(); ++it)
			{
				if (*it == vert2)
				{
					cond = 0;
					break;
				}
			}
			if (cond == 0) break;
		}
		auto stop = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
		timer = timer + time;
	}
	cout << "KONIEC3" << endl;
	timer = timer / edges;
	wynik << vertex << " " << timer << endl;


	/*
	for (int i = 0; i <vertex; i++)
	{
	cout << endl << "Sasiedzi wierzcholka " << i << ": ";
	for (vector<int>::iterator it = ZA[i].begin(); it != ZA[i].end(); ++it) cout << *it << ", ";
	}
	*/

}



struct Pair
{
	int a;
	int b;
};

struct Lista
{
	Lista *next;
	int v;
};

int NumberOfEdges(int vertex)
{
	return (int(((vertex*(vertex - 1) / 2) + vertex) * 0.6));
}


long double AdjacencyMatrix(int vertex,ifstream &input,ifstream &inputToFind)
{
	
	unsigned int edges = NumberOfEdges(vertex);
	
	//create empty matrix
	char **tab = new char*[vertex];
	for (int i = 0; i < vertex; i++)
	{
		tab[i] = new char[vertex];
	}

	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < vertex; j++)
			tab[i][j] = 0;
	int v1, v2;
	for (int i = 0; i < edges; i++)
	{
		input >> v1 >> v2;
		tab[v1][v2] = 1;
		tab[v2][v1] = 1;
	}

	//measure time
	long double  timer = 0;
	for (int i = 0; i < edges; i++)
	{
		inputToFind >> v1 >> v2;
		auto begin = std::chrono::high_resolution_clock::now();
		tab[v1][v2];
		auto end = std::chrono::high_resolution_clock::now();
		timer += long double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());

	}
	cout << "Amount of vertex: " << vertex << " time= " << fixed << setprecision(7) << timer / edges << endl;
	for (int i = 0; i < vertex; i++)
		delete[] tab[i];
	delete[] tab;
	return  timer / edges;

	//display matrix
	/*
	cout << endl;
	cout << " ";
	for (int i = 0; i < vertex; i++) cout << i;
	cout << endl;
	for (int i = 0; i < vertex; i++)
	{
		cout << i;
		for (int j = 0; j < vertex; j++) cout << (int)tab[i][j];
		cout << endl;
	}
	*/

	
	
}
void AdjacencyMatrixTime()
{
	ifstream file1;
	ifstream file2;
	ofstream output("adjmatrix.txt");
	int vertex = 50;
	for (int i = 1; i <= 15; i++)
	{
		file1.open("Graph" + to_string(i)+".txt");
		file2.open("Graph" + to_string(i)+"MIX.txt");
		output<<vertex<<","<<fixed << setprecision(7) << AdjacencyMatrix(vertex,file1,file2) << endl;
		file1.close();
		file2.close();
		vertex+=50;
	}
	output.close();
}

long double IncidenceMatrix(int vertex, ifstream &input, ifstream &inputToFind)
{

	int edges = NumberOfEdges(vertex);
	char **tab = new char*[vertex];
	for (int i = 0; i < vertex; i++)
	{
		tab[i] = new char[edges];
	}


	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < edges; j++)
			tab[i][j] = 0;
	int v1, v2;

	for (int i = 0; i < edges; i++)
	{
		input >> v1 >> v2;
		tab[v1][i] = 1;
		tab[v2][i] = 1;
	}

	//checking edges
	long double timer = 0;
	//int ile = 0;
	for (int i = 0; i < edges; i++)
	{
		inputToFind >> v1 >> v2;
		auto begin = std::chrono::high_resolution_clock::now();
		for (int j = 0; j < edges; j++)
		{
			if ((tab[v1][j] == tab[v2][j]) && (tab[v1][j] == 1)) //szukam kolumnami
			{
				//ile++;
				auto end = std::chrono::high_resolution_clock::now();
				timer += long double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
				break;
			}
		}
	}
	//cout << timer << endl;
	//cout <<"czas: "<< timer<<" wierzcholki: "<<vertex<<" krawedzie: "<<edges<<" znalezione: "<<ile << endl;
	cout << "Amount of vertex: " << vertex << " time= " << fixed << setprecision(7) << timer/edges << endl;

	/*
	//Display matrix
	ofstream test("lol.txt");
	cout << endl;
	test << " ";
	for (int i = 0; i < edges; i++) test << i;
	test << endl;
	for (int i = 0; i < vertex; i++)
	{
		test << i;
		for (int j = 0; j < edges; j++) test << (int)tab[i][j];
		test << endl;
	}

	*/

	for (int i = 0; i < vertex; i++)
		delete[] tab[i];
	delete[] tab;

	return  timer / edges;


	

	

}

void IncidenceMatrixTime()
{
	ifstream file1;
	ifstream file2;
	ofstream output("incmatrix.txt");
	int vertex = 50;
	for (int i = 1; i <= 15; i++)
	{
		file1.open("Graph" + to_string(i) + ".txt");
		file2.open("Graph" + to_string(i) + "MIX.txt");
		output << vertex << "," << fixed << setprecision(5) <<IncidenceMatrix(vertex, file1, file2) << endl;
		file1.close();
		file2.close();
		vertex += 50;
	}
	output.close();
}

long double EdgeList(int vertex, ifstream &input, ifstream &inputToFind)
{
	//vector<Pair> edgeList;
	int edges = NumberOfEdges(vertex);
	Pair *tab = new Pair [edges];
	Pair x;
	//load all vertexes
	for (int i = 0; i < edges; i++)
	{
		input >> x.a >> x.b;
		tab[i] = x;
		//edgeList.push_back(x);
	}

	//measure time
	long double timer = 0;
	for (int i = 0; i < edges; i++)
	{
		inputToFind >> x.a >> x.b;
		auto begin = std::chrono::high_resolution_clock::now();
		for (int j = 0; j < edges; j++)
		{
			if (((tab[j].a == x.a)&& (tab[j].b == x.b)) || ((tab[j].a == x.b) && (tab[j].b == x.a)))
			{
				auto end = std::chrono::high_resolution_clock::now();
				timer += long double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) ;
				
				break;
			}
				
		}
	}

	delete [] tab;
	cout << "Amount of vertex: " << vertex << " time= " << fixed << setprecision(7) << timer / edges << endl;
	return timer / edges;

}
void EdgeListTime()
{
	ifstream file1;
	ifstream file2;
	ofstream output("edgelist.txt");
	int vertex = 50;
	for (int i = 1; i <= 15; i++)
	{
		file1.open("Graph" + to_string(i) + ".txt");
		file2.open("Graph" + to_string(i) + "MIX.txt");
		output << vertex << "," << fixed << setprecision(5) << EdgeList(vertex, file1, file2) << endl;
		file1.close();
		file2.close();
		vertex += 50;
	}
	output.close();
}


long double AdjacencyLists(int vertex, ifstream &input, ifstream &inputToFind)
{
	
	int edges = NumberOfEdges(vertex);
	Lista ** tab;
	tab = new Lista *[vertex];
	Lista *p;
	Lista *r;
	for (int i = 0; i < vertex; i++)
	{
		tab[i] = NULL;
	}
	int v1, v2;
	for (int i = 0; i < edges; i++)
	{
		input >> v1 >> v2;
		//first direction
		if (v1 == v2)
		{
			p = new Lista;
			p->v = v2;
			p->next = tab[v1];
			tab[v1] = p;
		}
		else
		{
			//first
			p = new Lista;
			p->v = v2;
			p->next = tab[v1];
			tab[v1] = p;
			//second direction
			r = new Lista;
			r->v = v1;
			r->next = tab[v2];
			tab[v2] = r;
		}
		
	}
	long double timer = 0;
	//Searching
	
	for (int i = 0; i < edges; i++)
	{
		inputToFind >> v1 >> v2;
		p = tab[v1];
		auto begin = std::chrono::high_resolution_clock::now();
		
		while (p->next != NULL)
		{
			p = p->next;
			if (p->v == v2)
			{
				auto end = std::chrono::high_resolution_clock::now();
				timer += long double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()); //10^-6 sekundy
				break;
			}
		}
	}
	cout << "Amount of vertex: " << vertex << " time= " << fixed << setprecision(7) << timer / edges << endl;
	


	cout << endl;

	//Wypisanie wartosc
	/*
	for (int i = 0; i < vertex; i++)
	{
		cout << "A[" << i << "] =";
		p = tab[i];
		while (p)
		{
			cout << p->v << " ";
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
	return timer / edges;
	

	
	


}
void AdjacencyListsTime()
{
	ifstream file1;
	ifstream file2;
	ofstream output("adjacencylists.txt");
	int vertex = 50;
	for (int i = 1; i <= 15; i++)
	{
		file1.open("Graph" + to_string(i) + ".txt");
		file2.open("Graph" + to_string(i) + "MIX.txt");
		output << vertex << "," << fixed << setprecision(5) <<AdjacencyLists(vertex, file1, file2) << endl;
		file1.close();
		file2.close();
		vertex += 50;
	}
	output.close();
}


int main()
{

	//AdjacencyMatrixTime();
	//cout << "IncidenceMatrix: " << endl;
	//IncidenceMatrixTime();
	//cout << endl;
	//cout << "edgeList:" << endl;
	//EdgeListTime();
	//AdjacencyListsTime(); //mikro or normal


	//ifstream file("Test.txt");
	//AdjacencyLists(4, file, file);

	system("Pause");
	return 0;
}

