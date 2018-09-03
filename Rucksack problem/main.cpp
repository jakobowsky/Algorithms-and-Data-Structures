#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
using namespace std;


struct Item
{
	int sizeOfItem;
	int valueOfItem;
};

struct Rucksack
{
	int valueOfRack = 0;
	int sizeOfRack = 0;
	int maxSizeOfRack;
	vector <Item> items;
};

bool ratioF(Item a, Item b)
{
	return  a.valueOfItem /a.sizeOfItem  > b.valueOfItem / b.sizeOfItem  ;
}

void Generator(vector <Item> &items,int numberOfElements, int maxSizeOfItem)
{

	Item item;
	item.sizeOfItem = rand() % maxSizeOfItem + 1;
	item.valueOfItem = rand() % maxSizeOfItem * 2 + 1;
	items.push_back(item);

	for (int i = 1; i < numberOfElements; i++)
	{
		item.sizeOfItem = rand() % maxSizeOfItem + 1;
		item.valueOfItem = rand() % maxSizeOfItem * 2 + 1;
		bool thesame = 0;
		for (int j = 0; j < items.size(); j++)
		{
			if (items[j].sizeOfItem == item.sizeOfItem && items[j].valueOfItem == item.valueOfItem)
			{
				thesame = 1;
				break;
			}
		}
		if (thesame)
		{
			i--;
			continue;
		}
		else
			items.push_back(item);
	}
}

void ShowItems(vector <Item> &items)
{
	for (int i = 0; i < items.size(); i++)
	{
		cout << "Size of Items: " << items[i].sizeOfItem << "   , Value of Items: " << items[i].valueOfItem << " importance: "<< items[i].valueOfItem/items[i].sizeOfItem << endl;
	}
}

void NextPerm(int *actualPerm, int numberOfPerm, int numberOfElements) //moze sie nie udac bo np 8 sie na 4 bitach zapisuje
{
	for (int i = numberOfElements - 1; i >= 0; i--)
	{
		//cout << numberOfPerm % 2 << endl;
		actualPerm[i] = numberOfPerm % 2;
		numberOfPerm /= 2;
	}
	/*
	for (int i = 0; i < numberOfElements; i++)
		cout << actualPerm[i];
	cout << endl;
	*/
}

void BruteForce(Rucksack &backpack, int numberOfElements,vector <Item> &items,double &time)
{
	auto begin = std::chrono::high_resolution_clock::now();
	long long permutations = pow(2, numberOfElements);
	int * actualPerm = new int[numberOfElements];
	int * bestPerm = new int[numberOfElements]; 
	int bestValue = 0;
	for (int i = 0; i < permutations; i++)
	{
		backpack.valueOfRack = 0;
		backpack.sizeOfRack = 0;
		bool goodPerm = 1;
		NextPerm(actualPerm, i, numberOfElements);
		
		
		for (int j = 0; j < numberOfElements; j++)
		{
			backpack.valueOfRack += (items[j].valueOfItem * actualPerm[j]); //multiply * 1 if item is in actual permutation
			backpack.sizeOfRack += (items[j].sizeOfItem * actualPerm[j]);

			
			if (backpack.sizeOfRack > backpack.maxSizeOfRack)
			{
				goodPerm = 0;
				break;
			}
			
				
		}
		

		if (backpack.sizeOfRack <= backpack.maxSizeOfRack && backpack.valueOfRack > bestValue && goodPerm)
		{
			bestValue = backpack.valueOfRack;
			for (int j = 0; j < numberOfElements; j++)
			{
				bestPerm[j] = actualPerm[j];

			}
		}
	}

	
	auto end = std::chrono::high_resolution_clock::now();
	time = double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
	backpack.valueOfRack = 0;
	backpack.sizeOfRack = 0;

	for (int j = 0; j < numberOfElements; j++)
	{
		backpack.valueOfRack += (items[j].valueOfItem * bestPerm[j]); //multiply * 1 if item is in actual permutation
		backpack.sizeOfRack += (items[j].sizeOfItem * bestPerm[j]);
		if (bestPerm[j])
			backpack.items.push_back(items[j]);
		
	}
	

	delete[] actualPerm;
	delete[] bestPerm;



}

void Dynamic(Rucksack &backpack, vector <Item> &items,double &time)
{
	vector <Item> items2; //index from 1
	Item nothing;
	nothing.sizeOfItem = 9999;
	nothing.valueOfItem = 0;
	items2.push_back(nothing);
	for (int i = 0; i < items.size(); i++)
		items2.push_back(items[i]);

	int N = items.size(); //number of elements
    int W = backpack.maxSizeOfRack; 
	int **Q = new int*[N + 1];  //tab of elements in backpack
	int **P = new int*[N + 1]; //tab of sizes of elements in backpack
	for (int i = 0; i < N + 1; i++)
	{
		Q[i] = new int[W + 1];
		P[i] = new int[W + 1];
	}
	for (int i = 0; i < N + 1; i++)
	{
		for (int j = 0; j < W + 1; j++)
		{
			P[i][j] = 0;
			Q[i][j] = 0;
		}
	}

	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j < W + 1; j++)
		{
			if (j >= items2[i].sizeOfItem && P[i - 1][j - items2[i].sizeOfItem] + items2[i].valueOfItem > P[i - 1][j])
			{
				P[i][j] = P[i - 1][j - items2[i].sizeOfItem] + items2[i].valueOfItem;
				Q[i][j] = 1;
			}
			else
			{
				P[i][j] = P[i - 1][j];
				Q[i][j] = 0;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	time = double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
	//geting items to backpack
	
	/*
	int j = W, i = items.size(), sizeofBack = 0;
	while (j > 0 && i > 0)
	{
		if (Q[i][j] == 1)
		{
			j = j - items2[i].sizeOfItem;
			sizeofBack += items2[i].sizeOfItem;
			backpack.items.push_back(items2[i]);
		}
		i--;
	}

	backpack.valueOfRack = P[items.size()][W];
	backpack.sizeOfRack = sizeofBack;
	*/
	

	


	// Cout best solution
	
	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j<W + 1; j++)
		{
			cout << P[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl << endl;

	for (int i = 1; i<N + 1; i++)
	{
		for (int j = 1; j<W + 1; j++)
		{
			cout << Q[i][j] << ' ';
		}
		cout << endl;
	}

	

	cout << "Najlepsze rozwiazanie da nam wartosc: " << P[N][W] << endl << endl;
	
		
	//free memory


	for (int i = 0; i <= items.size(); ++i)
	{
		delete[] P[i];
		delete[] Q[i];
	}

	delete[] P;
	delete[] Q;

}
  
void DynamicValue(Rucksack &backpack, vector <Item> &items, double &time)
{
	vector <Item> items2; //index from 1
	Item nothing;
	nothing.sizeOfItem = 999999;
	nothing.valueOfItem = 0;
	items2.push_back(nothing);
	for (int i = 0; i < items.size(); i++)
		items2.push_back(items[i]);

	int N = items.size(); //number of elements
	int W = backpack.maxSizeOfRack;
	int **Q = new int*[N + 1];  //tab of elements in backpack
	int **P = new int*[N + 1]; //tab of sizes of elements in backpack
	for (int i = 0; i < N + 1; i++)
	{
		Q[i] = new int[W + 1];
		P[i] = new int[W + 1];
	}
	for (int i = 0; i < N + 1; i++)
	{
		for (int j = 0; j < W + 1; j++)
		{
			P[i][j] = 0;
			Q[i][j] = 0;
		}
	}

	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j < W + 1; j++)
		{
			if (j >= items2[i].sizeOfItem && P[i - 1][j - items2[i].sizeOfItem] + items2[i].valueOfItem > P[i - 1][j])
			{
				P[i][j] = P[i - 1][j - items2[i].sizeOfItem] + items2[i].valueOfItem;
				Q[i][j] = 1;
			}
			else
			{
				P[i][j] = P[i - 1][j];
				Q[i][j] = 0;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	time = double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
	//geting items to backpack

	
	int j = W, i = items.size(), sizeofBack = 0;
	while (j > 0 && i > 0)
	{
	if (Q[i][j] == 1)
	{
	j = j - items2[i].sizeOfItem;
	sizeofBack += items2[i].sizeOfItem;
	backpack.items.push_back(items2[i]);
	}
	i--;
	}

	backpack.valueOfRack = P[items.size()][W];
	backpack.sizeOfRack = sizeofBack;
	





	// Cout best solution
	/*
	for (int i = 1; i < N + 1; i++)
	{
	for (int j = 1; j<W + 1; j++)
	{
	cout << P[i][j] << ' ';
	}
	cout << endl;
	}
	cout << endl << endl;

	for (int i = 1; i<N + 1; i++)
	{
	for (int j = 1; j<W + 1; j++)
	{
	cout << Q[i][j] << ' ';
	}
	cout << endl;
	}



	cout << "Najlepsze rozwiazanie da nam wartosc: " << P[N][W] << endl << endl;
	*/

	//free memory


	for (int i = 0; i <= items.size(); ++i)
	{
		delete[] P[i];
		delete[] Q[i];
	}

	delete[] P;
	delete[] Q;

}



void Greedy(vector <Item> &items, Rucksack &backpack,double &time) //we need to pass sorted items here
{
	auto begin = std::chrono::high_resolution_clock::now();
	sort(items.begin(), items.begin() + items.size(), ratioF);
	int i = 0;
	while (i < items.size() && backpack.sizeOfRack <= backpack.maxSizeOfRack)
	{
		if (items[i].sizeOfItem + backpack.sizeOfRack <= backpack.maxSizeOfRack)
		{
			backpack.items.push_back(items[i]);
			backpack.sizeOfRack += items[i].sizeOfItem;
			backpack.valueOfRack += items[i].valueOfItem;
		}
		i++;
	}
	auto end = std::chrono::high_resolution_clock::now();
	time = double(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
	
}

/*
void MultiTest()
{
	int max = 20;
	int nrOfItems = 15;
	vector <Item> itemki;
	Generator(itemki, nrOfItems, max);
	cout << "pre sort: " << endl;
	ShowItems(itemki);
	cout << "after sort: " << endl;
	sort(itemki.begin(), itemki.begin() + itemki.size(),ratioF);
	ShowItems(itemki);

	Rucksack backpack;
	backpack.maxSizeOfRack = max;
	Greedy(itemki, backpack);
	cout << endl << endl;
	cout << " G R E E D Y:" << endl;
	cout << "------------------ backpack:" << endl;
	cout << "Uzyskanko value: " << backpack.valueOfRack << endl;
	cout << "max size: " << backpack.maxSizeOfRack << endl;
	cout << "size used: " << backpack.sizeOfRack << endl;
	cout << "Items: " << endl;
	for (int i = 0; i < backpack.items.size(); i++)
	{
		cout << " size: " << backpack.items[i].sizeOfItem << " value: " << backpack.items[i].valueOfItem << endl;
	}
	cout << "---------------------" << endl;
	Rucksack backpack2;
	backpack2.maxSizeOfRack = max;
	BruteForce(backpack2, nrOfItems, itemki);
	cout << endl << endl;
	cout << " B R U T E  F O R C E:" << endl;
	cout << "------------------ backpack:" << endl;
	cout << "Uzyskanko value: " << backpack2.valueOfRack << endl;
	cout << "max size: " << backpack2.maxSizeOfRack << endl;
	cout << "size used: " << backpack2.sizeOfRack << endl;
	cout << "Items: " << endl;
	for (int i = 0; i < backpack2.items.size(); i++)
	{
		cout << " size: " << backpack2.items[i].sizeOfItem << " value: " << backpack2.items[i].valueOfItem << endl;
	}
	cout << "---------------------" << endl;
	double time;
	Rucksack backpack3;
	backpack3.maxSizeOfRack = max;
	Dynamic(backpack3, itemki,time);
	cout << endl << endl;
	cout << " D Y N A M I C:" << endl;
	cout << "------------------ backpack:" << endl;
	cout << "Uzyskanko value: " << backpack3.valueOfRack << endl;
	cout << "max size: " << backpack3.maxSizeOfRack << endl;
	cout << "size used: " << backpack3.sizeOfRack << endl;
	cout << "Items: " << endl;
	for (int i = 0; i < backpack3.items.size(); i++)
	{
		cout << " size: " << backpack3.items[i].sizeOfItem << " value: " << backpack3.items[i].valueOfItem << endl;
	}
	cout << "---------------------" << endl;


}
*/


void DynamicTest()
{
	vector <Item> items;
	int b = 2000;
	for (int i = 0; i < 10; i++)
	{
		
		items.clear();
		ofstream file("dynamicSOLO" + to_string(b) + ".txt");
		file << "n,time" << endl;
		int n = 1000;
		for (int j = 0; j < 15; j++)
		{
			double time = 0;
			Generator(items, n, b);
			Rucksack rucksack;
			rucksack.maxSizeOfRack = b;
			
			Dynamic(rucksack, items,time);
			file << n << "," << time<< endl;
			cout<<"B: "<<b<<" N: " << n << " TIME: " << time << endl;
			n += 500;
			rucksack.sizeOfRack = 0;
			rucksack.valueOfRack = 0;
			rucksack.items.clear();
			items.clear();

		}

		file.close();
		b += 2000;
	}
}

void GreedyTest()
{
	vector <Item> items;
	int b = 2000;
	for (int i = 0; i < 10; i++)
	{
		
		items.clear();
		ofstream file("greedySOLO" + to_string(b) + ".txt");
		file << "n,time" << endl;
		int n = 1000;
		for (int j = 0; j < 15; j++)
		{
			double time = 0;
			Generator(items, n, b);
			Rucksack rucksack;
			rucksack.maxSizeOfRack = b;
			
			//posorotwac
			Greedy(items,rucksack, time);
			file << n << "," << time << endl;
			cout << "B: " << b << " N: " << n << " TIME: "  << time << endl;
			n += 500;
			rucksack.sizeOfRack = 0;
			rucksack.valueOfRack = 0;
			rucksack.items.clear();
			items.clear();
		}

		file.close();
		b += 2000;
	}
}

void BruteTest()
{
	//micro sec
	vector <Item> items;
	int b = 2000;
	for (int i = 0; i < 10; i++)
	{
		
		items.clear();
		ofstream file("bruteSOLO" + to_string(b) + ".txt");
		file << "n,time" << endl;
		int n = 1;
		for (int j = 0; j < 15; j++)
		{
			double time = 0;
			Generator(items, n, b);
			Rucksack rucksack;
			rucksack.maxSizeOfRack = b;

			BruteForce(rucksack, n,items, time);

			file << n << "," << time << endl;
			cout << "B: " << b << " N: " << n << " TIME: " << time << endl;
			n += 2;
			rucksack.sizeOfRack = 0;
			rucksack.valueOfRack = 0;
			rucksack.items.clear();
			items.clear();
		}

		file.close();
		b += 2000;
	}
}

void BruteAndDynamicTest()
{
	//micro sec
	vector <Item> items;
	int b = 20000;
	

	items.clear();
	ofstream file("2BruteVSDynamic" + to_string(b) + ".txt");
	file << "n,time" << endl;
	ofstream file1("2DynamicVSDynamic" + to_string(b) + ".txt");
	file1 << "n,time" << endl;
	int n = 1;
	for (int j = 0; j < 15; j++)
	{
		double time = 0;
		double time1 = 0;
		Generator(items, n, b);
		Rucksack rucksack;
		Rucksack rucksack1;
		rucksack.maxSizeOfRack = b;
		rucksack1.maxSizeOfRack = b;

		BruteForce(rucksack, n, items, time);
		Dynamic(rucksack1,items, time1);

		cout << "Brute:" << endl;
		file << n << "," << time << endl;
		cout << "B: " << b << " N: " << n << " TIME: " << time << endl;
		cout << "Dynamic:" << endl;
		file1 << n << "," << time1 << endl;
		cout << "B: " << b << " N: " << n << " TIME: " << time1 << endl;

		n += 2;
		rucksack.sizeOfRack = 0;
		rucksack.valueOfRack = 0;
		rucksack.items.clear();

		rucksack1.sizeOfRack = 0;
		rucksack1.valueOfRack = 0;
		rucksack1.items.clear();

		items.clear();
	}

	file.close();
	file1.close();
	
	
}

void DynamicAndGreedyTest()
{
	//micro sec
	vector <Item> items;
	int b = 20000;


	items.clear();
	ofstream file("3DynamicVSGreedy" + to_string(b) + ".txt");
	file << "n,time" << endl;
	ofstream file1("3GreedyVSDynamic" + to_string(b) + ".txt");
	file1 << "n,time" << endl;

	ofstream file2("3DynamicVSGreedyScore" + to_string(b) + ".txt");
	file2 << "n,DynamicScore,GreedyScore,G/D %" << endl;
	

	int n = 1000;
	for (int j = 0; j < 15; j++)
	{
		double time = 0;
		double time1 = 0;
		Generator(items, n, b);
		sort(items.begin(), items.begin() + items.size(), ratioF);
		Rucksack rucksack;
		Rucksack rucksack1;
		rucksack.maxSizeOfRack = b;
		rucksack1.maxSizeOfRack = b;

		
		DynamicValue(rucksack, items, time);
		Greedy(items, rucksack1, time1);

		cout << "Dynamic:" << endl;
		file << n << "," << time << endl;
		cout << "B: " << b << " N: " << n << " TIME: " << time << endl;
		cout << "Greedy:" << endl;
		file1 << n << "," << time1 << endl;
		cout << "B: " << b << " N: " << n << " TIME: " << time1 << endl;


		cout << n << "," << rucksack.valueOfRack << "," << rucksack1.valueOfRack << "," << float(rucksack1.valueOfRack) / float(rucksack.valueOfRack) * 100 << endl;
		file2 << n << "," << rucksack.valueOfRack << "," << rucksack1.valueOfRack << "," << float(rucksack1.valueOfRack) / float(rucksack.valueOfRack )* 100 << endl;



		n += 500;
		rucksack.sizeOfRack = 0;
		rucksack.valueOfRack = 0;
		rucksack.items.clear();

		rucksack1.sizeOfRack = 0;
		rucksack1.valueOfRack = 0;
		rucksack1.items.clear();

		items.clear();
	}

	file.close();
	file1.close();
	file2.close();
	


}

void Zaliczenie()
{
	vector<Item> items;
	Item przedmiot1;
	przedmiot1.sizeOfItem = 3;
	przedmiot1.valueOfItem = 1;
	items.push_back(przedmiot1);

	Item przedmiot2;
	przedmiot2.sizeOfItem = 2;
	przedmiot2.valueOfItem = 5;
	items.push_back(przedmiot2);

	Item przedmiot3;
	przedmiot3.sizeOfItem = 4;
	przedmiot3.valueOfItem = 3;
	items.push_back(przedmiot3);


	Item przedmiot4;
	przedmiot4.sizeOfItem = 2;
	przedmiot4.valueOfItem = 2;
	items.push_back(przedmiot4);


	Item przedmiot5;
	przedmiot5.sizeOfItem = 5;
	przedmiot5.valueOfItem = 7;
	items.push_back(przedmiot5);


	Item przedmiot6;
	przedmiot6.sizeOfItem = 13;
	przedmiot6.valueOfItem = 17;
	items.push_back(przedmiot6);

	ShowItems(items);

	Rucksack ruck;
	ruck.maxSizeOfRack = 12;
	ruck.sizeOfRack = 0;
	ruck.valueOfRack = 0;
	double time;
	Dynamic(ruck, items, time);




}


int main()
{
	srand(time(NULL));
	//MultiTest();
	//DynamicTest();
	//BruteTest();
	//GreedyTest();
	//BruteAndDynamicTest();
	//DynamicAndGreedyTest();
	Zaliczenie();
	system("Pause");
	return 0;
}