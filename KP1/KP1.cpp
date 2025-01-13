#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <vector>

const int GRADES_ARRAY_SIZE = 5;
const char* PATH = "students.txt";
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

struct student {
    string fullname;
    string group;
    int grades[GRADES_ARRAY_SIZE];
};



string serializeStudentToString(student* s) {
    string result = s->fullname + ";" + s->group + ";";
    for (int i = 0; i < GRADES_ARRAY_SIZE; i++) {
        result += to_string(s->grades[i]);
        if (i != GRADES_ARRAY_SIZE - 1) {
            result += ",";
        }
    }
    return result;
}

student deserializeStudentFromString(string serialized) {
    vector<string> parts = split(serialized, ";");
    student s;
    s.fullname = parts[0];
    s.group = parts[1];
    vector<string> grades = split(parts[2], ",");
    for (int i = 0; i < GRADES_ARRAY_SIZE; i++) {
        s.grades[i] = stoi(grades[i]);
    }
    return s;
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

void saveStudentsInFile(vector<student> students) {
    ofstream out;
    out.open(PATH);

    if (out.is_open())
    {
        for (int i = 0; i < students.size(); i++) {
            out << serializeStudentToString(&students[i]);
            if (i != students.size() - 1) {
                out << endl;
            }
        }
    }
    out.close();
}

vector<student> loadStudentsFromFile() {
    vector<student> students;
    string line, sss;
    ifstream in(PATH);

    if (in.is_open())
    {
        int i = 0;
        while (getline(in, line))
        {

            students.push_back(deserializeStudentFromString(line));
            i++;
        }
    }
    in.close();
    return students;
}

void printStudentInfo(student* s) {
    cout << serializeStudentToString(s) << endl;
}

void printStudentsList(vector<student>* students) {
    for (int i = 0; i < students->size(); i++) {
        
        printStudentInfo(&students->at(i));
    }
}

int getIndexByStudentName(string fullname, vector<student>* students) {
    for (int i = 0; i < students->size(); i++) {
        if (students->at(i).fullname == fullname) {
            return i;
        }
    }
    return -1;
}

void delIndexByStudentName(string fullname, vector<student>* students) {
    for (int i = 0; i < students->size(); i++) {
        if (students->at(i).fullname == fullname) {
            students->erase(students->begin() + getIndexByStudentName(fullname, students));
        }
    }
}

void editStudentMenu(vector<student>* students) {
    string firstname, secondname, fullname, first, second, f, st;
    cout << "Введите фамилию студента:" << endl;
    cin >> firstname;
    cout << "Введите инициалы студента:" << endl;
    cin >> secondname;
    fullname = firstname + " " + secondname;
    for (int i = 0; i < fullname.length(); i++) {
        if ((fullname[i] >= '0') && (fullname[i] <= '9')) {
            cout << "Цифрам тут не место!" << endl;
            cout << "Введите ещё раз фамилию и инициалы" << endl;
            cout << "Введите фамилию студента:" << endl;
            cin >> firstname;
            cout << "Введите инициалы студента:" << endl;
            cin >> secondname;
            fullname = firstname + " " + secondname;
        }
    }
    if (getIndexByStudentName(fullname, students) != -1) {
        student* s = &students->at(getIndexByStudentName(fullname, students));
        cout << "Введите НОВУЮ фамилию студента:" << endl;
        cin >> first;
        cout << "Введите НОВЫЕ инициалы студента:" << endl;
        cin >> second;
        f = first + " " + second;
        s->fullname = f;
        for (int i = 0; i < f.length(); i++) {
            if ((f[i] >= '0') && (f[i] <= '9')) {
                cout << "Цифрам тут не место!" << endl;
                cout << "Введите ещё раз фамилию и инициалы" << endl;
                cout << "Введите фамилию студента:" << endl;
                cin >> first;
                cout << "Введите инициалы студента:" << endl;
                cin >> second;
                f = first + " " + second;
            }
        }
        if (getIndexByStudentName(s->fullname, students) == -1) {
            cout << "Введите НОВЫЙ номер группы:" << endl;
            cin >> s->group;
            for (int i = 0; i < GRADES_ARRAY_SIZE; i++) {
                cout << "Введите НОВУЮ оценку [" << i << "]:" << endl;
                cin >> s->grades[i];
                while ((s->grades[i] < 2) || (s->grades[i]) > 5) {
                    cout << "Оценка не может быть такой!" << endl;
                    cout << "Введите оценку от 2 до 5." << endl;
                    cin >> s->grades[i];
                }
            }
        }
        else {
            int flag = 0;
            while (flag == 0) {
                cout << "Такое ФИО уже есть" << endl;
                cout << "Введите новое ФИО" << endl;
                cout << "Введите НОВУЮ фамилию студента:" << endl;
                cin >> first;
                cout << "Введите НОВЫЕ инициалы студента:" << endl;
                cin >> second;
                f = first + " " + second;
                s->fullname = f;
                for (int i = 0; i < f.length(); i++) {
                    if ((f[i] >= '0') && (f[i] <= '9')) {
                        cout << "Цифрам тут не место!" << endl;
                        cout << "Введите ещё раз фамилию и инициалы" << endl;
                        cout << "Введите фамилию студента:" << endl;
                        cin >> first;
                        cout << "Введите инициалы студента:" << endl;
                        cin >> second;
                        f = first + " " + second;
                    }
                }
                if (getIndexByStudentName(s->fullname, students) == -1) {
                    
                }
                else {
                    flag = 1;
                }
            }
        }
        cout << "Информация обновлена" << endl;
    }
    else {
        cout << "Студент не найден" << endl;
    }
    if (getIndexByStudentName(fullname, students) == -1) {}
    else {
        cout << "Такой студент уже есть" << endl;
    }
}

void addStudentMenu(vector<student>* students) {
    student s, k;
    cout << "Введите фамилию студента:" << endl;
    cin >> s.fullname;
    cout << "Введите инициалы студента:" << endl;
    cin >> k.fullname;
    s.fullname = s.fullname + " " + k.fullname;
    for (int i = 0; i < s.fullname.length(); i++) {
        if ((s.fullname[i] >= '0') && (s.fullname[i] <= '9')) {
            cout << "Цифрам тут не место!" << endl;
            cout << "Введите ещё раз фамилию и инициалы" << endl;
            cout << "Введите фамилию студента:" << endl;
            cin >> s.fullname;
            cout << "Введите инициалы студента:" << endl;
            cin >> k.fullname;
            s.fullname = s.fullname + " " + k.fullname;
        }
    }
    if (getIndexByStudentName(s.fullname, students) == -1) {
        cout << "Введите номер группы:" << endl;
        cin >> s.group;
        for (int i = 0; i < GRADES_ARRAY_SIZE; i++) {
            cout << "Введите оценку [" << i << "]:" << endl;
            cin >> s.grades[i];
            while ((s.grades[i] < 2) || (s.grades[i]) > 5) {
                cout << "Оценка не может быть такой!" << endl;
                cout << "Введите оценку от 2 до 5." << endl;
                cin >> s.grades[i];
            }
        }
        students->push_back(s);
        cout << "Студент добавлен" << endl;
    }
    else {
        cout << "Такой студент уже есть в базе" << endl;
    }
}

void deleteStudentMenu(vector<student>* students) {
    string firstname, secondname, fullname;
    cout << "Введите фамилию студента:" << endl;
    cin >> firstname;
    cout << "Введите инициалы студента:" << endl;
    cin >> secondname;
    fullname = firstname + " " + secondname;
    if (getIndexByStudentName(fullname, students) != -1) {
        students->erase(students->begin() + getIndexByStudentName(fullname, students));
        cout << "Студент удален" << endl;
    }
    else {
        cout << "Студент не найден" << endl;
    }
}

void help() {
    cout << "1. Добавить новую запись" << endl
        << "2. Редактировать запись" << endl
        << "3. Удалить запись" << endl
        << "4. Поиск студентов имеющих оценки 4 и 5" << endl
        << "5. Распечатать все записи" << endl
        << "6. Загрузить из файла" << endl
        << "7. Сохранить в файл" << endl
        << "0. Выход" << endl;
}

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(0, "Rus");

    vector<student> students = loadStudentsFromFile();
    string sss, fff;
    string* a = new string[students.size()];
    string* b = new string[students.size()];
    fff = "";
    for (int i = 0; i < students.size(); i++) {
        sss = serializeStudentToString(&students[i]);
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

    for (int i = 0; i < students.size(); i++) {
        for (int j = i + 1; j < students.size(); j++) {
            if (a[i] == a[j]) {
                b[i] = a[i];
                //cout << "Совпадение ФИО в файле!" << endl;
                delIndexByStudentName(b[i], &students);
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
            cout << "Ошибка ввода, выберите действие: "; 
            cin >> n;
        }
        switch (n) {
        case 1: {
            addStudentMenu(&students);
            break;
        }
        case 2: {
            editStudentMenu(&students);
            break;
        }
        case 3: {
            deleteStudentMenu(&students);
            break;
        }
        case 4: {
            cout << "Следующие студенты имеют оценки 4 и 5:" << endl;
            for (int i = 0; i < students.size(); i++) {
                bool flag1 = false;
                bool flag2 = false;
                for (int j = 0; j < GRADES_ARRAY_SIZE; j++) {
                    if (students[i].grades[j] == 4) {
                        flag1 = true;
                    }
                    else if (students[i].grades[j] == 5) {
                        flag2 = true;
                    }
                }
                if (flag1 && flag2) {
                    printStudentInfo(&students[i]);
                }
            }
            break;
        }
        case 5: {
            printStudentsList(&students);
            break;
        }
        case 6: {
            students = loadStudentsFromFile();
            break;
        }
        case 7: {
            saveStudentsInFile(students);
            break;
        }
        case 0: {
            return 0;
        }
        }
    }
}