#include <iostream>
#include "List.h"
#include <fstream>
#include "Tree.h"
#include "TreeAVL.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;
string cr, cl, cp;

void WyswietlDRZEWO(string sp, string sn, BSTNode * v)
{
	string s;

	if (v)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		WyswietlDRZEWO(s + cp, cr, v->Right);

		s = s.substr(0, sp.length() - 2);
		cout << s << sn << v->osoba.nr_indeksu << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		WyswietlDRZEWO(s + cp, cl, v->Left);
	}
}

void Testowanie()
{
	/* TESTOWANIE
	fstream plik;
	plik.open("studenci.txt", ios::in);
	List lista;
	for (int i = 0; i < 3; i++)
	{
	string imie, nazwisko;
	unsigned int nr_indeksu;
	plik >> imie >> nazwisko >> nr_indeksu;
	lista.dodajOstatni(imie, nazwisko, nr_indeksu);
	}
	cout << lista.rozmiar() << endl;
	lista.wyswietl();
	cout << endl;
	//lista.usunOsobe(123);
	//lista.znajdz(2311);
	//lista.usunOstatni();
	//lista.wyswietl();
	//lista.dodajPo(3, "XXXX", "XXXX", 2222);
	//lista.wyswietl();
	*/
	/* Testowanie struktury
	BSTNode drzewko;
	drzewko.osoba.imie = "Arek";
	drzewko.osoba.nazwisko = "COs";
	cout << drzewko.osoba.imie;
	*/
	/*
	Tree drzewko;
	drzewko.insertStudent("pierwszy", "x", 14);
	drzewko.insertStudent("drugi", "x", 12);
	drzewko.insertStudent("trzeci", "x", 16);
	drzewko.insertStudent("czwarty", "x", 20);
	drzewko.insertStudent("piaty", "x", 30);
	drzewko.inorder(drzewko.root);
	//drzewko.deleteTree(drzewko.root);
	cout << endl;
	drzewko.deleteStudent(14);
	cout << endl;
	drzewko.inorder(drzewko.root);
	//drzewko.searchForStudent(16);
	//	BSTNode *x = drzewko.succesor(drzewko.root);
	//	cout << x->osoba.nr_indeksu;
	//BSTNode *k = drzewko.searchForStudent(12);
	//cout << k->osoba.imie;
	*/
	/*
	TreeAVL drzewo;
	drzewo.insertBST("pierwszy", "x", 14);
	//cout << drzewo.root << endl;
	drzewo.insertBST("drugi", "x", 16);
	drzewo.insertBST("trzeci", "x", 13);
	drzewo.insertBST("czwarty", "x", 20);
	drzewo.insertBST("piaty", "x", 30);
	drzewo.inorder(drzewo.root);
	cout << endl;
	drzewo.removeBST(drzewo.searchForStudent(16));
	drzewo.inorder(drzewo.root);
	drzewo.insertBST("ostatni", "x", 12);
	cout << endl;
	drzewo.inorder(drzewo.root);
	*/

	/*
	int n = 10000;
	student *studenci = new student[n];
	WczytajDoTablicy(studenci,10); //wczytanie studentow
	for (int i = 0; i < 10; i++)
	cout << studenci[i].nr_indeksu << endl;
	cout << endl;

	List listaStudentow;
	WczytajDoListy(listaStudentow, studenci,10);
	listaStudentow.wyswietl();


	delete[] studenci;
	*/




}

void WczytajDoTablicy(student *studenci,int n,string nazwaPliku)
{
	// program wczyta studentow do tablicy structow
	ifstream plik;
	plik.open(nazwaPliku);
	for (int i = 0; i <n; i++)
	{
		plik >> studenci[i].imie >> studenci[i].nazwisko >> studenci[i].nr_indeksu;
	}
	plik.close();
}

void WczytajDoListy(List &lista, student* studenci,int n)
{
	for (int i = 0; i < n; i++)
	{
		lista.dodajOstatni(studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_indeksu);
	}
	cout << "Udalo sie dodac do listy" << endl;
}

void WczytajDoDrzewa(Tree &drzewo, student* studenci, int n)
{
	for (int i = 0; i < n; i++)
	{
		drzewo.insertStudent(studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_indeksu);
	}
	cout << "Udalo sie dodac do drzewa" << endl;
}

void WczytajDoDrzewaAVL(TreeAVL &drzewo, student* studenci, int n)
{
	for (int i = 0; i < n; i++)
	{
		drzewo.insertBST(studenci[i].imie, studenci[i].nazwisko, studenci[i].nr_indeksu);
	}
	cout << "Udalo sie dodac do drzewaAVL" << endl;
}
//////////////////////////////////////////////////////// Wczytywanie
void Zad1DrzewoBalanceWczytywanieMierzenie()
{
	ofstream plik("WpiszDrzewoBalance.txt");
	int ilosc = 10000;
	for (int i = 1; i <= 15; i++)
	{
		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		Tree drzewo;
		auto begin = std::chrono::high_resolution_clock::now();
		WczytajDoDrzewa(drzewo, studenci, ilosc);
		drzewo.rebalanceTree();
		//drzewo.postorder(drzewo.root);
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		//WyswietlDRZEWO("", "", drzewo.root);
		drzewo.~Tree();
		delete[] studenci;
		ilosc += 2500;
	}
	plik.close();
}

void Zad1DrzewoWczytywanieMierzenie()
{
	ofstream plik("WpiszDrzewo.txt");
	int ilosc = 10000;
	for (int i = 1; i <= 15; i++)
	{
		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		Tree drzewo;
		auto begin = std::chrono::high_resolution_clock::now();
		WczytajDoDrzewa(drzewo, studenci, ilosc);
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~Tree();
		delete[] studenci;
		ilosc += 2500;
	}
	plik.close();
}

void Zad1ListaWczytywanieMierzenie()
{
	ofstream plik("WpiszLista.txt");
	int ilosc = 10000;
	for (int i = 1; i <= 15; i++)
	{
		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci,ilosc,"studenci.txt");
		List listaStudentow;
		auto begin = std::chrono::high_resolution_clock::now();
		WczytajDoListy(listaStudentow, studenci, ilosc);
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		listaStudentow.~List();
		delete[] studenci;
		ilosc += 2500;
	}
	plik.close();
}
//////////////////////////////////////////////////////////
void Zad1DrzewoAVLWczytywanieMierzenie()
{

	ofstream plik("WpiszDrzewoAVL.txt");
	int ilosc = 10000;
	for (int i = 1; i <= 15; i++)
	{
		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		TreeAVL drzewo;
		auto begin = std::chrono::high_resolution_clock::now();
		WczytajDoDrzewaAVL(drzewo, studenci, ilosc);
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~TreeAVL();
		delete[] studenci;
		ilosc += 2500;
	}
	plik.close();
}

bool czyBylaWylosowana(int iLiczba, int tab[], int ile)
{
	if (ile <= 0)
		return false;

	int i = 0;
	do
	{
		if (tab[i] == iLiczba)
			return true;

		i++;
	} while (i < ile);

	return false;
}

int wylosuj(int n)
{
	//srand(time(0));
	return((rand() % n)) ;
}

void WypelnijTabliceLosowymi(int *tab,int n)
{
	
	for (int i = 0; i < n;)
	{
		int liczba = wylosuj(n);
		
		if (!czyBylaWylosowana(liczba, tab, i))
		{
			//cout << liczba << endl;
			tab[i++] = liczba;
		}
		
			
	}
}
///////////////////////////////////////////////////// Szukanie
void Zad2ListaSzukaj()
{
	ofstream plik("SzukajLista.txt");
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{
		
		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenci.txt");
		List listaStudentow;
		WczytajDoListy(listaStudentow, studenci, ilosc);
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);
		
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			listaStudentow.znajdz(studenci[tab[i]].nr_indeksu);
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		listaStudentow.~List();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
	plik.close();
}

void Zad2BSTSzukaj()
{
	ofstream plik("SzukajDrzewo.txt");
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{

		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		Tree drzewo;
		WczytajDoDrzewa(drzewo, studenci, ilosc);
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);

		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			drzewo.searchForStudent(studenci[tab[i]].nr_indeksu);
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~Tree();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
	plik.close();
}

void Zad2BSTBalanceSzukaj()
{
	ofstream plik("SzukajDrzewoBalance.txt");
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{

		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		Tree drzewo;
		WczytajDoDrzewa(drzewo, studenci, ilosc);
		drzewo.rebalanceTree();
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);

		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			drzewo.searchForStudent(studenci[tab[i]].nr_indeksu);
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~Tree();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
	plik.close();
}
/////////////////////////////////////////////////////
void Zad2BSTAVLSzukaj()
{
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{

		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		TreeAVL drzewo;
		WczytajDoDrzewaAVL(drzewo, studenci, ilosc);
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);

		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			drzewo.searchForStudent(studenci[tab[i]].nr_indeksu);
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~TreeAVL();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
}


////////////////////////////// Usuwanie
void ZadUsunLista()
{
	ofstream plik("UsunLista.txt");
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{
		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenci.txt");
		List listaStudentow;
		WczytajDoListy(listaStudentow, studenci, ilosc);
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);

		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			listaStudentow.usunOsobe(studenci[tab[i]].nr_indeksu);
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		listaStudentow.~List();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
	plik.close();
}

void ZadUsunBST()
{
	ofstream plik("UsunDrzewo.txt");
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{

		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		Tree drzewo;
		WczytajDoDrzewa(drzewo, studenci, ilosc);
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);

		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			drzewo.deleteStudent(studenci[tab[i]].nr_indeksu);
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~Tree();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
	plik.close();
}

void ZadUsunBSTBalance()
{
	ofstream plik("UsunDrzewoBalance.txt");
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{

		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		Tree drzewo;
		WczytajDoDrzewa(drzewo, studenci, ilosc);
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			drzewo.deleteStudent(studenci[tab[i]].nr_indeksu);
			drzewo.rebalanceTree();
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		plik << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~Tree();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
	plik.close();
}
//////////////////////////////////////


void ZadUsunBSTAVL()
{
	int ilosc = 5000;
	for (int i = 1; i <= 15; i++)
	{

		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc, "studenciMIX.txt");
		TreeAVL drzewo;
		WczytajDoDrzewaAVL(drzewo, studenci, ilosc);
		int *tab = new int[ilosc];
		WypelnijTabliceLosowymi(tab, ilosc);

		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < ilosc; i++)
		{
			drzewo.removeBST(drzewo.searchForStudent(studenci[tab[i]].nr_indeksu));
		}
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		drzewo.~TreeAVL();
		delete[] studenci;
		delete[] tab;
		ilosc += 1000;
	}
}


void Testing()
{
	int ilosc = 1000;
	for (int i = 1; i <= 15; i++)
	{
		student *studenci = new student[ilosc];
		WczytajDoTablicy(studenci, ilosc,"studenciMIX.txt");
		TreeAVL drzewoStudentow;
		auto begin = std::chrono::high_resolution_clock::now();
		WczytajDoDrzewaAVL(drzewoStudentow, studenci, ilosc);
		auto end = std::chrono::high_resolution_clock::now();
		cout << ilosc << "," << fixed << setprecision(5) << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) / 1000000000 << "\n";
		//drzewoStudentow.inorder(drzewoStudentow.root);
		drzewoStudentow.~TreeAVL();
		delete[] studenci;
		ilosc += 1000;
	}
}

void ZadZaliczenie()
{

	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	student dane[12];
	int dane1[12];
	dane1[0] = 7;
	dane1[1] = 3;
	dane1[2] = 2;
	dane1[3] = 8;
	dane1[4] = 4;
	dane1[5] = 1;
	dane1[6] = 9;
	dane1[7] = 11;
	dane1[8] = 5;
	dane1[9] = 12;
	dane1[10] = 6;
	dane1[11] = 10;
	for (int i = 0; i <12; i++)
	{
		dane[i].imie = dane1[i];
		dane[i].nazwisko = dane1[i];
		dane[i].nr_indeksu = dane1[i];
	}
	
	Tree drzewo;

	


	WczytajDoDrzewa(drzewo, dane, 12);
	WyswietlDRZEWO("", "", drzewo.root);
	cout << "POST ORDERD:" << endl;
	drzewo.postorder(drzewo.root);
	cout << "PRE ORDER:" << endl;
	drzewo.preorder(drzewo.root);
	cout << "IN ORDER:" << endl;
	drzewo.inorder(drzewo.root);

}

void ZadTESTOWANIE()
{

	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	student dane[13];
	int dane1[13];
	dane1[0] = 17;
	dane1[1] = 4;
	dane1[2] = 18;
	dane1[3] = 22;
	dane1[4] = 12;
	dane1[5] = 13;
	dane1[6] = 7;
	dane1[7] = 3;
	dane1[8] = 9;
	dane1[9] = 6;
	dane1[10] = 15;
	dane1[11] = 23;
	dane1[12] = 16;
	for (int i = 0; i <13; i++)
	{
		dane[i].imie = dane1[i];
		dane[i].nazwisko = dane1[i];
		dane[i].nr_indeksu = dane1[i];
	}

	Tree drzewo;




	WczytajDoDrzewa(drzewo, dane, 12);
	WyswietlDRZEWO("", "", drzewo.root);
	drzewo.rebalanceTree();
	cout << endl << endl;
	WyswietlDRZEWO("", "", drzewo.root);
	drzewo.deleteStudent(13);
	drzewo.rebalanceTree();
	cout << endl << endl;
	WyswietlDRZEWO("", "", drzewo.root);


	/*
	cout << "POST ORDERD:" << endl;
	drzewo.postorder(drzewo.root);
	cout << "PRE ORDER:" << endl;
	drzewo.preorder(drzewo.root);
	cout << "IN ORDER:" << endl;
	drzewo.inorder(drzewo.root);
	*/

}



int main()
{
	
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	//ZadZaliczenie();
	ZadTESTOWANIE();

	//Zad1DrzewoWczytywanieMierzenie();
	//Zad1ListaWczytywanieMierzenie();
	//Zad1DrzewoAVL();
	//Zad1DrzewoBalanceWczytywanieMierzenie();
	//Testing();
	//Zad2BSTSzukaj();
	//Zad2BSTAVLSzukaj();
	//Zad2ListaSzukaj();
	//Zad2BSTBalanceSzukaj();
	//ZadUsunLista();
	//ZadUsunBST();
	//ZadUsunBSTBalance();
	//ZadUsunBSTAVL();
	system("Pause");
	return 0;
}