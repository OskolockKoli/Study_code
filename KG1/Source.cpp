#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <vector>
const int BIRTH_DATE_ARRAY_SIZE = 3;
const char* PATH = "notes.txt";
using namespace std;

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

struct note {
    string fullname;
    string phone;
    int birthDate[BIRTH_DATE_ARRAY_SIZE];
};

string serializeNoteToString(note* n) {
    string result = n->fullname + ";" + n->phone + ";";
    for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) {
        result += to_string(n->birthDate[i]);
        if (i != BIRTH_DATE_ARRAY_SIZE - 1) {
            result += "-";
        }
    }
    return result;
}

note deserializeNoteFromString(string serialized) {
    vector<string> parts = split(serialized, ";");
    note n;
    n.fullname = parts[0];
    n.phone = parts[1];
    vector<string> birthDate = split(parts[2], ".");
    for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) {
        n.birthDate[i] = stoi(birthDate[i]);
    }
    return n;
}

int getFileLinesCount() {
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

void saveNotesInFile(vector<note> notes) {
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

vector<note> loadNotesFromFile() {
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

void printNoteInfo(note* n) {
    cout << serializeNoteToString(n) << endl;
}

void printNotesList(vector<note>* notes) {
    for (int i = 0; i < notes->size(); i++) {
        printNoteInfo(&notes->at(i));
    }
}

int getIndexByFullName(string fullname, vector<note>* notes) {
    for (int i = 0; i < notes->size(); i++) {
        if (notes->at(i).fullname == fullname) {
            return i;
        }
    }
    return -1;
}

void editNoteMenu(vector<note>* notes) {
    string fullname;
    cout << "Введите фамилию и имя контакта:" << endl;
    cin >> fullname;
    if (getIndexByFullName(fullname, notes) != -1) {
        note* n = &notes->at(getIndexByFullName(fullname, notes));
        cout << "Введите НОВУЮ фамилию и имя:" << endl;
        cin >> n->fullname;
        cout << "Введите НОВЫЙ номер телефона:" << endl;
        cin >> n->phone;
        for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) {
            cout << "Дата рождения [" << i << "]:" << endl;
            cin >> n->birthDate[i];
        }
        cout << "Информация обновлена" << endl;
    }
    else {
        cout << "Контакт не найден" << endl;
    }
}

void addNoteMenu(vector<note>* notes) {
    note n;
    cout << "Введите фамилию и имя контакта:" << endl;
    cin >> n.fullname;
    if (getIndexByFullName(n.fullname, notes) == -1) {
        cout << "Введите номер телефона:" << endl;
        cin >> n.phone;
        string a = "89999999999";
        string b = "89000000000";
        if ((n.phone > a) || (n.phone < b)) {
            cout << "Номер набран неккоректно" << endl;
            cout << "Введите номер в формате 89xxxxxxxxx" << endl;
            cin >> n.phone;
        }
        for (int i = 0; i < BIRTH_DATE_ARRAY_SIZE; i++) {
            cout << "Дата рождения [" << i << "]:" << endl;
            cin >> n.birthDate[i];
            if (i == 0) {
                if ((n.birthDate[i] < 0) || (n.birthDate[i] > 31)) {
                    cout << "День набран неккоректно" << endl;
                    cout << "Введите день нормально" << endl;
                    cin >> n.birthDate[i];
                }
            }
            if (i == 1) {
                if ((n.birthDate[i] < 0) || (n.birthDate[i] > 12)) {
                    cout << "Месяц набран неккоректно" << endl;
                    cout << "Введите месяц нормально" << endl;
                    cin >> n.birthDate[i];
                }
            }
            if (i == 2) {
                if ((n.birthDate[i] < 0) || (n.birthDate[i] > 2022)) {
                    cout << "Год набран неккоректно" << endl;
                    cout << "Введите год нормально" << endl;
                    cin >> n.birthDate[i];
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

void deleteNoteMenu(vector<note>* notes) {
    string fullname;
    cout << "Введите фамилию и имя контакта:" << endl;
    cin >> fullname;
    if (getIndexByFullName(fullname, notes) != -1) {
        notes->erase(notes->begin() + getIndexByFullName(fullname, notes));
        cout << "Конакт удален" << endl;
    }
    else {
        cout << "Конакт не найден" << endl;
    }
}

void help() {
    cout << "1. Добавить новую запись" << endl
        << "2. Редактировать запись" << endl
        << "3. Удалить запись" << endl
        << "4. Поиск контактов по месяцу рождения" << endl
        << "5. Распечатать все записи" << endl
        << "6. Загрузить из файла" << endl
        << "7. Сохранить в файл" << endl
        << "0. Выход" << endl;
}

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<note> notes = loadNotesFromFile();

    int n = -1;
    while (n != 0) {
        help();
        cin >> n;
        while (cin.fail() || (n < 0) || (n > 8)) {
            cin.clear();
            cin.sync();
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
            break;
        }
        case 6: {
            notes = loadNotesFromFile();
            break;
        }
        case 7: {
            saveNotesInFile(notes);
            break;
        }
        case 0: {
            return 0;
        }
        }
    }
}

