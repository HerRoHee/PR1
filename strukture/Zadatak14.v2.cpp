#include<iostream>
#include<cstdlib>

struct Student {
	int _ID = 0;
	char* _imePrezime{ nullptr };
	float* _prosjek{ nullptr };

	Student() {
		_ID = 0;
		_imePrezime = nullptr;
		_prosjek = nullptr;
	}

	void set(int ID, const char* imePrezime, float prosjek) {
		_ID = ID;

		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);

		if (_prosjek == nullptr) _prosjek = new float;
		*_prosjek = prosjek;
	}

	void print() {
		std::cout << _ID << " - " << _imePrezime << " [" << *_prosjek << "] \n";
	}

	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
		delete _prosjek; _prosjek = nullptr;
	}

};

int najboljiFakultet(Student**, int);
void najboljiStudent(Student**, int, int&, int&);

int main() {
	
	srand(time(NULL));

	int vel = 5;
	Student** s = new Student * [vel];

	for (int i = 0; i < vel; i++)
		*(s + i) = new Student[vel];
	
	{
		int ID = 0;
		for (int i = 0; i < vel; i++)
		{
			for (int j = 0; j < vel; j++)
			{
				float prosjek = 4;
				prosjek += (rand() % 50 / float(10)) + 1;
				(*(s + i) + j)->set(ID + 1, "student", prosjek);
				ID++;
			}
		}
	}

	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			(*(s + i) + j)->print();
		}
		std::cout << ".................................\n";
	}

	int index = najboljiFakultet(s, vel);
	std::cout << "\n\n\nNajbolji fakultet je sa indexom: " << index << "\n";
	for (int j = 0; j < vel; j++)
		(*(s + index) + j)->print();

	int StudentI = 0;
	int StudentJ = 0;
	najboljiStudent(s, vel, StudentI, StudentJ);
	std::cout << "\n\n\nNajbolji studnet je: [" << StudentI << "][" << StudentJ << "]\n";
	(*(s + StudentI) + StudentJ)->print();

	for (int i = 0; i < vel; i++)
		delete[] *(s + i);
	delete[] s;

	system("pause>nul");
	return 1;
}

int najboljiFakultet(Student** s, int vel) {
	int index = 0;
	float prosjek = 0.0f;
	float max = 0.0f;

	for (int i = 0; i < vel; i++)
	{
		prosjek = 0.0f;
		for (int j = 0; j < vel; j++)
		{
			prosjek += *(*(s + i) + j)->_prosjek;
		}
		prosjek /= float(vel);
		if (prosjek > max) {
			max = prosjek;
			index = i;
		}
	}

	return index;

}
void najboljiStudent(Student** s, int vel, int& StudentI, int& StudentJ) {
	float max = 0.0f;
	for (int i = 0; i < vel; i++)
	{
		for (int j = 0; j < vel; j++)
		{
			if (*(*(s + i) + j)->_prosjek > max) {
				max = *(*(s + i) + j)->_prosjek;
				StudentI = i;
				StudentJ = j;
			}
		}
	}
}