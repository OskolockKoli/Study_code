#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <ctime>
#include <regex>

using namespace std;

const int c = 1, N = 2000;
const int key_lenght = 6;

struct Elem {
    string key;
    bool deleted = false;
};


class Table {
    Elem dict[N];
    bool is_key(string key) {
        static const regex r(R"(^[0-9][0-9][A-Z][A-Z][0-9][0-9]$)");
        return regex_match(key.data(), r);
    }
    int hash(string key) {
        return (char(key[0]) + char(key[1]) + char(key[2]) + char(key[3]) + char(key[4]) + char(key[5])) % 2000;
    }
    int ahash(string key) {
        return pow(int(key[0]), 2) + pow(int(key[1]), 2) + pow(int(key[2]), 2) + pow(int(key[3]), 2) + pow(int(key[4]), 2) + pow(int(key[5]), 2);
    }

public:
    void add(string key) {
        if (!is_key(key)) {
            cout << "Ошибка ";
            return;
        }
        int id;
        for (int i = 0;; i++) {
            id = hash(key) + c * i;
            if (id >= N) {
                return;
            }
            if (dict[id].key.empty()) {
                dict[id].key = key;
                return;
            }
        }
    }

    int find(string key) {
        if (!is_key(key)) {
            cout << "\nError!\n";
            return -1;
        }
        int id;
        for (int i = 0;; i++) {
            id = hash(key) + c * i;
            if (id >= N || (!dict[id].deleted && dict[id].key.empty())) {
                return -1;
            }
            if (dict[id].key == key) {
                return id;
            }
        }
    }

    int afind(string key) {
        int id = ahash(key);
        return id;
    }

    string find(int index) {
        if (index >= N) {
            cout << "Error!";
            return "";
        }
        if (dict[index].key.empty())
            return "";

        return dict[index].key;
    }

    void show() {
        for (int i = 0; i < N; i++)
            if (!dict[i].key.empty())
                cout << i << " " << dict[i].key << " ";
        cout << endl;
    }

    void del(string key) {
        if (!is_key(key)) {
            cout << "\nError!\n";
            return;
        }
        int id = find(key);
        if (id != -1) {
            dict[id].deleted = true;
            dict[id].key = "";
        }
    }
};

void fill_table(Table& table) {
    string key = "123456";
    for (int i = 0; i < N * 2; i++) {
        for (int j = 0; j < key_lenght; j++) {
            if (j == 2 || j == 3)
                key[j] = 'A' + rand() % ('Z' - 'A');
            else
                key[j] = '0' + rand() % ('9' - '0');
        }
        table.add(key);
    }
}

void w_file(Table table) {
    fstream file("smth.txt", ios_base::out);
    int i, temp, j, flag;
    j = 0;
    flag = 1;
    int* arr = new int[N];
    int* brr = new int[N];
    for (i = 0; i < N; i++) {
        arr[i] = 0;
        brr[i] = 0;
    }
    if (!file.is_open()) {
        cout << "Error!\n";
        return;
    }
    for (i = 0; i < N; i++) {
        if (!table.find(i).empty()) {
            temp = table.afind(table.find(i));
            j = 0;
            while (arr[j] != 0) {
                if (temp == arr[j]) {
                brr[j]++;
                flag = 0;
                }
                j++;
            }
            if (flag == 1) {
                arr[j] = temp;
                brr[j]++;
            }
            flag = 1;
        }
    }
    for (i = 0; i < N; i++) {
        file << i << "\t" << brr[i] << '\n';
    }
    file.close();
}

string input_str() {
    cout << "Введите название строки: ";
    string value;
    cin >> value;
    return value;
}

int input_int() {
    int value;
    cin >> value;
    return value;
}

int main()
{
    setlocale(0, "Rus");
    srand(time(NULL));
    int c = 9;
    Table table;
    while (c != 0) {
        cout << endl;
        cout << "1, если нужно заполнить таблицу.\n";
        cout << "2, если нужно вывести таблицу.\n";
        cout << "3, если нужно добавить элемент.\n";
        cout << "4, если нужно удалить элемент по ключу.\n";
        cout << "5, если нужно найти элемент по ключу.\n";
        cout << "6, если нужно перенести таблицу в файл.\n";
        cout << "0, если ничего больше не нужно.\n";
        cout << endl;
        c = input_int();
        if ((c != 1) && (c != 2) && (c != 3) && (c != 4) && (c != 5) && (c != 6) && (c != 0)) {
            cout << "Error!" << endl;
        }
        if (c == 1) {
            fill_table(table);
        }
        if (c == 2) {
            table.show();
        }
        if (c == 3) {
            string key;
            key = input_str();
            table.add(key);
        }
        if (c == 4) {
            string key;
            key = input_str();
            table.del(key);
        }
        if (c == 5) {
            string key;
            key = input_str();
            cout << table.find(key);
        }
        if (c == 6) {
            w_file(table);
        }
    }
    cout << "Thanks!" << endl;
    return 0;
}