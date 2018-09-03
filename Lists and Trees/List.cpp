#include "List.h"

List::List()
{
	glowa = NULL;
	ROZMIAR = 0;
}

List::~List()
{
	while (glowa) usunOstatni();
}

unsigned int List::rozmiar()
{
	unsigned int rozmiar = 0;
	student * temp = glowa;
	while (temp)
	{
		temp = temp->nastepny;
		rozmiar++;
	}
	return rozmiar;
}

void List::wyswietl()
{
	int i = 1;
	student * temp = glowa;
	while (temp)
	{
		std::cout << "Osoba " << i++ << " " << temp->imie << " " << temp->nazwisko << " " << temp->nr_indeksu << std::endl;
		temp = temp->nastepny;
	}
}

void List::dodajPierwszy(string Nimie, string Nnazwisko, unsigned int Nnr_indeksu)
{
	student * osoba = new student;
	osoba->nastepny = glowa; //glowa staje sie teraz nastepnym elementem
	osoba->imie = Nimie;
	osoba->nazwisko = Nnazwisko;
	osoba->nr_indeksu = Nnr_indeksu;
	glowa = osoba; //element staje sie teraz glowa
}

void List::dodajOstatni(string Nimie, string Nnazwisko, unsigned int Nnr_indeksu)
{
	student * osoba = new student;
	osoba->imie = Nimie;
	osoba->nazwisko = Nnazwisko;
	osoba->nr_indeksu = Nnr_indeksu;
	osoba->nastepny = NULL; //nowy ostatni element nie wskazuje na nic
	student *pierwszaTMP = new student;
	pierwszaTMP = glowa;
	if (pierwszaTMP) // jezeli lista nie jest pusta to szuka ostatniego
	{
		while (pierwszaTMP->nastepny)
			pierwszaTMP = pierwszaTMP->nastepny;
		pierwszaTMP->nastepny = osoba;
	}
	else //jezeli lista byla pusta to nowy element staje sie glowa
	{
		glowa = osoba;
	}
	ROZMIAR++;
}

void List::dodajPrzed(int nr, string Nimie, string Nnazwisko, unsigned int Nnr_indeksu)
{
	if (nr == 1) dodajPierwszy(Nimie, Nnazwisko, Nnr_indeksu);
	else
	{
		int j = 2;
		int rozmiarListy = rozmiar();
		if (j > rozmiarListy)
		{
			cout << "Nie ma tylu elementow" << endl;
		}
		else
		{
			student *osoba = new student;
			osoba->imie = Nimie;
			osoba->nazwisko = Nnazwisko;
			osoba->nr_indeksu = Nnr_indeksu;
			student *temp = new student;
			temp = glowa;
			while ((j < nr) && (j < rozmiarListy))
			{
				temp = temp->nastepny;
				j++;
				//cout << temp->imie << endl;
			}
			osoba->nastepny = temp->nastepny;
			temp->nastepny = osoba;
		}		
	}

}

void List::dodajPo(int nr, string Nimie, string Nnazwisko, unsigned int Nnr_indeksu)
{
	int rozmiarListy = rozmiar();
	if (nr == rozmiarListy)
		dodajOstatni(Nimie, Nnazwisko, Nnr_indeksu);
	else if (nr > rozmiarListy)
		cout << "Zly rozmiar" << endl;
	else
	{
		student *osoba = new student;
		osoba->imie = Nimie;
		osoba->nazwisko = Nnazwisko;
		osoba->nr_indeksu = Nnr_indeksu;
		student *temp = new student;
		temp = glowa;
		int j = 1;
		while (j < nr)
		{
			temp = temp->nastepny;
			j++;
		}
		osoba->nastepny = temp->nastepny;
		temp->nastepny = osoba;
	}
}

void List::usunPierwszy()
{
	student * osoba = new student;
	osoba = glowa;
	if (osoba)
	{
		glowa = osoba->nastepny;
		delete osoba;
	}
}

void List::usunOstatni()
{
	student *osoba = glowa;
	if (osoba)
	{
		if (osoba->nastepny)
		{
			while (osoba->nastepny->nastepny)
				osoba = osoba->nastepny;
			delete osoba->nastepny;
			osoba->nastepny = NULL;
		}
		else
		{
			delete osoba;
			glowa = NULL;
		}
	}
	
}

void List::usunOsobe(int Nnr_indeksu)
{
	int rozmiarListy = ROZMIAR;
	int j = 0;
	bool usuwanie = 1;
	student *osoba = new student;
	student *wskaznik = new student;
	osoba = glowa;
	if (osoba->nr_indeksu == Nnr_indeksu) usunPierwszy();
	else
	{
		while (j++<rozmiarListy)
		{
			if (osoba->nastepny->nr_indeksu == Nnr_indeksu)
			{
				if (j == rozmiarListy) usunOstatni();
				else
				{
					wskaznik = osoba->nastepny;
					osoba->nastepny = osoba->nastepny->nastepny; //ZAPYTAC JAK USUNAC TA SRODKOWA OS
					delete wskaznik;
					usuwanie = 0;
					break;
				}
			}
			else osoba = osoba->nastepny;
		}
		if (usuwanie) cout << "Nie znaleziono elementu" << endl;
	}
	ROZMIAR--;
	
		

	
}

void List::znajdz(int Nnr_indeksu)
{
	if (Nnr_indeksu != 0)
	{
		student *osoba = new student;
		osoba = glowa;
		if (osoba->nr_indeksu == Nnr_indeksu)
		{
			//reutrn osoba
			//cout << "Osoba o indeksie: " << Nnr_indeksu << " to: " << osoba->imie << " " << osoba->nazwisko << endl;
		}
		else
		{
			bool flaga = 1;
			while (osoba->nastepny != NULL)
			{
				if (osoba->nastepny->nr_indeksu == Nnr_indeksu)
				{
					//return osoba
					//cout << "Osoba o indeksie: " << Nnr_indeksu << " to: " << osoba->nastepny->imie << " " << osoba->nastepny->nazwisko << endl;
					flaga = 0;
					break;
				}
				osoba = osoba->nastepny;
			}
			if (flaga) cout << "Nie znaleziono takiej osoby " << Nnr_indeksu << endl;

		}
	}
	
	
	
}

student * List::znajdzOsobeAdres(int Nnr_indeksu)
{
	student *osoba = new student;
	osoba = glowa;
	if (osoba->nr_indeksu == Nnr_indeksu)
	{
		return osoba;
	//	cout << "Osoba o indeksie: " << Nnr_indeksu << " to: " << osoba->imie << " " << osoba->nazwisko << endl;
	}
	else
	{
		bool flaga = 1;
		while (osoba->nastepny != NULL)
		{
			if (osoba->nastepny->nr_indeksu == Nnr_indeksu)
			{
				return osoba;
				//cout << "Osoba o indeksie: " << Nnr_indeksu << " to: " << osoba->nastepny->imie << " " << osoba->nastepny->nazwisko << endl;
				flaga = 0;
				break;
			}
			osoba = osoba->nastepny;
		}
		if (flaga) cout << "Nie znaleziono takiej osoby" << endl;
	}

}
