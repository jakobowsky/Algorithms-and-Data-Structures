#pragma once
#include <iostream>
#include <string>
using namespace std;

struct student
{
	student *nastepny;
	string imie;
	string nazwisko;
	unsigned int nr_indeksu;
};

class List
{
public:
	int ROZMIAR;
	student * glowa;
	List();
	~List();
	unsigned int rozmiar(); //pokazuje rozmiar listy
	void wyswietl(); // wyswietla cala liste
	void dodajPierwszy(string imie, string nazwisko, unsigned int nr_indeksu); // dodaje osobe na poczatek listy
	void dodajOstatni(string imie, string nazwisko, unsigned int nr_indeksu); // dodaje osobe na koniec listy
	void dodajPrzed(int nr, string imie, string nazwisko, unsigned int nr_indeksu); //dodaje osobe przed jakas osoba
	void dodajPo(int nr, string imie, string nazwisko, unsigned int nr_indeksu); //dodaje osobe po jakiejs osobie
	void usunPierwszy();
	void usunOstatni();
	void usunOsobe(int Nnr_indeksu);
	void znajdz(int Nnr_indeksu);
	student * znajdzOsobeAdres(int Nnr_indeksu);

};

