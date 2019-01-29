#include <string>
#include <iostream>
#include "Car.h"

using namespace std;

Car::Car() {}

Car::~Car()
{}

Car::Car(string line) : m_line(line) //constructeur
{
	//int index = 2; //on passe le ("b')
	//int index2;

	auto begin = line.begin();
	bool start = false;
	int colonne = 0;
	string::iterator it = line.begin();
	string::iterator end = line.end();
	string::iterator there = it;
	string tmp;
	string::iterator save = it;

	while (it != end)
	{
		there = it;
		if (*it == '\'' && it != save)
		{
			there++;
			while (*there != '\'' && there != end)
			{
				there++;
				if (*there == '\'' && there != (end - 1) && *(there + 1) != '\"')
				{
					//cout << "Ca fait chier ca : " << *(there + 1) << endl;
					there++;
				}
			}
			save = there;
			tmp = line.substr(it - begin + 1, there - it - 1);
			if (colonne == 3) //Identifiant
				m_identifiant = line.substr(it - begin + 1, there - it - 1);
			if (colonne == 5) // modele
				m_model = line.substr(it - begin + 1, there - it - 1);
			if (colonne == 6) //genre
				m_genre = line.substr(it - begin + 1, there - it - 1);
			if (colonne == 10) // enlev
			{
				m_enlev = atoi(tmp.c_str());
				m_enlevs = tmp;
			}
			if (colonne == 14) // liv
			{
				m_liv = atoi(tmp.c_str());
				m_livs = line.substr(it - begin + 1, there - it - 1);
			}
			if (colonne == 17) //villeenlev
			{
				m_villeenleve = atoi(tmp.c_str());
				m_villeenleves = line.substr(it - begin + 1, there - it - 1);
			}
			if (colonne == 18) //villeliv
			{
				m_villeliv = atoi(tmp.c_str());
				m_villelivs = line.substr(it - begin + 1, there - it - 1);
			}
			if (colonne == 19) //prix
				m_prix = atoi(tmp.c_str());
			if (colonne == 26) //VIN
				m_vin = line.substr(it - begin + 1, there - it - 1);
			if (colonne == 28) //ref code
				m_refcode = line.substr(it - begin + 1, there - it - 1);
			if (colonne == 30) //immat
				m_immat = line.substr(it - begin + 1, there - it - 1);

			colonne++;
			//cout << it - begin << *it;
			//cout << line.substr(it - begin + 1, there - it - 1) << endl;
			//cout << it - begin << "  " << there - it << endl;
		}
		it++;
	}
	//cout << "Nombre de colonne : " << colonne << endl;
}

//Faire toutes les methodes de retour variables + faire les atoi des variables en int (pour l'instant initialiser à 42)

string Car::get_identifiant() {return m_identifiant;}

string Car::get_model() {return m_model;}

string Car::get_genre() {return m_genre;}

string Car::get_enlevs() {return m_enlevs;}

int Car::get_enlev() {return m_enlev;}

int Car::get_liv() {return m_liv;}

string Car::get_livs() {return m_livs;}

int Car::get_villeenleve() {return m_villeenleve;}

string Car::get_villeenlevs() {return m_villeenleves;}

int Car::get_villeliv() {return m_villeliv;}

string Car::get_villelivs() {return m_villelivs;}

int Car::get_prix() {return m_prix;}

string Car::get_vin() {return m_vin;}

string Car::get_refcode() {return m_refcode;}

string Car::get_immat() {return m_immat;}