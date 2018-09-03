#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <chrono>
#include <random>
using namespace std;



clock_t starcik, stop, stop2, start;
float czas;
int s, y; //zmienne do Hamiltona s- wierzcholek startowy / y - zmienna do wpisywania wiercholkow cyklu do tablicy z cyklem Hamiltona

void Euler(int vertical,int node, stack<int>&temp, vector <int> &solution, bool **matrix)
{
	temp.push(node);
	for (int i = 0; i < vertical; i++)
	{
		if (matrix[node][i] == true)
		{
			matrix[node][i] = matrix[i][node] = false;
			Euler(vertical,i,temp,solution,matrix);
		}
	}
	solution.push_back(node);
	temp.pop();
}

void generate(int vertex, float sat,bool**Adj)
{
	vector <int> nodes;
	vector <int> cycle;
	int tmp;
	int nodeA, nodeB, nodeC;
	for (int i = 0; i < vertex; i++)
		nodes.push_back(i);
	for (int i = 0; i < vertex; i++)
	{
		tmp = rand() % nodes.size();
		cycle.push_back(nodes[tmp]);
		nodes.erase(nodes.begin() + tmp);
	}

	for (int i = 0; i < vertex - 1; i++)
	{
		Adj[cycle[i]][cycle[i + 1]] = Adj[cycle[i + 1]][cycle[i]] = true;
	}

	Adj[cycle[0]][cycle[cycle.size() - 1]] = Adj[cycle[cycle.size() - 1]][cycle[0]] = true;

	int edges = (((vertex * (vertex - 1)) / 2) * sat);
	
	edges -= vertex;

	for (int i = 0; i < edges; i += 3)
	{
		do
		{
			nodeA = rand() % vertex;
			nodeB = rand() % vertex;
			nodeC = rand() % vertex;
		} while (nodeA == nodeB || nodeA == nodeC || nodeB == nodeC ||
			Adj[nodeA][nodeB] == true || Adj[nodeA][nodeC] == true || Adj[nodeB][nodeC] == true);


		Adj[nodeA][nodeB] = Adj[nodeB][nodeA] = true;
		Adj[nodeA][nodeC] = Adj[nodeC][nodeA] = true;
		Adj[nodeB][nodeC] = Adj[nodeC][nodeB] = true;

	}
	/*
	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < vertex; j++)
			if (Adj[i][j] == true)
				cout << i << " " << j << "\n";
	*/
} //generator do Eulera

void generowanie(int n, int kr)
{
	//if (kr % 2 == 1)
	//	kr++;

	//TWORZE MACIERZ N*N
	int **tab2D = new int*[n];
	for (int m = 0; m < n; m++) {
		tab2D[m] = new int[n];
	}
	//ZERUJE MACIERZ
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tab2D[i][j] = 0;
		}
	};
	srand(time(NULL));
	int indeks1, indeks2;
	//TWORZE POLACZENIE KOLEJNEGO PUNKTU Z WCZESNIEJSZYMI
	tab2D[0][1] = tab2D[1][0] = 1;

	for (int k = 2; k < n; k++)
	{
		indeks1 = rand() % k;
		tab2D[k][indeks1] = tab2D[indeks1][k] = 1;
		//cout << indeks1 << "\t";
	};
	// UZUPELNIAL KRAWEDZIE DO WYMAGANEJ ILOSCI
	for (int kc = 0; kc <= (kr - n); kc++)
	{
		bool prawda = true;
		while (prawda)
		{
			indeks1 = rand() % n;
			indeks2 = rand() % n;
			if (tab2D[indeks1][indeks2] == 0 && indeks1 != indeks2)
			{
				prawda = false;
			}
		}
		tab2D[indeks1][indeks2] = tab2D[indeks2][indeks1] = 1;
	};

	//// LACZENIE NIEPARZYSTYCH WIERZCHOLKOW
	//for (int i = 0; i < n; ++iszukanie_cyklu_eulera)
	//{
	//	int temp = 0;
	//	for (int j = 0; j < n; ++j)
	//	{
	//		if (tab2D[i][j] == 1)
	//			temp += 1;
	//	}
	//	cout << i << "\t parzystosc:" << temp << "\n";
	//};

	//TWORZE LISTE OZNACZAJACA PARZYSTOSC
	int *lista = new int[n];

	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		for (int j = 0; j < n; j++)
		{
			if (tab2D[i][j] == 1)
				temp += 1;
		}
		lista[i] = temp;
		if (temp % 2 == 1) { lista[i] = temp; }
	};
	for (int a = 0; a< n; a++)
		//cout << lista[a] << "\t";
		//cout << "\n";

		//SZUKAMY NODE KTORE MAJA NIEPARZYSTOSC

		for (int z = 0; z < n; z++)
		{
			int coute = 0;
			int coute2 = n - 1;
			int temp1 = -1;
			int temp2 = -1;

			//SZUKAMY OD POCZATKU PIERWSZEGO
			while (temp1 == -1 && coute < n)
			{
				if (lista[coute] % 2 == 1)
				{
					temp1 = coute;
					//cout << "temp1 " << temp1 << "\t";
				}
				coute++;
			}
			//SZUKAMY OD KONCA DRUGIEGO
			while (temp2 == -1 && coute2 >= 0)
			{
				if (lista[coute2] % 2 == 1 && coute2 != temp1)
				{
					temp2 = coute2;
					//cout << "temp2 " << temp2 << "\t";
				}
				coute2--;
			}
			//cout << "\n";

			//JEZELI NIE ISTNIEJE KRAWEDZ MIEDZY NIMY TO TWORZYMY
			if (temp1 >= 0 && temp2 >= 0 && tab2D[temp1][temp2] == 0)
			{
				//cout << " tworzymy nowy \n";
				tab2D[temp1][temp2] = tab2D[temp2][temp1] = 1;
				lista[temp1] = 0;
				lista[temp2] = 0;
				kr++;
			}
			//JEZELI ISTNIEJE KRAWEDZ MIEDZY NIMY TO USUWAMY
			else if (temp1 >= 0 && temp2 >= 0 && tab2D[temp1][temp2] == 1)
			{
				if (lista[temp1] == 1 || lista[temp2] == 1)
				{
					//cout << "Blad!!!" << endl;
					system("pause");
				}
				//cout << " usuwamy stary \n";
				tab2D[temp1][temp2] = tab2D[temp2][temp1] = 0;
				lista[temp1] = 0;
				lista[temp2] = 0;
				kr--;
			}
			//JEZELI CALA LISTA SPRAWDZAJACA PARZYSTOSC JEST WYZEROWANA PRZERYWAMY FUNKCJE
			int sum = 0;
			for (int f = 0; f < n; f++)
			{
				if (lista[f] == 1)
					sum++;
			}
			if (sum == 0)
				break;
		}



	//cout << "\n";
	for (int i = 0; i < n; ++i)
	{
		int temp = 0;
		for (int j = 0; j < n; ++j)
		{
			if (tab2D[i][j] == 1)
				temp += 1;
		}
		//cout << i << "\t parzystosc:" << temp << "\n";
	};
	//TWORZYMY PLIK ZAPISUJAC GORNA CZĘŚĆ MACIERZY
	fstream plik;
	plik.open("wiwiwi.txt", ios::out);
	plik << n << " " << kr << endl;
	for (int x = 0; x < n; x++)
	{
		for (int y = x + 1; y < n; y++)
		{
			if (tab2D[x][y] == 1)
			{
				plik << x << " " << y << endl;
			}
		}
	}

}

void Task1()
{
	float saturation[6];
	saturation[0] = 0.2;
	saturation[1] = 0.3;
	saturation[2] = 0.4;
	saturation[3] = 0.6;
	saturation[4] = 0.8;
	saturation[5] = 0.9;

	for (int i = 0; i < 6; i++)
	{
		cout << "Saturation: " << saturation[i] << endl;
		ofstream out("EulerCycle" + to_string(i) + ".txt");
		out << "Vertex, Time" << endl;
		int vertex = 50;
		for (int j = 1; j <= 15; j++)
		{
			vector<int> solution;
			stack<int> temp;

			//init matrix for graph
			bool **matrix = new bool *[vertex];
			for (int i1 = 0; i1 < vertex; i1++) matrix[i1] = new bool[vertex];

			for (int i1 = 0; i1 < vertex; i1++)
				for (int i2 = 0; i2 < vertex; i2++)
					matrix[i1][i2] = false;

			generate(vertex, saturation[i], matrix);

			double timer = 0;
			auto begin = std::chrono::high_resolution_clock::now();
			Euler(vertex, 0, temp, solution, matrix);
			auto end = std::chrono::high_resolution_clock::now();
			timer = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000;
			out << vertex << "," << timer << endl;
			cout << vertex << "," << timer << endl;

			//free memory//////////////
			for (int i1 = 0; i1 < vertex; i1++)
				delete[] matrix[i1];
			delete[] matrix;

			solution.clear();
			vertex += 50;

		}
		out.close();

	}


}


void dfs(int n, int v, bool* visited, int **NM) { //analizuj v

	visited[v] = 1;
	//	cout << v << "-> ";
	for (int x = 0; x<n; x++) 		// dla wszystkich wierzcho³kow x
		if (NM[v][x] && !visited[x]) 	// jesli istnieje krawedz v-x i x nie byl odwiedzony
			dfs(n, x, visited, NM); // analizuj x

}


void generuj(int n, int m, int **NM) {

	// tworzenie losowego grafu nieskierowanego o m krawêdziach [macierz s¹siedztwa]


	int i = m, x, y;
	while (i) {
		y = rand() % n; // losowy wierzcho³ek (od 0 do n-1)
		x = rand() % n;
		if (NM[x][y] != 1 && x != y) { // bez petli w³asnych
			NM[x][y] = NM[y][x] = 1;
			i--;
		}
	}


	// sprawdzanie spojnosci grafu

	bool *visited = new bool[n];
	bool all_visited = 1;
	dfs(n, 0, visited, NM);

	for (x = 0; x<n - 1; x++) if (!visited[x]) { all_visited = 0; break; }

	if (all_visited); //printf("graf spojny\n");
	else {
		//printf("graf niespojny\nponowne generowanie: ");
		generuj(n, m, NM);
	}

}


int nr = 0, CH = 0, found = 0;	// dlugosc aktualnej sciezki, liczba cykli w grafie, flaga znalezienia cyklu

void Hamilton(int n, int v, int* path, bool* visited, int** NM, clock_t start, double &czasik) {

	if (found) { return; }
	stop2 = clock();
	czasik = (double)(stop2 - start);
	if (czasik >= 300000) {/* cout << "brejk, czas wynosi: " << czasik<<endl;*/ found = 2; return; } //jesli found =2 to byl brejk bo za dlugo dziala program a jesli found = 1 to cykl znaleziony

	path[nr++] = v;					// dopisujemy wierzcholek do sciezki

	if (nr != n) {					// jesli sciezka jest jeszcze niepelna
		visited[v] = true;
		for (int x = 0; x<n; x++) 		// dla wszystkich wierzcho³kow x
			if (NM[v][x] && !visited[x]) 	// jesli istnieje krawedz v-x i x nie byl odwiedzony
				Hamilton(n, x, path, visited, NM, start, czasik); // przejdz do x
		visited[v] = false;
	}


	else if (NM[v][0]) {  				// jesli scie¿ka zawiera juz wszystkie wierzcho³ki i jest cyklem

										//for (int z = 0; z<n; z++)  cout << path[z] << " "; // wypisz ja
		if (!found) { found = 1; stop2 = clock(); czasik = (double)(stop2 - start);/* cout <<"Czas wynosi: "<< czasik << endl;*/  return; } 	// po znalezieniu pierwszego cyklu wypisz czas
		CH++;				// liczba cykli++
	}


	nr--; 						// usuwamy wierzcho³ek ze scie¿ki

}


void Task2()
{
	float saturation[6];
	saturation[0] = 0.2;
	saturation[1] = 0.3;
	saturation[2] = 0.4;
	saturation[3] = 0.6;
	saturation[4] = 0.8;
	saturation[5] = 0.95;
	double suma = 0;
	for (int i = 0; i < 6; i++)
	{
		cout << "Saturation: " << saturation[i] << endl;
		ofstream out("HamiltonCycle" + to_string(i) + ".txt");
		out << "Vertex, Time" << endl;
		int vertex = 100;
		for (int j = 1; j <= 15; j++)
		{
			int edges = vertex*(vertex - 1)*0.5*saturation[i];
			double timer = 0;
			for (int k = 0; k < 10;k++)
			{
				
				int **NM = new int *[vertex];
				for (int x = 0; x < vertex; x++) NM[x] = new int[vertex];
				for (int x = 0; x < vertex; x++)
					for (int y = 0; y < vertex; y++) NM[x][y] = 0;

				generuj(vertex,edges,NM);

				bool *visited = new bool[vertex];
				int *path = new int[vertex];
				for (int x = 0; x < vertex; x++) visited[x] = false;

				starcik = clock();
				nr = 0; CH = 0; found = 0;

				Hamilton(vertex, 0, path, visited, NM, starcik, timer);
				cout << "K: " << k <<"czas: "<<timer<<endl;
				delete[] visited;
				delete[] path;
				suma = suma + timer;
			
			}
			suma = (double)(suma) / 10;
			out << vertex << "," << suma<< endl;
			cout << vertex << " vertexow, czas:  " << suma << endl;

			vertex += 50;
			suma = 0;
		}
		out.close();

	}


}


/*
void zaliczenie()
{

	
	int tab[4];
	tab[0] = 100;
	tab[1] = 200;
	tab[2] = 400;
	tab[3] = 500;

	float saturation[4];
	saturation[0] = 0.3;
	saturation[1] = 0.7;
	saturation[2] = 0.95;
	saturation[3] = 0.99;

	//cykl eulera
	for (int i = 0; i < 4; i++) //nasycenie
	{
		for (int j = 0; j < 4; j++) //wierzcholki
		{
			ifstream plik("wiwiwi.txt");
			int x;
			plik >> x >> x;

			int vertex = tab[j];
			int edges = vertex*(vertex - 1)*0.5*saturation[i];
			
			vector<int> solution;
			stack<int> temp;

			generowanie(vertex, edges);

			//init matrix for graph
			bool **matrix = new bool *[vertex];
			for (int i1 = 0; i1 < vertex; i1++) matrix[i1] = new bool[vertex];

			for (int i1 = 0; i1 < vertex; i1++)
				for (int i2 = 0; i2 < vertex; i2++)
				{
					int wierz1, wierz2;
					plik >> wierz1 >> wierz2;
					matrix[wierz1][wierz2] = true;
					matrix[wierz2][wierz1] = true;
				}

		
			double timer = 0;
			auto begin = std::chrono::high_resolution_clock::now();
			Euler(vertex, 0, temp, solution, matrix);
			auto end = std::chrono::high_resolution_clock::now();
			timer = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000;
			//out << vertex << "," << timer << endl;
			cout << vertex << "," << timer << endl;

			//free memory//////////////
			for (int i1 = 0; i1 < vertex; i1++)
				delete[] matrix[i1];
			delete[] matrix;

			plik.close();
			
		}
	}

}
*/

void Zaliczenie2EULER()
{

	



	float saturation[4];
	saturation[0] = 0.3;
	saturation[1] = 0.7;
	saturation[2] = 0.85;
	saturation[3] = 0.9;
	











	float saturaton[4];
	saturaton[0] = 0.3;
	saturaton[1] = 0.7;
	saturaton[2] = 0.85;
	saturaton[3] = 0.95;


	int vertex1[4];
	vertex1[0] = 100;
	vertex1[1] = 200;
	vertex1[2] = 400;
	vertex1[3] = 500;


	for (int i = 0; i < 4; i++)
	{
		cout << "Saturation: " << saturaton[i] << endl;
		
		for (int j = 0; j < 4; j++)
		{
			int vertex = vertex1[j];
			vector<int> solution;
			stack<int> temp;

			//init matrix for graph
			bool **matrix = new bool *[vertex];
			for (int i1 = 0; i1 < vertex; i1++) matrix[i1] = new bool[vertex];

			for (int i1 = 0; i1 < vertex; i1++)
				for (int i2 = 0; i2 < vertex; i2++)
					matrix[i1][i2] = false;

			generate(vertex, saturation[i], matrix);

			double timer = 0;
			auto begin = std::chrono::high_resolution_clock::now();
			Euler(vertex, 0, temp, solution, matrix);
			auto end = std::chrono::high_resolution_clock::now();
			timer = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000;
			//out << vertex << "," << timer << endl;
			cout << vertex << "," << timer << endl;

			//free memory//////////////
			for (int i1 = 0; i1 < vertex; i1++)
				delete[] matrix[i1];
			delete[] matrix;

			solution.clear();

		}
		

	}


}

void Zaliczenie2HAMILTON()
{
	float saturation[4];
	saturation[0] = 0.3;
	saturation[1] = 0.7;
	saturation[2] = 0.9;
	saturation[3] = 0.95;

	int vertex1[4];
	vertex1[0] = 100;
	vertex1[1] = 200;
	vertex1[2] = 400;
	vertex1[3] = 500;
	double suma = 0;
	ofstream out("HamiltonZaliczenie.txt");
	for (int i = 0; i < 4; i++)
	{
		cout << "Saturation: " << saturation[i] << endl;
		out << "Saturation: " << saturation[i] << endl;
		
		for (int j = 0; j <4; j++)
		{
			int vertex = vertex1[j];
			int edges = vertex*(vertex - 1)*0.5*saturation[i];
			double timer = 0;
			for (int k = 0; k < 10; k++)
			{

				int **NM = new int *[vertex];
				for (int x = 0; x < vertex; x++) NM[x] = new int[vertex];
				for (int x = 0; x < vertex; x++)
					for (int y = 0; y < vertex; y++) NM[x][y] = 0;

				generuj(vertex, edges, NM);

				bool *visited = new bool[vertex];
				int *path = new int[vertex];
				for (int x = 0; x < vertex; x++) visited[x] = false;

				starcik = clock();
				nr = 0; CH = 0; found = 0;

				Hamilton(vertex, 0, path, visited, NM, starcik, timer);
				cout << "K: " << k << " czas: " << timer << endl;
				delete[] visited;
				delete[] path;
				suma = suma + timer;

			}
			suma = (double)(suma) / 10;
			cout << vertex << " vertexow, czas:  " << suma << endl;
			out << vertex << " vertexow, czas:  " << suma << endl;
			suma = 0;
		}
		

	}
}




int main()
{
	/*
	int vertex = 700;
	bool **matrix = new bool*[vertex];
	for (int i = 0; i < vertex; i++) matrix[i] = new bool[vertex];

	for (int i = 0; i < vertex; i++)
		for (int j = 0; j < vertex; j++)
			matrix[i][j] = false;
	bool *visited = new bool [vertex];
	int edges = (int)(0.4 * (vertex*(vertex - 1) / 2));
	//cout << edges << endl;
	generate(vertex, 0.4, matrix);

	

	std::vector<int> solution;
	std::stack<int> temp;
	Hamilton(false,visited, vertex, 0, matrix, temp, solution);
	//Euler(vertex, 0, temp, solution, matrix);
	solution.clear();
	cout << solution.size();
	*/

	//Task1();
	
	//Task2();

	//zaliczenie();
	//Zaliczenie2();
	//Zaliczenie2EULER();
	//Zaliczenie2HAMILTON();
	

	system("pause");


}