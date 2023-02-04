/*Napisati program koji će omogučiti: Unos 2D niza od 10x10 elemanata vodeći računa da su svi elementi dvocifreni 
(ukoliko unos nekog elementa ne zadovoljava uslov, ponavljati unos tog elementa dok se ne zadovolji uslov); 
Koristiti funkciju unos Izvršiti transpoziciju niza tako što će se zamjeniti redovi i kolone - 
Koristiti funkciju transpose, a zatim na osnovu izmijenjenog 2D niza: 
Izračunati aritmetičku sredinu svih prostih brojeva ispod sporedne dijagonale - 
Koristiti dvije funkcije: aritmeticka i prost_broj (pozivati će se iz funkcije aritmeticka) 
Napisati funkciju simpatican koja će provjeriti da li su brojevi iznad sporedne dijagonale simpatični*. 
Obavezno koristiti navedene funkcije, a parametre i eventualne povratne vrijednosti definisati prema potrebi. 
U main() funkciji napisati testni program koji će omogućiti izvršenje svih funkcija navedenim redoslijedom.
Pomoć: Broj je simpatičan ukoliko je zbir cifara njegovog kvadrata jednak kvadratu zbira njegovih cifara. 
Broj 21 je simpatičan jer je s(441) = s(21) * s(21) pri čemu je s(n) zbir cifara prirodnog broja n.*/

#include<iostream>
#include<cstdlib>
#include <windows.h>

struct struktura {
	int* _broj{ nullptr };

	struktura() {
		_broj = nullptr;
	}

	void set(int broj) {
		if (_broj == nullptr) _broj = new int;
		*_broj = broj;
	}

	void print() {
		std::cout << "[" << *_broj << "] ";
	}

	~struktura() {
		delete _broj; _broj = nullptr;
	}

};

void transpozicija(struktura**, int);
bool prost(int);
float prosjek(struktura**, int);
bool simpatican(int);
int suma(int);
void simpaticnibrojevi(struktura**, int);

int main() {

	srand(time(NULL));
	int vel = 10;
	struktura** s = new struktura * [vel];
	for (int i = 0; i < vel; i++)
		*(s + i) = new struktura[vel];

	{
		int x; std::cout << "Unesite 1 za manuelni unos: "; std::cin >> x;

		for (int i = 0; i < vel; i++)
		{
			for (int j = 0; j < vel; j++)
			{
				int broj;
				do {
					if (x == 1) {
						std::cout << "Unesite dvocifren broj: "; std::cin >> broj;
					}
					else {
						broj = 10; broj += rand() % 89 + 1;
					}
				} while (broj < 10 || broj > 99);
				(*(s + i) + j)->set(broj);
			}
		}
	}

	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			(*(s + i) + j)->print();
		}
		std::cout << std::endl;
	}

	std::cout << "\n\n\n\n";
	std::cout << "Transpozicioniran niz: \n";
	transpozicija(s, vel);

	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			(*(s + i) + j)->print();
		}
		std::cout << std::endl;
	}

	std::cout << "\n";
	float f = prosjek(s, vel);
	if (f == -1.0f) std::cout << "U nizu nema prostih brojeva ispod sporedne dijagonale!";
	else std::cout << "Prosjek prostih brojeva ispod sporedne dijagonale je: " << f;

	std::cout << "\n\n\n\n\n";
	simpaticnibrojevi(s, vel);

	for (int i = 0; i < vel; i++)
		delete[] * (s + i);
	delete[] s;

	system("pause>nul");
	return 1;
}

void transpozicija(struktura** s, int vel) {
	
	int** niz = new int* [vel];
	for (int i = 0; i < vel; i++)
		*(niz + i) = new int[vel];

	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			*(*(niz + i) + j) = *(*(s + j) + i)->_broj;
		}
	}

	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			*(*(s + i) + j)->_broj = *(*(niz + i) + j);
		}
	}

	for (int i = 0; i < vel; i++)
		delete[] * (niz + i);
	delete[] niz;
}

bool prost(int n) {
	if (n <= 1) return false;
	else if (n == 2 || n == 3) return true;
	else {
		for (int i = 2; i < n; i++)
		{
			if (n % i == 0) return false;
		}
	}
	return true;
}

float prosjek(struktura** s, int vel) {
	float prosjek = 0.0f;
	int brojac = 0;
	for (int i = 0; i < vel; i++)
	{
		for (int j = vel - 1; j + i >= vel - 1; j--)
		{
			if (prost(*(*(s + i) + j)->_broj)) {
				brojac++;
				prosjek += *(*(s + i) + j)->_broj;
			}
		}
	}

	if (brojac == 0) {
		return -1.0f;
	}

	return (prosjek /= float(brojac));
}

int suma(int n) {
	int s = 0;
	while (n) {
		s += n % 10; n /= 10;
	}
	return s;
}
bool simpatican(int n) {
	int kvadrat = pow(n,2);
	n = suma(n);
	return (suma(kvadrat) == pow(n,2));
}

void simpaticnibrojevi(struktura** s, int vel) {

	std::cout << "Simpaticni brojevi su obojeni crvenom bojom: \n";

	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel - i; j++)
		{
			int k = 14;
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			if (simpatican(*(*(s + i) + j)->_broj)) k = 4;

			SetConsoleTextAttribute(hConsole, k);
			(*(s + i) + j)->print();
		
		}
		std::cout << "\n";
	}
}