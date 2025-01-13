#pragma once
#include <iostream>
#include <string>
#include "Category.h"
using namespace std;
class Disease
{
private:
	Category category;
	string title;	

public: // методы для получения значений полей
	Category get_category();
	string get_title();	

	// методы для установки значений полей
	void set_category(string c);
	void set_title(string t);	

	Disease(Category c, string t)  // конструктор класса с параметрами
	{
		category = c;
		title = t;		
	}

	Disease() // конструктор класса без параметров
	{
		category = Category();
		title = "";		
	}

	// перегрузка операторов >> и << для записи объектов класса в файл и чтения из файла
	friend std::istream& operator >>(std::istream& is, Disease& dis) {
		if (is) {
			is
				>> dis.category
				>> dis.title				
				;
		}
		return is;
	}

#pragma warning(default:4716)
	friend std::ostream& operator <<(std::ostream& os, Disease const& dis)
	{
		os
			<< dis.category << ' '
			<< dis.title << ' '			
			<< '\n'
			;
	}
};