#include <iostream> 
#include <string>
#include <fstream>
#include <windows.h>
#include <vector> 
#include <typeinfo>

const int BIRTH_DATE_ARRAY_SIZE = 3;
const char* PATH = "notes.txt"; //адрес файла
using namespace std;

vector<string> split(string s, string delimiter) { //функция разделяет строку на отдельные элементы данных
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start)); //получаем по элементу, начиная с первого 
    return res; //возвращаем по элементу, начиная с первого
}

struct note { //структура данных
    string fullname;
    string phone;
    int birthDate[BIRTH_DATE_ARRAY_SIZE];
};

string serializeNoteToString(note* n) { //набор данных превращаем в строку
    string result = n->fullname + ";" + n->phone + ";";
    for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) {
        result += to_string(n->birthDate[i]);
        if (i != BIRTH_DATE_ARRAY_SIZE - 1) {
            result += ".";
        }
    }
    return result;
}

note deserializeNoteFromString(string serialized) {  //строку с данными превращаем в набор данных
    vector<string> parts = split(serialized, ";");
    note n;
    n.fullname = parts[0];

    n.phone = parts[1];

    vector<string> birthDate = split(parts[2], ".");
    for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) {
        try {
            n.birthDate[i] = stoi(birthDate[i]);
        }
        catch (...)
        {
            n.birthDate[i] = -1;
            cout << "Error in file!" << endl;
        }
        if (typeid(stoi(birthDate[i])) != typeid(int)) {
            throw;
        }
        //n.birthDate[i] = stoi(birthDate[i]);
    }
    return n;
}

int getFileLinesCount() { //количество человек, которые мы записали в файл
    int count = 0;
    string line;
    ifstream in(PATH);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            count++;
        }
    }
    in.close();
    return count;
}

void saveNotesInFile(vector<note> notes) { //сохраняем данные в файл в виде строки построчно
    ofstream out;
    out.open(PATH);

    if (out.is_open())
    {
        for (int i = 0; i < notes.size(); i++) {
            out << serializeNoteToString(&notes[i]);
            if (i != notes.size() - 1) {
                out << endl;
            }
        }
    }
    out.close();
}

vector<note> loadNotesFromFile() { //выгружаем из файла информацию в виде данных
    vector<note> notes;
    string line;
    ifstream in(PATH);

    if (in.is_open())
    {
        int i = 0;
        while (getline(in, line))
        {
            notes.push_back(deserializeNoteFromString(line));
            i++;
        }
    }
    in.close();
    return notes;
}

void printNoteInfo(note* n) { //выводим данные одного человека
    cout << serializeNoteToString(n) << endl;
}

void printNotesList(vector<note>* notes) { //выводим все данные
    for (int i = 0; i < notes->size(); i++) {
        printNoteInfo(&notes->at(i));
    }
}

int getIndexByFullName(string fullname, vector<note>* notes) { //определяем какой человек в списке по фио
    for (int i = 0; i < notes->size(); i++) {
        if (notes->at(i).fullname == fullname) {
            return i;
        }
    }
    return -1;
}

void editNoteMenu(vector<note>* notes) { //редактируем данные о человеке с проверками
    string firstname, secondname, fullname, first, second, f;
    cout << "Введите фамилию контакта:" << endl;
    cin >> firstname;
    cout << "Введите имя контакта:" << endl;
    cin >> secondname;
    fullname = firstname + " " + secondname;
    for (int i = 0; i < fullname.length(); i++) {
        if ((fullname[i] >= '0') && (fullname[i] <= '9')) { //проверка на отсутствие цифр в фио
            cout << "Цифрам тут не место!" << endl;
            cout << "Введите ещё раз фамилию и инициалы" << endl;
            cout << "Введите фамилию студента:" << endl;
            cin >> fullname;
            cout << "Введите инициалы студента:" << endl;
            cin >> fullname;
            fullname = fullname + " " + fullname;
        }
    }
    if (getIndexByFullName(fullname, notes) != -1) { //редактируем фио с проверкой
        note* n = &notes->at(getIndexByFullName(fullname, notes));
        cout << "Введите НОВУЮ фамилию:" << endl;
        cin >> first;
        cout << "Введите НОВЫЕ инициалы:" << endl;
        cin >> second;
        f = first + " " + second;
        n->fullname = f;
        for (int i = 0; i < n->fullname.length(); i++) {
            if ((n->fullname[i] >= '0') && (n->fullname[i] <= '9')) {
                cout << "Цифрам тут не место!" << endl;
                cout << "Введите ещё раз фамилию и инициалы" << endl;
                cout << "Введите фамилию студента:" << endl;
                cin >> n->fullname;
                cout << "Введите инициалы студента:" << endl;
                cin >> n->fullname;
                n->fullname = n->fullname + " " + n->fullname;
            }
        }
        if (getIndexByFullName(fullname, notes) != -1) {
            cout << "Введите НОВЫЙ номер телефона:" << endl;
            cin >> n->phone;
            for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) {
                cout << "Дата рождения [" << i << "]:" << endl;
                cin >> n->birthDate[i];
                if (i == 0) {
                    while ((n->birthDate[i] < 1950) || (n->birthDate[i] > 2022)) {
                        cout << "Год набран неккоректно" << endl;
                        cout << "Введите год нормально" << endl;
                        cin >> n->birthDate[i];
                    }
                }
                if (i == 1) {
                    while ((n->birthDate[i] < 1) || (n->birthDate[i] > 12)) {
                        cout << "Месяц набран неккоректно" << endl;
                        cout << "Введите месяц нормально" << endl;
                        cin >> n->birthDate[i];
                    }
                }
                if (i == 2) {
                    if (n->birthDate[i - 1] % 2 == 0) {
                        while ((n->birthDate[i] < 0) || (n->birthDate[i] > 30)) {
                            cout << "День набран неккоректно" << endl;
                            cout << "Введите день нормально" << endl;
                            cin >> n->birthDate[i];
                        }
                    }
                    if (n->birthDate[i - 1] % 2 == 1) {
                        while ((n->birthDate[i] < 0) || (n->birthDate[i] > 31)) {
                            cout << "День набран неккоректно" << endl;
                            cout << "Введите день нормально" << endl;
                            cin >> n->birthDate[i];
                        }
                    }
                    if (n->birthDate[i - 1] == 2) {
                        while ((n->birthDate[i] < 0) || (n->birthDate[i] > 28)) {
                            cout << "День набран неккоректно" << endl;
                            cout << "Введите день нормально" << endl;
                            cin >> n->birthDate[i];
                        }
                    }
                }
            }
            cout << "Информация обновлена" << endl;
        }
        else {
            cout << "Такой контакт уже есть в базе" << endl;
        }

    }
    else {
        cout << "Контакт не найден" << endl;
    }
}

void addNoteMenu(vector<note>* notes) { //новый контакт
    note n, k;
    cout << "Введите фамилию контакта:" << endl;
    cin >> n.fullname;
    cout << "Введите инициалы контакта:" << endl;
    cin >> k.fullname;
    n.fullname = n.fullname + " " + k.fullname;
    for (int i = 0; i < n.fullname.length(); i++) {
        if ((n.fullname[i] >= '0') && (n.fullname[i] <= '9')) { //проверка на отсутствие цифр в фио
            cout << "Цифрам тут не место!" << endl;
            cout << "Введите ещё раз фамилию и инициалы" << endl;
            cout << "Введите фамилию студента:" << endl;
            cin >> n.fullname;
            cout << "Введите инициалы студента:" << endl;
            cin >> n.fullname;
            n.fullname = n.fullname + " " + k.fullname;
        }
    }
    if (getIndexByFullName(n.fullname, notes) == -1) { //проверка правильности набора номера телефона
        cout << "Введите номер телефона:" << endl;
        cin >> n.phone;
        string a = "89999999999";
        string b = "89000000000";
        if ((n.phone > a) || (n.phone < b)) {
            cout << "Номер набран неккоректно" << endl;
            cout << "Введите номер в формате 89xxxxxxxxx" << endl;
            cin >> n.phone;
        }
        for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) { //проверка правильности набора даты рождения
            cout << "Дата рождения(год, месяц, день) [" << i << "]:" << endl;
            cin >> n.birthDate[i];
            if (i == 0) {
                while ((n.birthDate[i] < 1950) || (n.birthDate[i] > 2022)) {
                    cout << "Год набран неккоректно" << endl;
                    cout << "Введите год нормально" << endl;
                    cin >> n.birthDate[i];
                }
            }
            if (i == 1) {
                while ((n.birthDate[i] < 1) || (n.birthDate[i] > 12)) {
                    cout << "Месяц набран неккоректно" << endl;
                    cout << "Введите месяц нормально" << endl;
                    cin >> n.birthDate[i];
                }
            }
            if (i == 2) {
                if (n.birthDate[i - 1] % 2 == 0) {
                    while ((n.birthDate[i] < 0) || (n.birthDate[i] > 30)) {
                        cout << "День набран неккоректно" << endl;
                        cout << "Введите день нормально" << endl;
                        cin >> n.birthDate[i];
                    }
                }
                if (n.birthDate[i - 1] % 2 == 1) {
                    while ((n.birthDate[i] < 0) || (n.birthDate[i] > 31)) {
                        cout << "День набран неккоректно" << endl;
                        cout << "Введите день нормально" << endl;
                        cin >> n.birthDate[i];
                    }
                }
                if (n.birthDate[i - 1] == 2) {
                    while ((n.birthDate[i] < 0) || (n.birthDate[i] > 28)) {
                        cout << "День набран неккоректно" << endl;
                        cout << "Введите день нормально" << endl;
                        cin >> n.birthDate[i];
                    }
                }
            }
        }
        notes->push_back(n);
        cout << "Контакт добавлен" << endl;
    }
    else {
        cout << "Такой контакт уже есть в базе" << endl;
    }
}

void deleteNoteMenu(vector<note>* notes) { //удаление по фио от пользователя с проверкой
    string firstname, secondname, fullname;
    cout << "Введите фамилию студента:" << endl;
    cin >> firstname;
    cout << "Введите инициалы студента:" << endl;
    cin >> secondname;
    fullname = firstname + " " + secondname;
    for (int i = 0; i < fullname.length(); i++) {
        if ((fullname[i] >= '0') && (fullname[i] <= '9')) { //проверка на отсутствие цифр в фио
            cout << "Цифрам тут не место!" << endl;
            cout << "Введите ещё раз фамилию и инициалы" << endl;
            cout << "Введите фамилию студента:" << endl;
            cin >> fullname;
            cout << "Введите инициалы студента:" << endl;
            cin >> fullname;
            fullname = fullname + " " + fullname;
        }
    }
    if (getIndexByFullName(fullname, notes) != -1) {
        notes->erase(notes->begin() + getIndexByFullName(fullname, notes));
        cout << "Конакт удален" << endl;
    }
    else {
        cout << "Конакт не найден" << endl;
    }
}

void help() { //меню
    cout << "1. Добавить новую запись" << endl
        << "2. Редактировать запись" << endl
        << "3. Удалить запись" << endl
        << "4. Поиск контактов по месяцу рождения" << endl
        << "5. Распечатать все записи" << endl
        << "6. Загрузить из файла" << endl
        << "7. Сохранить в файл" << endl
        << "0. Выход" << endl;
}

void delIndexByFullName(string fullname, vector<note>* notes) { //удаление по фио
    for (int i = 0; i < notes->size(); i++) {
        if (notes->at(i).fullname == fullname) {
            notes->erase(notes->begin() + getIndexByFullName(fullname, notes));
        }
    }
}

int check(vector<note> notes) {
    string s, f;
    int flag = 0;
    int temp1, temp2, i, j;
    for (j = 0; j < notes.size(); j++) {
        s = serializeNoteToString(&notes[j]);
        for (i = 0; i < s.length(); i++) {
            if (s[i] == ';') {
                temp1 = i;
                break;
            }
            if ((int(s[i]) > 47) && (int(s[i]) < 58)) {
                //cout << "Error in file: fullname on " << j + 1 << " line!" << endl << endl;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            for (i = temp1 + 1; i < s.length(); i++) {
                if (s[i] == ';') {
                    temp2 = i;
                    break;
                }
                if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                    //cout << "Error in file: phone number on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    temp2 = i;
                    break;
                }
            }
        }
        if (flag == 0) {
            for (i = temp2 + 1; i < s.length(); i++) {
                if (s[i] == ';') {
                    break;
                }
                if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91)) || (int(s[i]) == 45)) {
                    //cout << "Error in file: phone number on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    break;
                }
            }
        }
        return flag;
        flag = 0;
    }
}

int main() {

    SetConsoleCP(1251); //русский язык
    SetConsoleOutputCP(1251);

    vector<note> notes = loadNotesFromFile(); //в список добавляем всех из файла

    check(notes);
    if (check(notes) == 1) {
        cout << "Error in file!" << endl;
        return 1;
    }

    string sss, fff;
    string* a = new string[notes.size()];
    string* b = new string[notes.size()];
    fff = "";
    for (int i = 0; i < notes.size(); i++) {
        sss = serializeNoteToString(&notes[i]);
        for (int i = 0; i < sss.length(); i++) {
            if (sss[i] == ';') {
                break;
            }
            else {
                fff += sss[i];
            }
        }
        a[i] = fff;
        fff = "";
    }
    for (int i = 0; i < notes.size(); i++) {
        for (int j = i + 1; j < notes.size(); j++) {
            if (a[i] == a[j]) {
                b[i] = a[i];
                //cout << "Совпадение ФИО в файле!" << endl;
                delIndexByFullName(b[i], &notes);
                break;
            }
        }
    }
    int n = -1;
    while (n != 0) {
        help();
        cin >> n;
        while (cin.fail() || cin.get() != '\n') {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail());
            cout << "Ошибка ввода, выберите действие: "; cin >> n;
        }
        switch (n) {
        case 1: {
            addNoteMenu(&notes);
            break;
        }
        case 2: {
            editNoteMenu(&notes);
            break;
        }
        case 3: {
            deleteNoteMenu(&notes);
            break;
        }
        case 4: {
            int month;
            cout << "Введите номер месяца" << endl;
            cin >> month;
            cout << "У следующих контактов, в этот месяц день рождения:" << endl;
            for (int i = 0; i < notes.size(); i++) {
                if (notes[i].birthDate[1] == month) {
                    printNoteInfo(&notes[i]);
                }
            }
            break;
        }
        case 5: {
            printNotesList(&notes);
            cout << "Вывод всех контактов произошёл успешно" << endl;
            break;
        }
        case 6: {
            notes = loadNotesFromFile();
            cout << "Загрузка всех контактов из файла произошла успешно" << endl;
            break;
        }
        case 7: {
            saveNotesInFile(notes);
            cout << "Загрузка всех контактов в файл произошла успешно" << endl;
            break;
        }
        case 0: {
            return 0;
        }
        }
    }
}
