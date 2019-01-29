#pragma once
#ifndef CAR_H
#define CAR_H

class Car
{
	public:
		Car();
		Car(std::string str);
		std::string get_identifiant();
		std::string get_model();
		std::string get_genre();
		std::string get_enlevs();
		int get_enlev();
		int get_liv();
		std::string get_livs();
		int get_villeenleve();
		std::string get_villeenlevs();
		int get_villeliv();
		std::string get_villelivs();
		int get_prix();
		std::string get_vin();
		std::string get_refcode();
		std::string get_immat();
		~Car();
		std::string m_line;

	private:
		std::string m_identifiant;
		std::string m_model;
		std::string m_genre;
		int m_enlev;
		std::string m_enlevs;
		int m_liv;
		std::string m_livs;
		std::string m_typesiteliv;
		int m_villeenleve;
		std::string m_villeenleves;
		int m_villeliv;
		std::string m_villelivs;
		int m_prix;
		std::string m_vin;
		std::string m_refcode;
		std::string m_immat;
};

#endif // !CAR_H

