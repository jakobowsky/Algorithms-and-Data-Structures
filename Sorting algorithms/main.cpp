//#pragma comment(linker, "/STACK:367772160")
//#pragma GCC optimize ("-O3")
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

void BubbleSort(int *tab, int n)
{

	bool swaping = 1;
	for (int i = 0; i < n; i++)
	{
		bool swaping = 1;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (tab[j] > tab[j + 1]) { swap(tab[j], tab[j + 1]); swaping = 0; }
		}
		if (swaping) break;
	}

}


void Heapify(int *tab, int n, int i)
{
	int naj = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && tab[l] > tab[naj])
		naj = l;

	if (r < n && tab[r] > tab[naj])
		naj = r;

	if (naj != i)
	{
		int pom = tab[naj];
		tab[naj] = tab[i];
		tab[i] = pom;
		Heapify(tab, n, naj);
	}
}
void HeapSort(int *tab, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(tab, n, i); //pierwsza budowa kopca

	for (int i = n - 1; i >= 0; i--)
	{
		int pom = tab[0]; //sciaganie maxa i odbudowa kopca
		tab[0] = tab[i];
		tab[i] = pom;
		Heapify(tab, i, 0);
	}
}


void CountingSort(int * tab, int n)
{
	//int n = 10;
	//int * tab = new int [n];
	//for (int i = 0; i < n; i++) cin >> tab[i];
	int k = tab[0];
	for (int i = 1; i < n; i++)
	{
		if (tab[i] > k) k = tab[i];

	}


	// for (int i = 0; i < 10; i++) cout << tab[i] << " ";
	int * tab2 = new int[k + 1];
	int * sortedTab = new int[n];
	for (int i = 0; i <= k; i++) tab2[i] = 0;
	for (int i = 0; i < n; i++) tab2[tab[i]] ++;

	//for (int i = 0; i <= k; i++) cout << tab2[i] << " ";
	//cout << endl;

	for (int i = 1; i <= k; i++) tab2[i] += tab2[i - 1]; //stan licznika okresla ostatnia pozycje w zbiorze uporzadkowanym, na ktorej nalezy umiesic wartosc rowna numerowi licznika
	//for (int i = 0; i <= k; i++) cout << tab2[i] << " ";
	//cout << endl;

	for (int i = 0; i < n; i++)
	{
		sortedTab[--tab2[tab[i]]] = tab[i]; //przepisywanie do tablicy , zmniejszamy ilosc w tab2 po uzyciu elementu
	}

	for (int i = 0; i < n; i++) tab[i] = sortedTab[i];
	//for (int i = 0; i < n; i++) cout << tab[i] << " ";


}

void ShellSort(int *tab, int n)
{

	int h = 1;
	while (h <= n) h = 3 * h + 1;
	h = h / 9;
	if (h == 0) h = 1;


	while (h > 0) //sorotwanie jak insert sort
	{
		for (int i = h; i < n; i++)
		{
			int k = tab[i];
			int j = i - h;
			while ((j >= 0) && (tab[j] > k))
			{
				tab[j + h] = tab[j];
				tab[j] = k;
				j = j - h;
			}
		}
		h = h / 3;
	}



}

void QuickSortAlg(int left, int right, int *tab)
{

	for (int i = 0; i <= 6; i++) cout << tab[i] << " ";
	cout << "  L: " << left << " R: " << right << " pivot: ";
	if (right <= left) return;
	int i = left - 1 ;
	int j = right + 1 ;
	int pivot = tab[(left + right) / 2];
	cout << pivot << "    ";
	
	while (1)
	{
		
		while (pivot > tab[++i]); //wszystkie elementy <= na lewo a wszystkie >= na prawo
		while (pivot < tab[--j]);
		if (i <= j)
		{
			
			swap(tab[i], tab[j]);
		}
		else break;
	}
	
	cout << " L: " << i << " R: " << j<< "  ";
	cout << "/";
	for (int i = 0; i <= 6; i++) cout << tab[i] << " ";
	cout << endl;
	if (j > left) QuickSortAlg(left, j, tab);
	if (i < right) QuickSortAlg(i, right, tab);
}

void Merge(int *tabOrg, int *tabNew, int iLeft, int iMiddle, int iRight)
{
	int i = iLeft;
	int j = iMiddle + 1;
	int index = iLeft;
	while (i <= iMiddle && j <= iRight)
	{
		if (tabOrg[i] <= tabOrg[j])	tabNew[index++] = tabOrg[i++];
		else tabNew[index++] = tabOrg[j++];
	}
	while (i <= iMiddle) tabNew[index++] = tabOrg[i++];
	while (j <= iRight) tabNew[index++] = tabOrg[j++];

	for (int iNew = iLeft; iNew <= iRight; iNew++) tabOrg[iNew] = tabNew[iNew];

}

void MergeSortAlg(int *tabOrg, int *tabNew, int iLeft, int iRight)
{
	if (iLeft >= iRight) return;
	int iMiddle = (iLeft + iRight) / 2;
	MergeSortAlg(tabOrg, tabNew, iLeft, iMiddle);
	MergeSortAlg(tabOrg, tabNew, iMiddle + 1, iRight);
	Merge(tabOrg, tabNew, iLeft, iMiddle, iRight);
}

void Zad1()
{
	string name0 = "BubbleSort.csv";
	string name1 = "HeapSort.csv";
	string name2 = "CountingSort.csv";
	string name3 = "ShellSort.csv";
	string names[4] = { name0,name1,name2,name3 };
	for (int m = 0; m < 4; m++)
	{
		int i = 1;
		int n = 10000;
		srand(time(NULL));
		fstream out;
		out.open(names[m], fstream::out);
		out << "NumberOfElemements,time\n";
		cout << m << " now: " << endl;
		while (i++ <= 20)
		{
			int * tab = new int[n + 1];
			for (int j = 0; j < n; j++)
			{
				tab[j] = rand() % 1000;
				//cout << tab[j] << " ";
			}
			//BubbleSort(tab, n);
			//HeapSort(tab, n);
			//CountingSort(tab, n);
			//ShellSort(tab, n);
			auto begin = std::chrono::high_resolution_clock::now();
			if (m == 0) BubbleSort(tab, n);
			else if (m == 1) HeapSort(tab, n);
			else if (m == 2) CountingSort(tab, n);
			else if (m == 3) ShellSort(tab, n);
			auto end = std::chrono::high_resolution_clock::now();
			out << n << "," << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "\n";
			/*
			int start = clock();
			int stop = clock();
			double time = double((stop - start)) / CLOCKS_PER_SEC;
			*/
			//out << n << "," << time << "\n";
			cout << n << " Succes" << endl;
			delete[] tab;
			/* SPECIAL CASE
			if (m ==0) n += 1000;
			else n += 100000;
			*/
			n += 7500;
		}
		out.close();

	}



}

void Elements(int number, int *tab, int n)
{
	srand(time(NULL));

	switch (number)
	{
	case 1: // random numbers
	{
		for (int i = 0; i < n; i++) tab[i] = rand() % 1000;
		break;
	}
	case 2: //constant numbers
	{
		for (int i = 0; i < n; i++) tab[i] = 1;
		break;
	}
	case 3: // increasing numbers
	{
		for (int i = 0; i < n; i++) tab[i] = i;
		break;
	}
	case 4: //decreasing numbers
	{

		for (int i = 0; i < n; i++) tab[i] = n - i - 1;
		break;

	}
	case 5: // increase and decrease
	{
		for (int i = 0; i < n / 2; i++) tab[i] = i;
		int k = n / 2;
		for (int i = n / 2; i < n; i++) tab[i] = k--;
		break;
	}
	case 6: //decrase and increase
	{
		int k = n - 1;
		for (int i = 0; i < n / 2; i++) tab[i] = k--;
		for (int i = n / 2; i < n; i++) tab[i] = k++;
		break;
	}


	default:
	{
		cout << "Wrong number";
		break;
	}
	}

}

void TestEl()
{
	//int i = 1;
	int n = 7500;
	int *tab = new int[n + 1];
	int *tabNew = new int[n + 1];
	for (int j = 1; j <= 6; j++)
	{
		cout << j << " typ " << endl;
		int *tab = new int[n + 1];
		Elements(j, tab, n);
		//MergeSortAlg(tab,tabNew,0,n);
		//QuickSortAlg(0, n, tab);
		//CountingSort(tab, n);
		delete[] tab;
	}

}

void TestTime()
{
	int *tab = new int[5001];
	Elements(1, tab, 5000);
	auto begin = std::chrono::high_resolution_clock::now();
	HeapSort(tab, 5000);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
}

void Zad2()
{
	string name0 = "QuickSort";
	string name1 = "HeapSort";
	string name2 = "MergeSort";
	string endName = ".csv";
	string names[3] = { name0,name1,name2 };
	for (int m = 0; m < 3; m++) // choose type of sort
	{
		cout << names[m] << " :" << endl;
		for (int k = 1; k <= 6; k++) //choose type of elements
		{
			int n = 10000;

			cout << "type of numbers: " << k << endl;
			// Elements -> k ->  1 - 6
			int i = 1;

			fstream out;
			out.open(names[m] + to_string(k) + endName, fstream::out);
			out << "NumberOfElemements,time\n";
			while (i++ <= 15)
			{

				int * tab = new int[n + 1];
				int * tabMerge = new int[n + 1];
				Elements(k, tab, n); // create chosen type of elements
				auto begin = std::chrono::high_resolution_clock::now();
				if (m == 0) QuickSortAlg(0, n, tab-1);
				else if (m == 1) HeapSort(tab, n);
				else if (m == 2) MergeSortAlg(tab, tabMerge, 0, n);
				auto end = std::chrono::high_resolution_clock::now();
				out << n << "," << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "\n";
				cout << n << " Succes" << endl;
				delete[] tab;
				delete[] tabMerge;
				if (m == 0) n += 7500;
				else n += 100000;

			}
			out.close();

		}
	}

}


void Zad1Zdawanie()
{

	int * tab = new int[101];
	// LOSOWO
	Elements(1, tab, 100);
	cout << " L O S O W O" << endl;
	for (int i = 0; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	///////////////
	Elements(1, tab, 100);
	BubbleSort(tab, 100);
	cout << "Bubble Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	////////////
	Elements(1, tab, 101);
	HeapSort(tab, 100);
	cout << "Heap Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(1, tab, 101);
	CountingSort(tab, 100);
	cout << "Counting Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(1, tab, 101);
	ShellSort(tab, 100);
	cout << "Shell Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(1, tab, 101);
	QuickSortAlg(0, 100, tab);
	cout << "Quick Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(1, tab, 101);
	int * tab2 = new int[101];
	MergeSortAlg(tab, tab2, 0, 100);
	cout << "Merge Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	
	//A ksztal
	cout << " A KSZTALT" << endl;
	Elements(5, tab, 100);
	for (int i = 0; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	///////////////
	Elements(5, tab, 100);
	BubbleSort(tab, 100);
	cout << "Bubble Sort: " << endl;
	for (int i = 0; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	////////////
	Elements(5, tab, 101);
	HeapSort(tab, 100);
	cout << "Heap Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(5, tab, 101);
	CountingSort(tab, 100);
	cout << "Counting Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(5, tab, 101);
	ShellSort(tab, 100);
	cout << "Shell Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(5, tab, 101);
	QuickSortAlg(0, 100, tab);
	cout << "Quick Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(5, tab, 101);
	int * tab3 = new int[101];
	MergeSortAlg(tab, tab3, 0, 100);
	cout << "Merge Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;

	//V ksztal
	cout << " V KSZTALT" << endl;
	Elements(6, tab, 100);
	for (int i = 0; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	///////////////
	Elements(6, tab, 100);
	BubbleSort(tab, 100);
	cout << "Bubble Sort: " << endl;
	for (int i = 0; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	////////////
	Elements(6, tab, 101);
	HeapSort(tab, 100);
	cout << "Heap Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(6, tab, 101);
	CountingSort(tab, 100);
	cout << "Counting Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(6, tab, 101);
	ShellSort(tab, 100);
	cout << "Shell Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(6, tab, 101);
	QuickSortAlg(0, 100, tab);
	cout << "Quick Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;
	//////////////
	Elements(6, tab, 101);
	int * tab4 = new int[101];
	MergeSortAlg(tab, tab4, 0, 100);
	cout << "Merge Sort: " << endl;
	for (int i = 1; i < 100; i++) cout << tab[i] << " ";
	cout << endl;

	delete[] tab;
}

void Zad2Zdawanie()
{
	cout << "A ksztalt" << endl;
	int * tab = new int[99999];
	Elements(5, tab, 99999);
	auto begin = std::chrono::high_resolution_clock::now();
	QuickSortAlg(1, 99999, tab);
	auto end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "  ";

	int * tab2 = new int[100000];
	Elements(5, tab2, 100000);
	 begin = std::chrono::high_resolution_clock::now();
	QuickSortAlg(1, 100000, tab2);
	 end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "  ";

	int * tab3 = new int[100001];
	Elements(5, tab3, 100001);
	 begin = std::chrono::high_resolution_clock::now();
	QuickSortAlg(1, 100001, tab3);
	 end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "  ";
	cout << endl;

	cout << "V ksztalt" << endl;
	int * tab4 = new int[99999];
	Elements(6, tab4, 99999);
	 begin = std::chrono::high_resolution_clock::now();
	QuickSortAlg(1, 99999, tab4);
	 end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "  ";

	int * tab7 = new int[100000];
	Elements(6, tab7, 100000);
	begin = std::chrono::high_resolution_clock::now();
	QuickSortAlg(1, 100000, tab7);
	end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "  ";

	
	int * tab6 = new int[100001];
	Elements(6, tab6, 100001);
	begin = std::chrono::high_resolution_clock::now();
	QuickSortAlg(1, 100001, tab6);
	end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "  ";
	

}

void TestowanieQuicka()
{
	int tab[7] = { 1,2,3,9,8,7,6 };
	QuickSortAlg(0, 6, tab);
}


int main()
{

	//Zad1();
	//Zad2();

	
	//int tab [] = {99, 5, 4, 3, 87, 1, 5, 2, 3, 21,99 ,4,98,21};
	//for (int i = 0; i <14; i++) cout << tab[i] << " ";
	//cout << endl << endl;
	//QuickSortAlg(0, 13, tab);
	//HeapSort(tab, 13);
	//for (int i = 1; i < 14; i++) cout << tab[i] << " ";

	//Zad1Zdawanie();
	//Zad2Zdawanie();
	TestowanieQuicka();

	

	system("pause");
	return 0;
}