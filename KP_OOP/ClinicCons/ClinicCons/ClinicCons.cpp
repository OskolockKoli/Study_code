// ClinicCons.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include "Disease.h"
#include "Patient.h"
#include "Clinic.h"
#include "Card.h"
#include "PRegistration.h"

using namespace std;
PRegistration* pr = PRegistration::getInstance();

void autoMenu(); // функция для вывода меню

int main()
{
    setlocale(LC_ALL, "Russian");
    pr->readDiseasesFromFile();
    pr->readPatientsFromFile();
    pr->readClinicsFromFile();
    pr->setCards();    
    autoMenu();
}

// реализация объявленных выше функций
void autoMenu() {
    cout << endl;
    int operation = -1;
    while (operation != 0) {
        cout << endl;
        cout << "Выберите операцию" << endl;
        cout << "0: Выход" << endl;
        cout << "1: Добавить диагноз" << endl;
        cout << "2: Удалить диагноз" << endl;
        cout << "3: Показать диагнозы" << endl;
        cout << "4: Добавить пациента" << endl;
        cout << "5: Удалить пациента" << endl;
        cout << "6: Показать пациентов" << endl;
        cout << "7: Добавить больницу" << endl;
        cout << "8: Удалить больницу" << endl;
        cout << "9: Показать больницы" << endl;
        cout << "10: Добавить карточку" << endl;
        cout << "11: Удалить карточку" << endl;
        cout << "12: Показать карточки" << endl;
        cout << "13: Поиск пациентов по отделению" << endl;
        cout << "14: Поиск пациентов по диагнозам" << endl;
        cout << "15: Поиск пациентов по сложности заболевания" << endl;
        cout << "16: Поиск пациентов по количеству диагнозов" << endl;
        cout << "17: Поиск пациентов по продолжительности болезни" << endl;
        cout << "18: Поиск больниц по количеству койко-мест" << endl;
        cout << "19: Поиск пациентов по району" << endl;
        cout << "20: Поиск пациентов по категории диагноза" << endl;
        cin >> operation;

        switch (operation)
        {
        case 1: pr->addDisease();  break;
        case 2: pr->delDisease();  break;
        case 3: pr->showDiseases();  break;
        case 4: pr->addPatient(); break;
        case 5: pr->delPatient();  break;
        case 6: pr->showPatients();  break;
        case 7: pr->addClinic();  break;
        case 8: pr->delClinic();  break;
        case 9: pr->showClinics();  break;
        case 10: pr->addCard();  break;
        case 11: pr->delCard();  break;
        case 12: pr->showCards();  break;
        case 13: pr->searchDepartment();  break;
        case 14: pr->searchDisease();  break;
        case 15: pr->searchHardness();  break;
        case 16: pr->searchDiseasesAmount(); break;
        case 17: pr->searchDuration(); break;
        case 18: pr->searchPlacesAmount();  break;
        case 19: pr->searchDistrict(); break;
        case 20: pr->searchCategory(); break; 
        default: break;
        }
    }
}