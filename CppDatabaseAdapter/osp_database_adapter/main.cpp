#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

string Znajdz_tablice(string napis, int &wynik_operacji, string sciezkaodczyt) {
	fstream plik;
	string wynik, stary_wynik = "";
	bool koniec_sprawdzania = false;

	plik.open(sciezkaodczyt, ios::in);
	if (plik.good()) {
		for (;;) {
			getline(plik, wynik);
			if (wynik == napis) {
				wynik = "Znaleziono tablice : " + wynik;
				wynik_operacji = 11;
				koniec_sprawdzania = true;
			}
			else if (wynik == stary_wynik) {
				wynik = "Nie znaleziono tablicy!";
				wynik_operacji = 10;
				koniec_sprawdzania = true;
			}
			stary_wynik = wynik;
			if (koniec_sprawdzania == true) {
				koniec_sprawdzania = false;
				break;
			}
		}
	}
	else {
		wynik = "ERROR: Nie mozna otworzyc pliku!";
		wynik_operacji = 100;
	}
	plik.close();
	return wynik;
}

string Dodaj_tablice(string napis, int& wynik_operacji, string sciezkazapis) {
	fstream plik;
	string wynik;
	string tablica;
	int zm_pom;
	Znajdz_tablice(napis, zm_pom, sciezkazapis);
	if (zm_pom == 10 || zm_pom == 100) {
		plik.open(sciezkazapis, ios::out | ios::app);
		if (plik.good()) {
			plik.seekp(0, ios_base::end);
			plik << endl << napis;
			wynik = "Zapisano tablice : " + napis;
			wynik_operacji = 21;
		}
		else {
			wynik = "ERROR: Nie mozna otworzyc pliku!";
			wynik_operacji = 200;
		}
		plik.close();
	}
	else {
		wynik = "Istnieje taka tablica!";
		wynik_operacji = 20;
	}
	return wynik;
}

int main(int argc, char* argv[]) {
	string wynik;
	string operacja = argv[1];
	string napis = argv[2];
	string sciezka = argv[3];
	int wynik_operacji;
	bool koniec_sprawdzania = false;
	if (operacja == "odczyt") {
		wynik = Znajdz_tablice(napis, wynik_operacji, sciezka);
		cout << wynik_operacji << endl;
		cout << wynik << endl;
	}
	else if (operacja == "zapis") {
		wynik = Dodaj_tablice(napis, wynik_operacji, sciezka);
		cout << wynik_operacji << endl;
		cout << wynik << endl;
	}
	else {
		cout << "Nie podano poprawnej parametryzacji!";
		wynik_operacji = 0;
	}
	return wynik_operacji;
}