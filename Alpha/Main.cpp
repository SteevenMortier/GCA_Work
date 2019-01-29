#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <SDL.h>
#include "Car.h"
#include "SceneMenu.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#include <thread>
#include <mutex>

using namespace std;

list<Car> get_infos()
{
	ifstream file("P:/smortier/encoursTRP.csv");
	int nb_cars = 0;
	int counter = 0;
	string str;
	list<Car> list_car;


	//cout << "We can now start to dev the excel pick up info" << endl;

	if (!file)
		return (list_car);

	getline(file, str);
	getline(file, str);
	while (getline(file, str))
	{
		Car test(str);
		list_car.push_back(test);
		counter++;
	}

	for (Car test : list_car)
	{
		cout << "Info Voiture :" << endl;
		cout << "Identifiant : " << test.get_identifiant() << endl;
		cout << "Modele : " << test.get_model() << endl;
		cout << "Genre : " << test.get_genre() << endl;
		cout << "Enleve : " << test.get_enlev() << " + " << test.get_enlevs() << endl;
		cout << "Liv : " << test.get_liv() << " + " << test.get_livs() << endl;
		cout << "Ville Enlev = " << test.get_villeenleve() << " + " << test.get_villeenlevs() << endl;
		cout << "VilleLiv = " << test.get_villeliv() << " + " << test.get_villelivs() << endl;
		cout << "Prix = " << test.get_prix() << endl;
		cout << "VIN : " << test.get_vin() << endl;
		cout << "Ref Code : " << test.get_refcode() << endl;
		cout << "Immat : " << test.get_immat() << endl;
		cout << "----------------------------" << endl;
	}

	file.close();

	return list_car;
}

/*void exec_py()
{
	system("cd .. && py get_file.py");
}*/

int main(int ac, char **av)
{
	std::thread t1([]() { system("cd .. && py get_file.py"); });
	//t1.join();
	get_infos();
	SceneMenu menu("Alpha", 1280, 720);

	if (menu.init_window() == false)
	{
		cout << "Ca marche pas" << endl;
		return 0;
	}

	menu.main_loop();

	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}