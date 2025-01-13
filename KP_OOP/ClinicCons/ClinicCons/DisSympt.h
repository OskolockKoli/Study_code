#pragma once
#include <iostream>
#include <string>
#include "Disease.h"
#include "Symptom.h"

class DisSympt
{
private:
	Disease disease;
	Symptom symptom;

public: // методы для получения значений полей	
	Disease get_disease();
	Symptom get_symptom();

	// методы для установки значений полей	
	void set_disease(Disease d);
	void set_symptom(Symptom s);

	DisSympt(Disease d, Symptom s)  // конструктор класса с параметрами
	{
		disease = d;
		symptom = s;
	}

	DisSympt() // конструктор класса без параметров
	{
		disease = Disease();
		symptom = Symptom();
	}

	// перегрузка операторов >> и << для записи объектов класса в файл и чтения из файла
	friend std::istream& operator >>(std::istream& is, DisSympt& ds) {
		if (is) {
			is
				>> ds.disease
				>> ds.symptom				
				;
		}
		return is;
	}

#pragma warning(default:4716)
	friend std::ostream& operator <<(std::ostream& os, DisSympt const& ds)
	{
		os
			<< ds.disease << ' '
			<< ds.symptom << ' '			
			<< '\n'
			;
	}
};

