#pragma once
#include <iostream>
#include <string>
#include "Disease.h"
#include "Patient.h"
#include "Clinic.h"
#include "department.h"

using namespace std;

class Card
{
private:
	int duration;	
	Disease disease;
	Patient patient;
	string hardness;
	Clinic clinic;
	int place;
	Department department;

public:
	// методы для получения значений полей	
	int get_duration();
	Disease get_disease();
	Patient get_patient();
	string get_hardness();
	Clinic get_clinic();
	int get_place();
	Department get_department();

	// методы для установки значений полей	
	void set_duration(int d);
	void set_disease(Disease d);
	void set_patient(Patient p);
	void set_hardness(string h);
	void set_clinic(Clinic c);
	void set_place(int p);
	void set_department(Department d);

	Card(int du, Disease d, Patient pt, string h, Clinic c, int p, Department dp) // конструктор класса с параметрами
	{
		duration = du;
		disease = d;
		patient = pt;
		hardness = h;
		clinic = c;
		place = p;
		department = dp;
	}

	Card() // конструктор класса без параметров
	{
		duration = 0;
		hardness = "";		
		place = 0;
		department = Department();
	}
};

