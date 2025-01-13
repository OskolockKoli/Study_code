#pragma once
#include <iostream>
#include <string>
#include "District.h"

using namespace std;
class Clinic
{
private:
	District district;
	int places;
	string title;	
public:
	// методы для получения значений полей
	District get_district();
	int get_places();
	string get_title();

	// методы для установки значений полей
	void set_district(District d);
	void set_places(int p);
	void set_title(string t);

	Clinic(District d, int p, string t) // конструктор класса с параметрами
	{
		district = d;
		places = p;
		title = t;
	}

	Clinic() // конструктор класса без параметров
	{
		district = District();
		places = 0;
		title = "";
	}

	// перегрузка операторов >> и << для записи объектов класса в файл и чтения из файла
	friend std::istream& operator >>(std::istream& is, Clinic& cl) {
		if (is) {
			is
				>> cl.district
				>> cl.places
				>> cl.title
				;
		}
		return is;
	}

#pragma warning(default:4716)
	friend std::ostream& operator <<(std::ostream& os, Clinic const& cl)
	{
		os
			<< cl.district << ' '
			<< cl.places << 0
			<< cl.title << ' '
			<< '\n'
			;
	}
};

