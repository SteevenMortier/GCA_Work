#include <iostream>
#include <vector>

class Point
{
public:
	Point();
	Point(double a, double b);
	~Point();
	double x;
	double y;
};

Point::Point(double a, double b) : x(a), y(b)
{}

Point::Point() : x(0.0), y(0.0)
{}

Point::~Point() {};

class Vecteur
{
public:
	Vecteur();
	~Vecteur();
	double x;
	double y;
};

Vecteur::Vecteur(): x(0.0), y(0.0)
{}

Vecteur::~Vecteur() {};

class Car
{
public:
	Car(double lenght, double hight);
	~Car();
	std::vector<Point> m_coords;
	std::vector<Point> m_coords_init;
	double m_lenght;
	double m_hight;
	double m_shift;
};

Car::Car(double lenght, double hight) : m_lenght(lenght), m_hight(hight), m_shift(0.0)
{}

Car::~Car()
{
	//std::cout << "Called destructor of car" << std::endl;
	m_coords.clear();
}

int intersectsegment(Point A,Point B,Point I,Point P)
{
	Vecteur D,E;
	double u, t;
 	D.x = B.x - A.x;
	D.y = B.y - A.y;
	E.x = P.x - I.x;
	E.y = P.y - I.y;
	double denom = D.x * E.y - D.y * E.x;
 	if (denom == 0)
		return -1;
	t = - (A.x * E.y - I.x * E.y - E.x * A.y + E.x * I.y) / denom;
	if (t < 0 || t >= 1)
		return 0;
	u = - (-D.x *A.y + D.x * I.y + D.y * A.x - D.y * I.x) / denom;
	if (u < 0 || u >= 1)
 		return 0;
	return 1;
}

bool Collision(Car tab, int nbp, Point P)
{
	int		i;
	Point	I;
	I.x = 1000000 + rand() % 100;
	I.y = 1000000 + rand() % 100;
	int nbintersections = 0;
	for(i = 0; i < nbp; i++)
	{
		Point A = tab.m_coords[i];
		Point B;
		if (i == nbp - 1)
			B = tab.m_coords[0];
		else
         		B = tab.m_coords[i + 1];
     		int iseg = intersectsegment(A, B, I, P);
     		if (iseg == -1)
         		return Collision(tab, nbp, P);
     	nbintersections += iseg;
  	}
  	if (nbintersections % 2 == 1)
     		return true;
  	else
     		return false;
}

bool car_collision(Car car1, int nbp_car1, Car car2, int nbp_car2)
{
	for (auto car : car2.m_coords)
	{
		if (Collision(car1, nbp_car1, car))
			return false;
	}
	for (auto car : car1.m_coords)
	{
		if (Collision(car2, nbp_car2, car))
			return false;
	}
	return true;
}

/********* End collision algo **********/
/********* Start Using the Collision algo *********/

double limite_camion = 15000.0f;

bool move_car(std::vector<Car> *Lot, int cars_placed, std::vector<Car>* map)
{
	int index;

	for (auto map_c : (*map))
	{
		printf("map size : (%d)\n", (*map).size());
		printf("Combien de points [%d], et combien vaut le shift [%f]\n", map_c.m_coords.size(), (*Lot)[cars_placed].m_shift);
		while ((*Lot)[cars_placed].m_shift < limite_camion - (*Lot)[cars_placed].m_lenght && !car_collision(map_c, map_c.m_coords.size(), (*Lot)[cars_placed], (*Lot)[cars_placed].m_coords.size()))
		{
			(*Lot)[cars_placed].m_shift += 10.0f;
			//printf("\e[31mLenght car(%f) + his shift(%f) = %f\e[39m\n",(*Lot)[cars_placed].m_lenght, (*Lot)[cars_placed].m_shift, (*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift);
			if ((*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift >= limite_camion)
			{
				printf("\e[31mLenght car(%f) + it shift(%f) = %f\e[39m\n",(*Lot)[cars_placed].m_lenght, (*Lot)[cars_placed].m_shift, (*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift);
				return false;
			}
			index = 0;
			for (auto tmp : (*Lot)[cars_placed].m_coords) // les coords sont obérentes
			{
				(*Lot)[cars_placed].m_coords[index].x = (*Lot)[cars_placed].m_coords_init[index].x + (*Lot)[cars_placed].m_shift;
				index++;
			}
		}
		if ((*Lot)[cars_placed].m_shift + (*Lot)[cars_placed].m_lenght >= limite_camion)
		{
			return false;
		}
	}
	std::cout << "\e[92mPlaced Car" << cars_placed << " at pos : " << (*Lot)[cars_placed].m_shift << "\e[39m" << std::endl;
	return true;
}

int place_cars(std::vector<Car>* Lot, int number_cars, std::vector<Car>* map, int index)
{
	static int cars_placed;
	//std::cout << "Car_placed (index dont on s'occupe de placer) : " << cars_placed << std::endl;
	//std::cout << "cars_placed : " << cars_placed << " / " << number_cars << std::endl;
	if (cars_placed == number_cars)
		return 1;
	else
	{
		std::cout << "\e[33mSEGV with car placed = " << cars_placed << "\e[39m" << std::endl;
		if (move_car(Lot, cars_placed, map)) // we move following car following the route until it can be placed
		{
			(*map).push_back((*Lot)[cars_placed]);
			//printf("There is now %d cars on the map\n", (*map).size());
			cars_placed += 1;
		}
		else
		{
			(*map).pop_back();
			printf("\e[31mCar%d as been deleted from the map\e[39m\n", (*map).size() - 1);
			index = 0;
			for (auto tmp : (*Lot)[cars_placed].m_coords)
			{
				(*Lot)[cars_placed].m_coords[index].x = (*Lot)[cars_placed].m_coords_init[index].x;
				index++;
			}
			(*Lot)[cars_placed].m_shift = 0.0f;
			cars_placed -= 1;
			if ((*map).size() <= 0 && (*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift >= limite_camion)
				return -1;
			(*Lot)[cars_placed].m_shift += 10.0f;
			index = 0;
			for (auto tmp : (*Lot)[cars_placed].m_coords)
			{
				(*Lot)[cars_placed].m_coords[index].x  = (*Lot)[cars_placed].m_coords_init[index].x + (*Lot)[cars_placed].m_shift;
				index++;
			}
		}
		if (place_cars(Lot, number_cars, map, index) == -1 && (*map).size() < number_cars)
			return -1;
	}
}

int main()
{
	std::vector<Car> Lot;
	std::vector<Car> map;
	Car carA(5271, 1496);
	Car carB(4924, 1797);
	Car carC(4924, 1797);
	double shift = 0;
	Point P;
	int index = 0;

	P.x = 1500;
	P.y = 1500;
	//Points : Mercedes class S Long
	carA.m_coords.push_back(Point(0, 0));
	carA.m_coords.push_back(Point(5271, 0));
	carA.m_coords.push_back(Point(5271, 897.6));
	carA.m_coords.push_back(Point(4054.45, 897.6));
	carA.m_coords.push_back(Point(3109.89, 1496));
	carA.m_coords.push_back(Point(1317.75, 1496));
	carA.m_coords.push_back(Point(527.1, 1047.2));
	carA.m_coords.push_back(Point(0, 1047.2));
	carA.m_coords_init = carA.m_coords;
	Lot.push_back(carA);
	//Points : Mercedes CLE SUV
	carB.m_coords.push_back(Point(0, 0));
	carB.m_coords.push_back(Point(4924, 0));
	carB.m_coords.push_back(Point(4924, 1168.05));
	carB.m_coords.push_back(Point(3787.54, 1347.75));
	carB.m_coords.push_back(Point(3030.23, 1797));
	carB.m_coords.push_back(Point(757.31, 1797));
	carB.m_coords.push_back(Point(0, 1347.75));
	carB.m_coords_init = carB.m_coords;
	Lot.push_back(carB);

	carC.m_coords.push_back(Point(0, 0));
	carC.m_coords.push_back(Point(4924, 0));
	carC.m_coords.push_back(Point(4924, 1168.05));
	carC.m_coords.push_back(Point(3787.54, 1347.75));
	carC.m_coords.push_back(Point(3030.23, 1797));
	carC.m_coords.push_back(Point(757.31, 1797));
	carC.m_coords.push_back(Point(0, 1347.75));
	carC.m_coords_init = carB.m_coords;
	Lot.push_back(carC);

	if (place_cars(&Lot, Lot.size(), &map, index) == -1)
	{
		printf("Impossible de placer le Lot\n");
	}
	else
	{
		for (auto tmp : Lot)
		{
			std::cout << "We placed a car at " << tmp.m_shift << "mm" <<  std::endl;
			std::cout << "His lenght was " << tmp.m_lenght << "mm" <<  std::endl;
		}
	}
	carA.m_coords.clear();
	carB.m_coords.clear();
	carC.m_coords.clear();
}
