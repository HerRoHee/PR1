/*Kreirati dinamički dvodimenzionalni niz čiji su elementi objekti tipa student 
(student je struktura čija su obilježja data u nastavku). 
Omogućiti korisniku da unese dimenzije niza.

struct student
{
    char *ID;
    char *imePrezime;
    float *prosjek;
};

Kompletan 2D niz predstavlja univerzitet. Redovi dvodimenzionalnog niza predstavljaju različite fakultete,
a kolone studente (radi jednostavnosti rješenja podrazumijevati da svaki fakultet ima isti broj studenata). 
Omogućiti korisniku unos svih podataka za sve studente, te napraviti funkciju koja će pronaći fakultet sa 
najvećim prosjekom te ispisati koji je to redni broj fakulteta (index reda sa najvećim prosjekom). 
Zatim pronaći i ispisati ID studenta koji ima najveći prosjek na cijelom univerzitetu.

(U ovom zadatku je zabranjeno indexirati elemente niza uglastim zagradama. 
Obavezno koristiti aritmetiku pokazivača. 
Obavezno voditi računa o dealociranju dinamički alocirane memorije.)*/

#include<iostream>
#include<cstdlib>

struct Student {
	int _ID;
	char* _imePrezime;
	float* _prosjek;

	Student() {
		_ID = 0;
		_imePrezime = nullptr;
		_prosjek = nullptr;
	}
	void set(int id, const char* imePrezime, float prosjek) {
		_ID = id;
		if (_prosjek == nullptr) _prosjek = new float;
		*_prosjek = prosjek;

		int vel = strlen(imePrezime) + 1;
		if (_imePrezime != nullptr) { delete[] _imePrezime; _imePrezime = nullptr; }
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);

	}

	void print() {
		std::cout << _ID << " - " << _imePrezime << " - [" << *_prosjek << "]\n";
	}

	~Student() {
		delete[] _imePrezime;
		delete _prosjek;
		_imePrezime = nullptr;
		_prosjek = nullptr;
	}

};

int najboljiFax(Student**, int, int);
int najboljiStudent(Student**, int, int);

void test1() {

	srand(time(NULL));

	int redovi = 5;
	int kolone = 5;

	// std::cout << "Unesite redove: "; std::cin >> redovi;
	// std::cout << "Unesite kolone: "; std::cin >> kolone;

	Student** s = new Student * [redovi];

	for (int i = 0; i < redovi; i++)
		*(s + i) = new Student[kolone];

	int x;
	std::cout << "Unesite 1 za manuelni unos, inace unesite bilo koji drugi broj: "; std::cin >> x;

	int ID = 0;
	{
		for (int i = 0; i < redovi; i++)
		{
			for (int j = 0; j < kolone; j++)
			{
				ID++;
				if (x == 1) {
					char text[100]; std::cin.ignore();
					std::cout << "[" << i << "][" << j << "] - Unesite ime i prezime studenta: "; std::cin.getline(text, 100);
					float prosjek = 0.0f;
					std::cout << "Unesite prosjek studenta: "; std::cin >> prosjek;
					(*(s + i) + j)->set(ID, text, prosjek);
				}
				else {
					float prosjek = 4;
					prosjek += ((float(rand() % 50) / 10) + 1.1);
					(*(s + i) + j)->set(ID, "student", prosjek);
				}

			}
		}
	}

	for (int i = 0; i < redovi; i++)
	{
		for (int j = 0; j < kolone; j++)
		{
			(*(s + i) + j)->print();
		}
		std::cout << ".........................................\n";
	}

	int index = najboljiFax(s, redovi, kolone);
	std::cout << "\n\n\n";
	std::cout << "Najbolji fax je sa indexom [" << index << "]\n";
	for (int j = 0; j < kolone; j++)
	{
		(*(s + index) + j)->print();
	}

	int indeks = najboljiStudent(s, index, kolone);
	std::cout << "\n\n\n";
	std::cout << "Najbolji student na najboljem faxu [" << index << "] je [" << indeks << "]: \n";
	(*(s + index) + indeks)->print();

	for (int i = 0; i < redovi; i++)
		delete[] * (s + i);
	delete[] s;

}

int main() {

	test1();
	
	system("pause>nul");
	return 1;
}

int najboljiFax(Student** s, int redovi, int kolone) {
	float max = 0.0f;
	int index = 0;
	for (int i = 0; i < redovi; i++)
	{
		float prosjek = 0.0f;
		for (int j = 0; j < kolone; j++)
		{
			prosjek += *(*(s + i) + j)->_prosjek;
		}
		prosjek /= float(kolone);
		if (prosjek > max) {
			max = prosjek;
			index = i;
		}
	}

	return index;
}
int najboljiStudent(Student** s, int index, int kolone) {
	float* max = new float(0.0f);
	int indeks = 0;

	for (int j = 0; j < kolone; j++)
	{
		if (*(*(s + index) + j)->_prosjek > *max) {
			*max = *(*(s + index) + j)->_prosjek;
			indeks = j;
		}
	}

	delete max;

	return indeks;
}