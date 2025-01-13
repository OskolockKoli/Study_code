#pragma once
class PRegistration
{
private:
	static PRegistration* instance;
	PRegistration() {}
	PRegistration(const PRegistration&);
	PRegistration& operator = ( PRegistration& );

public:
	static PRegistration* getInstance() {
		if (!instance)
			instance = new PRegistration();
		return instance;
	}

	// получение данных из файлов
	void readDiseasesFromFile();
	void readPatientsFromFile();
	void readClinicsFromFile();
	void readCategoriesFromFile();
	void readSymptomsFromFile();
	void readDisSymptomsFromFile();
	void readDistrictsFromFile();
	void readDepartmentsFromFile();

	void showSympts();


	void addDisease(); // функция для добавления записи о диагнозе
	void delDisease();  // удалить диагнозы
	void showDiseases(); // показать диагнозы

	void addPatient(); // добавление пациента
	void delPatient(); // удалить пациента
	void showPatients(); // показать пациентов

	void addClinic(); // добавление клиники
	void delClinic(); // удалить клинику
	void showClinics(); // показать клиники

	void addCard(); // добавление клиники
	void delCard(); // удалить клинику
	void showCards(); // показать клиники

	void setCards();  // создание пустых объектов Card

	// поиск данных
	void searchDepartment();
	void searchDisease();
	void searchHardness();
	void searchPlacesAmount();
	void searchDiseasesAmount();
	void searchDuration();
	void searchDistrict();
	void searchCategory();
};

