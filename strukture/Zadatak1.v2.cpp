#include<iostream>
#include<cstdlib>

struct Fudbaler {
	int* _godRodjenja{ nullptr };
	int* _brojIgraca{ nullptr };
	int* _brojGolova{ nullptr };

	Fudbaler() {
		_godRodjenja = nullptr;
		_brojIgraca = nullptr;
		_brojGolova = nullptr;
	}

	void set(int godRodjenja, int brojIgraca, int brojGolova) {
		if (_godRodjenja == nullptr) _godRodjenja = new int;
		if (_brojIgraca == nullptr) _brojIgraca = new int;
		if (_brojGolova == nullptr) _brojGolova = new int;

		*_godRodjenja = godRodjenja;
		*_brojIgraca = brojIgraca;
		*_brojGolova = brojGolova;
	}

	void ispis() {
		std::cout << "Igrac: " << *_brojIgraca << " (" << *_godRodjenja << ") - " << *_brojGolova << "\n";
	}

	~Fudbaler() {
		delete _godRodjenja; delete _brojIgraca; delete _brojGolova;
		_godRodjenja = _brojIgraca = _brojGolova = nullptr;
	}

};

int najgoriTim(Fudbaler**, int);
int najboljiIgracUNajgoremTimu(Fudbaler**, int);
int najboljiTim(Fudbaler**, int);

int main() {

	int vel = 5;
	Fudbaler** f = new Fudbaler * [vel];
	for (int i = 0; i < vel; i++)
		*(f + i) = new Fudbaler[vel];

	srand(time(NULL));
	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			int godRodj = 1980 + rand() % ((2000 + 1) - 1980);
			int broj = rand() % 30 + 1;
			int golovi = rand() % 5;
			(*(f + i) + j)->set(godRodj, broj, golovi);
		}
	}

	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			(*(f + i) + j)->ispis();
		}
		std::cout << ".....................................\n";
	}

	int najbolji = najboljiTim(f, vel);

	std::cout << "\n\n\nNajbolji tim je sa indexom: " << najbolji << "\n";
	for (int j = 0; j < vel; j++)
	{
		(*(f + najbolji) + j)->ispis();
	}

	int index = najgoriTim(f, vel);
	std::cout << "\n\n\nNajgori tim je sa indexom: " << index << std::endl;
	for (int j = 0; j < vel; j++)
	{
		(*(f + index) + j)->ispis();
	}

	int indeks = najboljiIgracUNajgoremTimu(f, vel);
	std::cout << "\nNajbolji igrac u najgorem timu je: " << index << " - " << indeks << "\n";
	(*(f + index) + indeks)->ispis();

	for (int i = 0; i < vel; i++)
		delete[] * (f + i);
	delete[] f;

	system("pause>nul");
	return 1;
}

int najgoriTim(Fudbaler** f, int vel) {
	float min = 5.0f;
	int index = 0;
	float prosjek = 0.0f;

	for (int i = 0; i < vel; i++)
	{
		prosjek = 0.0f;
		for (int j = 0; j < vel; j++)
		{
			prosjek += *(*(f + i) + j)->_brojGolova;
		}
		prosjek /= float(vel);
		if (prosjek < min) {
			min = prosjek;
			index = i;
		}
	}

	return index;
}
int najboljiIgracUNajgoremTimu(Fudbaler** f, int vel) {
	int index = najgoriTim(f, vel);
	float max = -1.0f;
	int indeks = 0;
	int brojg = 0;

	for (int j = 0; j < vel; j++)
	{
		brojg = *(*(f + index) + j)->_brojGolova;
		if (brojg > max) {
			max = brojg;
			indeks = j;
		}
	}

	return indeks;
}
int najboljiTim(Fudbaler** f, int vel) {
	int index = 0;
	float prosjek = 0.0f;
	float max = 0.0f;

	for (int i = 0; i < vel; i++)
	{
		prosjek = 0.0f;
		for (int j = 0; j < vel; j++)
		{
			prosjek += *(*(f + i) + j)->_brojGolova;
		}
		prosjek /= float(vel);
		if (prosjek > max) {
			max = prosjek;
			index = i;
		}
	}

	return index;
}