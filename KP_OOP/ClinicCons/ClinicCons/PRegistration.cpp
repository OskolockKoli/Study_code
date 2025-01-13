#include <fstream>
#include "PRegistration.h"
#include "Disease.h"
#include "Patient.h"
#include "Clinic.h"
#include "Card.h"
#include "Symptom.h"
#include "DisSympt.h"
#include "District.h"
#include "department.h"
#include "Category.h"
PRegistration* PRegistration::instance = 0;

const int _size = 10, _rows = 100, _lines = 50; // константа, размер массива с записями
Disease diseases[_size]; // массив с записями по диагнозам
Patient patients[_size]; // массив с записями по пациентам
Clinic clinics[_size]; // массив с записями по клиникам
Card cards[_rows]; // массив с записями по карточкам

Symptom symptoms[_lines]; // массив с записями по симптомам
DisSympt dis_simpts[_rows]; // массив с записями по симптомам болезней
District districts[_size]; // массив с записями по районам
Department departments[_lines]; // массив с записями по отделениям
Category categories[_lines]; // массив с записями по категориям болезней


void PRegistration::readCategoriesFromFile()
{
    ifstream fileIn;
    fileIn.open("categories.txt");
    Category _c;
    int i = 0;
    while (fileIn >> _c) {
        categories[i] = _c;
        i++;
    }
    fileIn.close();
}
void PRegistration::readDiseasesFromFile() {
    ifstream fileIn;
    fileIn.open("diseases.txt");
    Disease _dis;
    int i = 0;
    while (fileIn >> _dis) {
        diseases[i] = _dis;
        i++;
    }
    fileIn.close();
}
void PRegistration::readPatientsFromFile() {
    ifstream fileIn;
    fileIn.open("patients.txt");
    Patient _p;
    int i = 0;
    while (fileIn >> _p) {
        patients[i] = _p;
        i++;
    }
    fileIn.close();
}
void PRegistration::readClinicsFromFile() {
    ifstream fileIn;
    fileIn.open("clinics.txt");
    Clinic _c;
    int i = 0;
    while (fileIn >> _c) {
        clinics[i] = _c;
        i++;
    }
    fileIn.close();
}
void PRegistration::readSymptomsFromFile()
{
    ifstream fileIn;
    fileIn.open("symptoms.txt");
    Symptom _s;
    int i = 0;
    while (fileIn >> _s) {
        symptoms[i] = _s;
        i++;
    }
    fileIn.close();
}
void PRegistration::readDisSymptomsFromFile()
{
    ifstream fileIn;
    fileIn.open("dis_sympt.txt");
    DisSympt _s;
    int i = 0;
    while (fileIn >> _s) {
        dis_simpts[i] = _s;
        i++;
    }
}
void PRegistration::readDistrictsFromFile()
{
    ifstream fileIn;
    fileIn.open("districts.txt");
    District _d;
    int i = 0;
    while (fileIn >> _d) {
        districts[i] = _d;
        i++;
    }
}
void PRegistration::readDepartmentsFromFile()
{
    ifstream fileIn;
    fileIn.open("departments.txt");
    Department _d;
    int i = 0;
    while (fileIn >> _d) {
        departments[i] = _d;
        i++;
    }
}

void setDiseases()
{
    for (int i = 0; i < _size; i++) {
        diseases[i] = Disease();
    }
}
void PRegistration::addDisease() {
    cout << endl;
    string cat, title;
    bool flag = false;
    cout << "Введите категорию диагноза: ";
    cin >> cat;
    cout << "Введите название диагноза: ";
    cin >> title;
    for (int i = 0; i < _size; i++) {
        if (diseases[i].get_title() == "") {
            diseases[i].set_category(cat);
            diseases[i].set_title(title);
            flag = true;
            break;
        }
    }
    if (flag) cout << "Запись добавлена." << endl;
    else cout << "Нет свободного места. Удалите записи." << endl;
}
void PRegistration::delDisease() {
    cout << endl;
    int id;
    cout << "Введите номер диагноза: ";
    cin >> id;
    if (id < 0 || id > 9)
    {
        cout << "Номер неверен." << endl;
        return;
    }
    diseases[id].set_category("");
    diseases[id].set_title("");
    cout << "Запись с номером " << id << " удалена." << endl;
}
void PRegistration::showDiseases() {
    bool flag = false;
    string sympt = "";
    for (int i = 0; i < _size; i++) {
        if (diseases[i].get_category().get_title() != "")
        {
            for (int j = 0; j < _rows; j++)
            {
                if (dis_simpts[j].get_disease().get_title() == diseases[i].get_title())
                {
                    sympt = dis_simpts[j].get_symptom().get_title();
                }
            }
            if(sympt == "") cout << "--------------------------------------------------------------\n" << "ID: " << i << " | Категория: " << diseases[i].get_category() << "| Название: " << diseases[i].get_title() << " |" << "\n--------------------------------------------------------------\n" << endl;
            else cout << "--------------------------------------------------------------\n" << "ID: " << i << " | Категория: " << diseases[i].get_category() << "| Название: " << diseases[i].get_title() << " | Симптомы: " << sympt << " |" << "\n--------------------------------------------------------------\n" << endl;
            flag = true;
        }
    }
    if (!flag) cout << "Записи отсутствуют." << endl;
}

void PRegistration::addPatient() {
    cout << endl;
    string lname, name, pat, address, phone;
    bool flag = false;
    cout << "Введите фамилию пациента: ";
    cin >> lname;
    cout << "Введите имя пациента: ";
    cin >> name;
    cout << "Введите отчество пациента: ";
    cin >> pat;
    cout << "Введите адрес пациента: ";
    cin >> address;
    cout << "Введите телефон пациента: ";
    cin >> phone;
    for (int i = 0; i < _size; i++) {
        if (patients[i].get_lname() == "") {
            patients[i].set_lname(lname);
            patients[i].set_name(name);
            patients[i].set_pat(pat);
            patients[i].set_address(address);
            patients[i].set_phone(phone);
            flag = true;
            break;
        }
    }
    if (flag) cout << "Запись добавлена." << endl;
    else cout << "Нет свободного места. Удалите записи." << endl;
}
void PRegistration::delPatient() {
    cout << endl;
    int id;
    cout << "Введите номер пациента: ";
    cin >> id;
    if (id < 0 || id > 9)
    {
        cout << "Номер неверен." << endl;
        return;
    }
    patients[id].set_lname("");
    patients[id].set_name("");
    patients[id].set_pat("");
    patients[id].set_address("");
    patients[id].set_phone("");
    cout << "Запись с номером " << id << " удалена." << endl;
}
void PRegistration::showPatients() {
    bool flag = false;
    for (int i = 0; i < _size; i++) {
        if (patients[i].get_lname() != "")
        {
            cout << "-------------------------------------------------------------------------------\n" << "ID: " << i << " | ФИО: " << patients[i].get_lname() + " " + patients[i].get_name() + " " + patients[i].get_pat() << " | Адрес: " << patients[i].get_address() << " | Телефон: " << patients[i].get_phone() << " |" << "\n-------------------------------------------------------------------------------\n" << endl;
            flag = true;
        }
    }
    if (!flag) cout << "Записи отсутствуют." << endl;
}

void PRegistration::addClinic()
{
    cout << endl;
    string dis, title;
    int pl, iddis;
    bool flag = false;
    cout << "Введите номер района: ";
    cin >> iddis;
    cout << "Введите название клиники: ";
    cin >> title;
    cout << "Введите количество койко-мест в клинике: ";
    cin >> pl;

    for (int i = 0; i < _size; i++) {
        if (clinics[i].get_title() == "") {
            clinics[i].set_district(districts[iddis]);
            clinics[i].set_title(title);
            clinics[i].set_places(pl);
            flag = true;
            break;
        }
    }
    if (flag) cout << "Запись добавлена." << endl;
    else cout << "Нет свободного места. Удалите записи." << endl;
}
void PRegistration::delClinic()
{
    cout << endl;
    int id;
    cout << "Введите номер клиники: ";
    cin >> id;
    if (id < 0 || id > 9)
    {
        cout << "Номер неверен." << endl;
        return;
    }
    clinics[id].set_district(District());
    clinics[id].set_title("");
    clinics[id].set_places(0);
    cout << "Запись с номером " << id << " удалена." << endl;
}
void PRegistration::showClinics()
{
    bool flag = false;
    for (int i = 0; i < _size; i++) {
        if (clinics[i].get_title() != "")
        {
            cout << "-------------------------------------------------------------------------------\n" << "ID: " << i << " | Район: " << clinics[i].get_district() << "| Название: " << clinics[i].get_title() << " | Кол-во мест: " << clinics[i].get_places() << " |" << "\n-------------------------------------------------------------------------------\n" << endl;
            flag = true;
        }
    }
    if (!flag) cout << "Записи отсутствуют." << endl;
}

void PRegistration::setCards()
{
    for (int i = 0; i < _rows; i++) {
        cards[i] = Card();
    }
}
void PRegistration::addCard()
{
    cout << endl;
    string hard, dep;
    int place, dis, pt, cl, dur;
    bool flag = false;
    cout << "Введите длительность болезни: ";
    cin >> dur;
    cout << "Введите номер диагноза: ";
    cin >> dis;
    cout << "Укажите тяжесть заболевания: ";
    cin >> hard;
    cout << "Введите номер пациента: ";
    cin >> pt;
    cout << "Введите номер клиники: ";
    cin >> cl;
    cout << "Введите номер койко-места в клинике: ";
    cin >> place;
    cout << "Введите отделение в клинике: ";
    cin >> dep;
    if (pt < 0 || pt > 9 || cl < 0 || cl > 9 || dis < 0 || dis > 9)
    {
        cout << "Введены неверные данные" << endl;
        return;
    }
    for (int i = 0; i < _rows; i++) {
        if (cards[i].get_duration() == 0) {
            cards[i].set_duration(dur);
            cards[i].set_disease(diseases[dis]);
            cards[i].set_hardness(hard);
            cards[i].set_patient(patients[pt]);
            cards[i].set_clinic(clinics[cl]);
            cards[i].set_place(place);
            cards[i].set_department(dep);
            flag = true;
            break;
        }
    }
    if (flag) cout << "Запись добавлена." << endl;
    else cout << "Нет свободного места. Удалите записи." << endl;
}
void PRegistration::delCard()
{
    cout << endl;
    int id;
    cout << "Введите номер карточки: ";
    cin >> id;
    if (id < 0 || id > 99)
    {
        cout << "Номер неверен." << endl;
        return;
    }
    cards[id].set_duration(0);
    cards[id].set_disease(Disease());
    cards[id].set_hardness("");
    cards[id].set_patient(Patient());
    cards[id].set_clinic(Clinic());
    cards[id].set_place(0);
    cards[id].set_department(Department());
    cout << "Запись с номером " << id << " удалена." << endl;
}
void PRegistration::showCards()
{
    bool flag = false;
    for (int i = 0; i < _rows; i++) {
        if (cards[i].get_hardness() != "")
        {
            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" << "ID: " << i << " | Длительность лечения: " << cards[i].get_duration() << " | Диагноз: " << cards[i].get_disease().get_title() << " | Пациент: " << cards[i].get_patient().get_lname() + " " + cards[i].get_patient().get_name() + " " + cards[i].get_patient().get_pat() << " | Тяжесть заболевания: " << cards[i].get_hardness() << " | Клиника: " << cards[i].get_clinic().get_title() << " | Место: " << cards[i].get_place() << " | Отделение: " << cards[i].get_department().get_title() << " |" << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" << endl;
            flag = true;
        }
    }
    if (!flag) cout << "Записи отсутствуют." << endl;
}

void PRegistration::searchDepartment()
{
    string dep;
    cout << endl;
    cout << "Введите название подразделения или его часть: ";
    cin >> dep;
    for (int i = 0; i < _rows; i++)
    {
        if (cards[i].get_department().get_title().find(dep) != string::npos)
        {
            cout << "---------------------------------------------\n" << "ФИО: " << cards[i].get_patient().get_lname() + " " + cards[i].get_patient().get_name() + " " + cards[i].get_patient().get_pat() << " | Телефон: " << cards[i].get_patient().get_phone() << " |" << "\n---------------------------------------------\n" << endl;
        }
    }
}
void PRegistration::searchDisease()
{
    string des;
    cout << endl;
    cout << "Введите название диагноза или его часть: ";
    cin >> des;
    for (int i = 0; i < _rows; i++)
    {
        if (cards[i].get_disease().get_title().find(des) != string::npos)
        {
            cout << "---------------------------------------------\n" << "ФИО: " << cards[i].get_patient().get_lname() + " " + cards[i].get_patient().get_name() + " " + cards[i].get_patient().get_pat() << " | Телефон: " << cards[i].get_patient().get_phone() << " |" << "\n---------------------------------------------\n" << endl;
        }
    }
}
void PRegistration::searchHardness()
{
    string hard;
    cout << endl;
    cout << "Введите тяжесть заболевания или часть его названия: ";
    cin >> hard;
    for (int i = 0; i < _rows; i++)
    {
        if (cards[i].get_hardness().find(hard) != string::npos)
        {
            cout << "---------------------------------------------\n" << "ФИО: " << cards[i].get_patient().get_lname() + " " + cards[i].get_patient().get_name() + " " + cards[i].get_patient().get_pat() << " | Телефон: " << cards[i].get_patient().get_phone() << " |" << "\n---------------------------------------------\n" << endl;
        }
    }
}
void PRegistration::searchPlacesAmount()
{
    int min, max;
    cout << endl;
    cout << "Введите минимальное количество койко-мест: ";
    cin >> min;
    cout << endl << "Введите максимальное количество койко-мест: ";
    cin >> max;
    for (int i = 0; i < _rows; i++)
    {
        if ((clinics[i].get_places() >= min) & (clinics[i].get_places() <= max))
        {
            cout << "---------------------------------------------\n" << " Название: " << clinics[i].get_title() << " | Количество мест: " << clinics[i].get_places() << " |" << "\n---------------------------------------------\n" << endl;
        }
    }
}
void PRegistration::searchDiseasesAmount()
{
    int _diseases[_size];
    for (int i = 0; i < _size; i++)
    {
        _diseases[i] = 0;
    }
    for (int j = 0; j < _size; j++)
    {
        for (int i = 0; i < _rows; i++)
        {
            if (cards[i].get_patient().get_lname().find(patients[j].get_lname()) != string::npos)
            {
                _diseases[j]++;
            }
        }
    }
    int min, max;
    cout << endl;
    cout << "Введите минимальное количество болезней: ";
    cin >> min;
    cout << endl << "Введите максимальное количество болезней: ";
    cin >> max;
    for (int j = 0; j < _size; j++)
    {
        if ((_diseases[j] >= min) & (_diseases[j] <= max))
        {
            cout << "---------------------------------------------\n" << " Пациент: " << patients[j].get_lname() + " " + patients[j].get_name() + " " + patients[j].get_pat() << " | Количество болезней: " << _diseases[j] << " |" << "\n---------------------------------------------\n" << endl;
        }
    }
}
void PRegistration::searchDuration()
{
    int min, max;
    cout << endl;
    cout << "Введите минимальную длительность лечения: ";
    cin >> min;
    cout << endl << "Введите максимальную длительность лечения: ";
    cin >> max;
    for (int i = 0; i < _rows; i++)
    {
        if ((cards[i].get_duration() >= min) & (cards[i].get_duration() <= max))
        {
            cout << "-------------------------------------------------------------------------------\n" << "ФИО: " << cards[i].get_patient().get_lname() + " " + cards[i].get_patient().get_name() + " " + cards[i].get_patient().get_pat() << " | Телефон: " << cards[i].get_patient().get_phone() << " | Длительность лечения: " << cards[i].get_duration() << " | Диагноз: " << cards[i].get_disease().get_title() << " |" << "\n-------------------------------------------------------------------------------\n" << endl;
        }
    }
}
void PRegistration::searchDistrict()
{
    string dist;
    cout << endl;
    cout << "Введите название района или его часть: ";
    cin >> dist;
    for (int i = 0; i < _rows; i++)
    {
        if (cards[i].get_clinic().get_district().get_title().find(dist) != string::npos)
        {
            cout << "-------------------------------------------------------------------------------\n" << "ФИО: " << cards[i].get_patient().get_lname() + " " + cards[i].get_patient().get_name() + " " + cards[i].get_patient().get_pat() << " | Телефон: " << cards[i].get_patient().get_phone() << " | Больница: " << cards[i].get_clinic().get_title() << " | Диагноз: " << cards[i].get_disease().get_title() << " | Период болезни: " << cards[i].get_duration() << " |" << "\n-------------------------------------------------------------------------------\n" << endl;
        }
    }
}

void PRegistration::searchCategory()
{
    string dis;
    cout << endl;
    cout << "Введите название категории диагноза или его часть: ";
    cin >> dis;
    for (int i = 0; i < _rows; i++)
    {
        if (cards[i].get_disease().get_category().get_title().find(dis) != string::npos)
        {
            cout << "-------------------------------------------------------------------------------\n" << "ФИО: " << cards[i].get_patient().get_lname() + " " + cards[i].get_patient().get_name() + " " + cards[i].get_patient().get_pat() << " | Телефон: " << cards[i].get_patient().get_phone() << " | Больница: " << cards[i].get_clinic().get_title() << " | Диагноз: " << cards[i].get_disease().get_title() << " | Период болезни: " << cards[i].get_duration() << " |" << "\n-------------------------------------------------------------------------------\n" << endl;
        }
    }
} 

