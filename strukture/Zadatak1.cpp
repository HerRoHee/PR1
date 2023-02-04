// Zadatak
/* Kreirati dinamički dvodimenzionalni niz čiji su elementi objekti tipa fudbaler
(fudbaler je struktura čija su obilježja data u nastavku).
Omogućiti korisniku da unese dimenzije niza.
struct fudbaler
{
    int* godRodjenja;
    int* brojIgraca;
    int* golovi;
};
Redovi dvodimenzionalnog niza predstavljaju
različite timove, a kolone predstavljaju igrače u tim timovima. Omogućiti korisniku unos svih
podataka za sve igrače, te napraviti (i testirati u main funkciji) funkciju koja će pronaći
tim sa najvećim prosjekom. Zatim napraviti (i testirati u main funkciji) funkciju koja će
pronaći igrača sa najviše golova u timu sa najlošijim prosjekom golova. Radi lakšeg
testiranja programa obavezno u funkciji unosa podataka omogućiti da se podaci generišu kao sljedeće:
godRodjenja: 1980 + rand() % ((2000 + 1) - 1980) // Generiše brojeve u rangu 1980 - 2000
brojIgraca: rand() % 30 + 1
golovi: rand() % 5 */
#include<iostream>

struct FootballPlayer {
    int* _birthYear{ nullptr };
    int* _playerNumber{ nullptr };
    int* _goals{ nullptr };

    FootballPlayer() { // defalut constructor
        _birthYear = nullptr;
        _playerNumber = nullptr;
        _goals = nullptr;
    }

    FootballPlayer(int birthYear, int playerNumber, int goals) { // custom constructor
        allocate();
        *_birthYear = birthYear;
        *_playerNumber = playerNumber;
        *_goals = goals;
    }

    void allocate() {
        if (_birthYear == nullptr) _birthYear = new int;
        if (_playerNumber == nullptr) _playerNumber = new int;
        if (_goals == nullptr) _goals = new int;
    }

    // set functions
    void setBirthYear(int birthYear) { 
        if (_birthYear == nullptr) _birthYear = new int; 
        *_birthYear = birthYear; 
    }
    void setPlayerNumber(int playerNumber) { 
        if (_playerNumber == nullptr) _playerNumber = new int; 
        *_playerNumber = playerNumber; 
    }
    void setGoals(int goals) { 
        if (_goals == nullptr) _goals = new int; 
        *_goals = goals; 
    }

    // get functions
    int getBirthYear() const { return *_birthYear; }
    int getPlayerNumber() const { return *_playerNumber; }
    int getGoals() const { return *_goals; }

    void set(int birthYear, int playerNumber, int goals) { // default set
        delete _birthYear; delete _playerNumber; delete _goals;
        allocate();
        *_birthYear = birthYear;
        *_playerNumber = playerNumber;
        *_goals = goals;
    }

    void set(FootballPlayer& f) { // copy set
        allocate();
        *_birthYear = f.getBirthYear();
        *_playerNumber = f.getPlayerNumber();
        *_goals = f.getGoals();
    }

    void print() {
        std::cout << "Football player: " << *_playerNumber << " (" << *_birthYear << ") \n";
        std::cout << "Goals: " << *_goals << "\n";
        std::cout << "..........................................................\n";
    }

    ~FootballPlayer() {
        delete _birthYear; delete _playerNumber; delete _goals;
    }

};

void test1();
int bestTeam(FootballPlayer*, int, int);
void worstTeam(FootballPlayer*, int&, int&);

int main() {

    test1();

	system("pause>nul");
	return 1;
}

void test1() {

    int rows; std::cout << "Enter rows: "; std::cin >> rows;
    int cols; std::cout << "Enter columns: "; std::cin >> cols;

    FootballPlayer* f = new FootballPlayer[rows * cols];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int birthYear = 1980 + rand() % ((2000 + 1) - 1980);
            int playerNumber = rand() % 30 + 1;
            int goals = rand() % 5;
            (f + i * rows + j)->set(birthYear, playerNumber, goals);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            (f + i * rows + j)->print();
        }
        std::cout << "-----------------------------------------------------\n";
    }

    std::cout << "\n\n****************************************************\n";

    int index = bestTeam(f, rows, cols);
    std::cout << "The best team is [" << index << "]: \n";
    for (int j = 0; j < cols; j++)
    {
        (f + index*rows + j)->print();
    }

    std::cout << "\n\n****************************************************\n\n";

    int copyRows = rows;
    worstTeam(f, rows, cols);
    std::cout << "Best player in the worst team is [" << rows << "][" << cols << "]:\n";
    (f + copyRows*rows + cols)->print();

    delete[] f;
}

int bestTeam(FootballPlayer* f, int rows, int cols) {
    float max = -1.00f;
    float avrg = 0.00f;
    int index = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            avrg += (*(f + i * rows + j)).getGoals();
        }
        avrg /= float(cols);
        if (avrg > max) { max = avrg; index = i; }
    }

    return index;
}

void worstTeam(FootballPlayer* f, int& rows, int& cols) {
    float min = 10.00f;
    float avrg = 0.00f;
    int index = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            avrg += (*(f + i * rows + j)).getGoals();
        }
        avrg /= float(cols);
        if (avrg < min) { min = avrg; index = i; }
    }

    int max = 0;
    int indeks = 0;
    for (int j = 0; j < cols; j++)
    {
        if( (f + index*rows + j)->getGoals() > max) { 
            max = (f + index*rows + j)->getGoals();
            indeks = j;
        }
    }

    rows = index;
    cols = indeks;
}