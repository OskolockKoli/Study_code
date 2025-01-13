#pragma once
#include <iostream>
#include <string>
using namespace std;
class Category
{
private:
	string title;

public: // методы для получения значений полей	
	string get_title();

	// методы для установки значений полей	
	void set_title(string t);

	Category(string t)  // конструктор класса с параметрами
	{
		title = t;
	}

	Category() // конструктор класса без параметров
	{
		title = "";
	}

	// перегрузка операторов >> и << для записи объектов класса в файл и чтения из файла
	friend std::istream& operator >>(std::istream& is, Category& dis) {
		if (is) {
			is
				>> dis.title
				;
		}
		return is;
	}

#pragma warning(default:4716)
	friend std::ostream& operator <<(std::ostream& os, Category const& dis)
	{
		os
			<< dis.title << ' '
			<< ' '
			;
	}
};

