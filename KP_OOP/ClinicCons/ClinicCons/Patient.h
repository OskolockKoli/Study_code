#pragma once
#include <iostream>
#include <string>
using namespace std;
class Patient
{
private:
	string lname;
	string name;
	string pat;
	string address;
	string phone;

public: // методы для получения значений полей
	string get_lname();
	string get_name();
	string get_pat();
	string get_address();
	string get_phone();

	// методы для установки значений полей
	void set_lname(string ln);
	void set_name(string n);
	void set_pat(string p);
	void set_address(string a);
	void set_phone(string p);

	Patient(string ln, string n, string pat, string a, string p) // конструктор класса с параметрами
	{
		lname = ln;
		name = n;
		pat = pat;
		address = a;
		phone = p;
	}

	Patient() // конструктор класса без параметров
	{
		lname = "";
		name = "";
		pat = "";
		address = "";
		phone = "";
	}

	// перегрузка операторов >> и << для записи объектов класса в файл и чтения из файла
	friend std::istream& operator >>(std::istream& is, Patient& pat) {
		if (is) {
			is
				>> pat.lname
				>> pat.name
				>> pat.pat
				>> pat.address
				>> pat.phone
				;
		}
		return is;
	}

#pragma warning(default:4716)
	friend std::ostream& operator <<(std::ostream& os, Patient const& pat)
	{
		os
			<< pat.lname << ' '
			<< pat.name << ' '
			<< pat.pat << ' '
			<< pat.address << ' '
			<< pat.phone << ' '
			<< '\n'
			;
	}
};