#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>

const char* PATH1 = "clients.txt"; //адрес файла для клиентов
const char* PATH2 = "cars.txt"; //адрес файла для машин
const char* PATH3 = "rent.txt"; //адрес файла для их связи

using namespace std;

//----------------------------------------------------

vector<string> split(string s, string delimiter) { //разбивает строку на части
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

//----------------------------------------------------

struct client {
    string num;
    string fio;
    string pd;
    string adr;
};

string serializeClientToString(client* n) { //набор характеристик превращаем в строку
    string result = n->num + ";" + n->fio + ";" + n->pd + ";" + n->adr;
    return result;
}

client deserializeClientFromString(string serialized) {  //строку превращаем в набор характеристик
    vector<string> parts = split(serialized, ";");
    client n;
    n.num = parts[0];
    n.fio = parts[1];
    n.pd = parts[2];
    n.adr = parts[3];

    return n;
}

void saveClientsInFile(vector<client> clients) { //сохраняем данные в файл
    ofstream out;
    out.open(PATH1);

    if (out.is_open())
    {
        for (int i = 0; i < clients.size(); i++) {
            out << serializeClientToString(&clients[i]);
            if (i != clients.size() - 1) {
                out << endl;
            }
        }
    }
    out.close();
}

vector<client> loadClientsFromFile() { //выгружаем из файла
    vector<client> clients;
    string line;
    ifstream in(PATH1);

    if (in.is_open())
    {
        int i = 0;
        while (getline(in, line))
        {
            clients.push_back(deserializeClientFromString(line));
            i++;
        }
    }
    in.close();
    return clients;
}

int getIndexByNum(string num, vector<client>* clients) { //определяем какой человек в списке по номеру
    int i;
    for (i = 0; i < clients->size(); i++) {
        if (clients->at(i).num == num) {
            return i;
        }
    }
    return -1;
}

void Clientadd(vector<client>* clients) {//добавляем нового клиента
    client n;
    int flag, i, temp;
    string s1, s2, s3, s4, s, sa, sb, sch;
    cout << "Start registering a new client." << endl;
    cout << endl;

    cout << "Please, enter your driver's license number. (NOT 00 AA 000000)" << endl;
    cout << "Please, enter your region code: (input format - NN) ";
    cin >> sa;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sa.length(); i++) {
            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sa.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sa;
        }
    }
    cout << "Please, enter your series: (input format - AA)";
    cin >> sch;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sch.length(); i++) {
            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == sch.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sch;
        }
    }
    cout << "Please, enter your number: (input format - NNNNNN)";
    cin >> sb;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sb.length(); i++) {
            if ((int(sb[i]) > 47) && (int(sb[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sb.length()) && (temp == 6)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sb;
        }
    }
    s1 = sa + " " + sch + " " + sb;
    n.num = s1;
    if (getIndexByNum(n.num, clients) == -1) {

        cout << "Please, enter your fullname: (with one gap)";
        cin >> s2;
        cin >> s;
        s2 = s2 + " " + s;
        n.fio = s2;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < n.fio.length(); i++) {
                if ((int(n.fio[i]) > 47) && (int(n.fio[i]) < 58)) {
                    temp++;
                }
            }
            if (temp > 0) {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> s2;
                cin >> s;
                s2 = s2 + " " + s;
                n.fio = s2;
            }
            else {
                flag = 1;
            }
        }
        cout << "Please, enter your passport details: (with one gap)";
        cin >> s3;
        cin >> s;
        s3 = s3 + " " + s;
        n.pd = s3;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < n.pd.length(); i++) {
                if ((int(n.pd[i]) > 64) && (int(n.pd[i]) < 91) && (int(n.pd[i]) > 96) && (int(n.pd[i]) < 123)) {
                    temp++;
                }
            }
            if (temp > 0) {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> s3;
                cin >> s;
                s3 = s3 + " " + s;
                n.pd = s3;
            }
            else {
                flag = 1;
            }
        }
        cout << "Please, enter your adress. Please, enter your street: ";
        cin >> s4;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < s4.length(); i++) {
                if ((int(s4[i]) > 47) && (int(s4[i]) < 58)) {
                    temp++;
                }
            }
            if (temp > 0) {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> s4;
            }
            else {
                flag = 1;
            }
        }
        cout << "Please, enter your house: ";
        cin >> s;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < s.length(); i++) {
                if ((int(s[i]) > 64) && (int(s[i]) < 91) && (int(s[i]) > 96) && (int(s[i]) < 123)) {
                    temp++;
                }
            }
            if (temp > 0) {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> s;
            }
            else {
                flag = 1;
            }
        }
        s4 = s4 + " " + s;
        n.adr = s4;


        clients->push_back(n);
        cout << endl;
        cout << "Client added successfully." << endl;
        cout << endl;
    }
    else {
        cout << "Same client already is in base!" << endl;
    }
}

void printClientInfo(client* n) { //выводим данные одного человека
    cout << serializeClientToString(n) << endl;
}

void printClientList(vector<client>* clients) { //выводим всех клиентов
    int i;
    for (i = 0; i < clients->size(); i++) {
        printClientInfo(&clients->at(i));
    }
}

void delIndexByNum(string num, vector<client>* clients) { //удаление по фио
    for (int i = 0; i < clients->size(); i++) {
        if (clients->at(i).num == num) {
            clients->erase(clients->begin() + getIndexByNum(num, clients));
        }
    }
}

int Clientcheck(vector<client> clients) {//проверка информации о клиенте
    string s, f;
    int flag = 0;
    int temp1, temp2, temp3, i, j, tempf, temps, tempt;
    int temp = 0;
    for (j = 0; j < clients.size(); j++) {
        s = serializeClientToString(&clients[j]);
        for (i = 0; i < s.length(); i++) {
            if ((s[i] == ' ') && (temp == 0)) {
                tempf = i;
                temp++;
            }
            if ((s[i] == ' ') && (temp == 1)) {
                temps = i;
            }
            if (s[i] == ';') {
                break;
            }
        }
        for (i = 0; i < tempf; i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                flag = 1;
                break;
            }
        }
        for (i = tempf + 1; i < temps; i++) {
            if ((int(s[i]) != 65) && (int(s[i]) != 66)) {
                //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                flag = 1;
                break;
            }
        }
        for (i = temps + 1; i < s.length(); i++) {
            if (s[i] == ';') {
                temp1 = i;
                break;
            }
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
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
                if (((int(s[i]) > 47) && (int(s[i]) < 58))) {
                    //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    temp2 = i;
                    break;
                }
            }
        }
        if (flag == 0) {
            for (i = temp2 + 1; i < s.length(); i++) {
                if (s[i] == ';') {
                    temp3 = i;
                    break;
                }
                if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                    //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    temp3 = i;
                    break;
                }
            }
        }
        if (flag == 0) {
            for (i = temp3 + 1; i < s.length(); i++) {
                if (s[i] == ' ') {
                    tempt = i;
                }
            }
            for (i = temp3 + 1; i < tempt; i++) {
                if (((int(s[i]) > 47) && (int(s[i]) < 58))) {
                    //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    break;
                }
            }
            for (i = tempt + 1; i < s.length(); i++) {
                if (s[i] == ';') {
                    break;
                }
                if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                    //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    break;
                }
            }
        }
        return flag;
        flag = 0;
    }
}

//----------------------------------------------------

struct car {
    string num;
    string br;
    string col;
    int year;
    bool avail;
};

inline const char* const BoolToString(bool b)
{
    return b ? "1" : "0";
}

bool to_bool(string const& s) {
    return s != "0";
}

string serializeCarToString(car* n) { //набор данных превращаем в строку
    string result = n->num + ";" + n->br + ";" + n->col + ";" + to_string(n->year) + ";" + BoolToString(n->avail);
    return result;
}

car deserializeCarFromString(string serialized) {  //строку с данными превращаем в набор данных
    vector<string> parts = split(serialized, ";");
    car n;
    n.num = parts[0];
    n.br = parts[1];
    n.col = parts[2];
    n.year = stoi(parts[3]);
    n.avail = to_bool(parts[4]);

    return n;
}

void saveCarsInFile(vector<car> cars) { //сохраняем данные в файл
    ofstream out;
    out.open(PATH2);

    if (out.is_open())
    {
        for (int i = 0; i < cars.size(); i++) {
            out << serializeCarToString(&cars[i]);
            if (i != cars.size() - 1) {
                out << endl;
            }
        }
    }
    out.close();
}

vector<car> loadCarsFromFile() { //выгружаем информацию из файла
    vector<car> cars;
    string line;
    ifstream in(PATH2);

    if (in.is_open())
    {
        int i = 0;
        while (getline(in, line))
        {
            cars.push_back(deserializeCarFromString(line));
            i++;
        }
    }
    in.close();
    return cars;
}

int getIndexByNum(string num, vector<car>* cars) { //определяем какая машина в списке по номеру
    int i;
    for (i = 0; i < cars->size(); i++) {
        if (cars->at(i).num == num) {
            return i;
        }
    }
    return -1;
}

int getIndexByBrand(string br, vector<car>* cars) { //определяем какой автомобиль в списке по марке
    int i;
    for (i = 0; i < cars->size(); i++) {
        if (cars->at(i).br == br) {
            return i;
        }
    }
    return -1;
}

void Caradd(vector<car>* cars) { //добавление нового автомобиля
    car n;
    bool b = false;
    int flag, i, temp, j;
    string s1, s2, s3, s4, s, sa, sch, stemp1, stemp2;
    cout << "Start registering a new car." << endl;
    cout << endl;

    cout << "Please, enter your driver's license number." << endl;
    cout << "Please, enter numbers of your license number: (input format - NNNNN) ";
    cin >> sa;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sa.length(); i++) {
            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sa.length()) && (temp == 5)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sa;
        }
    }
    cout << "Please, enter letters of your license number: (input format - AAA) ";
    cin >> sch;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sch.length(); i++) {
            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == sch.length()) && (temp == 3)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sch;
        }
    }

    s1 = sch + " " + sa;
    for (i = 1; i < 3; i++) {
        stemp1 += sch[i];
    }
    for (i = 0; i < 3; i++) {
        stemp2 += sa[i];
    }
    j = 0;
    for (i = 4; i < 6; i++) {
        s1[i] = stemp1[j];
        j++;
    }
    j = 0;
    for (i = 1; i < 4; i++) {
        s1[i] = stemp2[j];
        j++;
    }
    for (i = 0; i < s1.length(); i++) {
        if (i == 6) {
            s1[i] = '-';
        }
    }

    n.num = s1;
    if (getIndexByNum(n.num, cars) == -1) {

        cout << "Please, enter car brand: ";
        cin >> s2;
        n.br = s2;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < n.br.length(); i++) {
                if ((int(n.br[i]) > 47) && (int(n.br[i]) < 58)) {
                    temp++;
                }
            }
            if (temp > 0) {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> s2;
                n.br = s2;
            }
            else {
                flag = 1;
            }
        }
        cout << "Please, enter car colour: ";
        cin >> s3;
        n.col = s3;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < n.col.length(); i++) {
                if ((int(n.col[i]) > 47) && (int(n.col[i]) < 58)) {
                    temp++;
                }
            }
            if (temp > 0) {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> s3;
                n.col = s3;
            }
            else {
                flag = 1;
            }
        }
        cout << "Please, enter car year: ";
        cin >> s4;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < s4.length(); i++) {
                if ((int(s4[i]) > 64) && (int(s4[i]) < 91) && (int(s4[i]) > 96) && (int(s4[i]) < 123)) {
                    temp++;
                }
            }
            if (temp > 0) {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> s4;
            }
            else {
                flag = 1;
            }
        }
        n.year = stoi(s4);

        n.avail = 1;

        cars->push_back(n);
        cout << endl;
        cout << "Car added successfully." << endl;
        cout << endl;
    }
    else {
        cout << "Same car already is in base!" << endl;
    }
}

void printCarInfo(car* n) { //выводим данные одного автомобиля
    cout << serializeCarToString(n) << endl;
}

void printCarList(vector<car>* cars) { //выводим данные всех автомобилей
    int i;
    for (i = 0; i < cars->size(); i++) {
        printCarInfo(&cars->at(i));
    }
}

void delIndexByNum(string num, vector<car>* cars) { //удаление по номеру
    for (int i = 0; i < cars->size(); i++) {
        if (cars->at(i).num == num) {
            cars->erase(cars->begin() + getIndexByNum(num, cars));
        }
    }
}

int Carcheck(vector<car> cars) { //проверка на соответствие всем условиям
    string s, f;
    int flag = 0;
    int temp1, temp2, temp3, i, j;
    int temp = 0;
    for (j = 0; j < cars.size(); j++) {
        s = serializeCarToString(&cars[j]);
        for (i = 0; i < 1; i++) {
            if ((int(s[i]) == 65) || (int(s[i]) == 66)) {}
            else {
                flag = 1;
                break;
            }
        }
        for (i = 1; i < 4; i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                flag = 1;
                break;
            }
        }
        for (i = 4; i < 6; i++) {
            if ((int(s[i]) == 65) || (int(s[i]) == 66)) {}
            else {
                flag = 1;
                break;
            }
        }
        for (i = 6; i < 7; i++) {
            if ((int(s[i]) != 45)) {
                flag = 1;
                break;
            }
        }
        for (i = 7; i < s.length(); i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                flag = 1;
                break;
            }
            if (s[i] == ';') {
                temp1 = i;
                break;
            }
        }
        if (flag == 0) {
            for (i = temp1 + 1; i < s.length(); i++) {
                if (s[i] == ';') {
                    temp2 = i;
                    break;
                }
                if (((int(s[i]) > 47) && (int(s[i]) < 58))) {
                    //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    temp2 = i;
                    break;
                }
            }
        }
        if (flag == 0) {
            for (i = temp2 + 1; i < s.length(); i++) {
                if (s[i] == ';') {
                    temp3 = i;
                    break;
                }
                if (((int(s[i]) > 47) && (int(s[i]) < 58))) {
                    //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    temp3 = i;
                    break;
                }
            }
        }
        if (flag == 0) {
            for (i = temp3 + 1; i < s.length(); i++) {
                if (s[i] == ';') {
                    break;
                }
                if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                    //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                    flag = 1;
                    break;
                }
            }
        }
        return flag;
        flag = 0;
    }
}

//-----------------------------------------------

struct rent {
    string carinf;
    string clientinf;
    string data;
};

string serializeRentToString(rent* n) { //набор характеристик превращаем в строку
    string result = n->carinf + ";" + n->clientinf + ";" + n->data;
    return result;
}

rent deserializeRentFromString(string serialized) {  //строку превращаем в набор характеристик
    vector<string> parts = split(serialized, ";");
    rent n;
    n.carinf = parts[0];
    n.clientinf = parts[1];
    n.data = parts[2];

    return n;
}

int getIndexByInf(string clientinf, vector<rent>* rents) { //номер в списке по клиенту
    int i;
    for (i = 0; i < rents->size(); i++) {
        if (rents->at(i).clientinf == clientinf) {
            return i;
        }
    }
    return -1;
}

int getIndexByInf2(string carinf, vector<rent>* rents) { //номер в списке по машине
    int i;
    for (i = 0; i < rents->size(); i++) {
        if (rents->at(i).carinf == carinf) {
            return i;
        }
    }
    return -1;
}

void saveRentsInFile(vector<rent> rents) { //сохраняем данные в файл
    ofstream out;
    out.open(PATH3);
    int i;

    if (out.is_open())
    {
        for (i = 0; i < rents.size(); i++) {
            out << serializeRentToString(&rents[i]);
            if (i != rents.size() - 1) {
                out << endl;
            }
        }
    }
    cout << "Save completed successfulyy." << endl;
    out.close();
}

vector<rent> loadRentsFromFile() { //выгружаем информацию из файла
    vector<rent> rents;
    string line;
    ifstream in(PATH3);

    if (in.is_open())
    {
        int i = 0;
        while (getline(in, line))
        {
            rents.push_back(deserializeRentFromString(line));
            i++;
        }
    }
    in.close();
    return rents;
}

void delIndexByInf(string clientinf, vector<rent>* rents) { //удалить по клиенту
    for (int i = 0; i < rents->size(); i++) {
        if (rents->at(i).clientinf == clientinf) {
            rents->erase(rents->begin() + getIndexByInf(clientinf, rents));
        }
    }
}

void Clientedit(vector<client>* clients, vector<rent>* rents) { //редактируем данные о клиенте
    int i, flag, temp;
    string sf, ss, st, num, s2, s3, s4, s, sc;
    cout << "Please, enter number of client you want to edit: ";
    cin >> sf;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sf.length(); i++) {
            if ((int(sf[i]) > 47) && (int(sf[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sf.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sf;
        }
    }
    cin >> ss;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < ss.length(); i++) {
            if ((int(ss[i]) == 65) || (int(ss[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == ss.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> ss;
        }
    }
    cin >> st;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < st.length(); i++) {
            if ((int(st[i]) > 47) && (int(st[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == st.length()) && (temp == 6)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> st;
        }
    }
    num = sf + " " + ss + " " + st;
    sc = num;
    if (getIndexByNum(num, clients) != -1) {
        client* n = &clients->at(getIndexByNum(num, clients));
        cout << "Please, enter NEW driver's license number. (NOT 00 AA 000000)" << endl;
        cout << "Please, enter NEW region code: (input format - NN) ";
        cin >> sf;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < sf.length(); i++) {
                if ((int(sf[i]) > 47) && (int(sf[i]) < 58)) {
                    temp++;
                }
            }
            if ((temp == sf.length()) && (temp == 2)) {
                flag = 1;
            }
            else {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> sf;
            }
        }
        cout << "Please, enter NEW series: (input format - AA)";
        cin >> ss;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < ss.length(); i++) {
                if ((int(ss[i]) == 65) || (int(ss[i]) == 66)) {
                    temp++;
                }
            }
            if ((temp == ss.length()) && (temp == 2)) {
                flag = 1;
            }
            else {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> ss;
            }
        }
        cout << "Please, enter NEW number: (input format - NNNNNN)";
        cin >> st;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < st.length(); i++) {
                if ((int(st[i]) > 47) && (int(st[i]) < 58)) {
                    temp++;
                }
            }
            if ((temp == st.length()) && (temp == 6)) {
                flag = 1;
            }
            else {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> st;
            }
        }
        num = sf + " " + ss + " " + st;
        if (getIndexByInf(sc, rents) != -1) {
            rent* m = &rents->at(getIndexByInf(sc, rents));
            m->clientinf = num;
            saveRentsInFile(*rents);
        }
        if (getIndexByNum(num, clients) == -1) {
            n->num = num;
            cout << "Please, enter NEW fullname: (with one gap)";
            cin >> s2;
            cin >> s;
            s2 = s2 + " " + s;
            n->fio = s2;
            flag = 0;
            while (flag == 0) {
                temp = 0;
                for (i = 0; i < n->fio.length(); i++) {
                    if ((int(n->fio[i]) > 47) && (int(n->fio[i]) < 58)) {
                        temp++;
                    }
                }
                if (temp > 0) {
                    cout << "Sorry, wrong input. Try one more time, please." << endl;
                    cin >> s2;
                    cin >> s;
                    s2 = s2 + " " + s;
                    n->fio = s2;
                }
                else {
                    flag = 1;
                }
            }
            cout << "Please, enter NEW passport details: (with one gap)";
            cin >> s3;
            cin >> s;
            s3 = s3 + " " + s;
            n->pd = s3;
            flag = 0;
            while (flag == 0) {
                temp = 0;
                for (i = 0; i < n->pd.length(); i++) {
                    if ((int(n->pd[i]) > 64) && (int(n->pd[i]) < 91) && (int(n->pd[i]) > 96) && (int(n->pd[i]) < 123)) {
                        temp++;
                    }
                }
                if (temp > 0) {
                    cout << "Sorry, wrong input. Try one more time, please." << endl;
                    cin >> s3;
                    cin >> s;
                    s3 = s3 + " " + s;
                    n->pd = s3;
                }
                else {
                    flag = 1;
                }
            }
            cout << "Please, enter NEW adress. Please, enter your street: ";
            cin >> s4;
            flag = 0;
            while (flag == 0) {
                temp = 0;
                for (i = 0; i < s4.length(); i++) {
                    if ((int(s4[i]) > 47) && (int(s4[i]) < 58)) {
                        temp++;
                    }
                }
                if (temp > 0) {
                    cout << "Sorry, wrong input. Try one more time, please." << endl;
                    cin >> s4;
                }
                else {
                    flag = 1;
                }
            }
            cout << "Please, enter NEW house: ";
            cin >> s;
            flag = 0;
            while (flag == 0) {
                temp = 0;
                for (i = 0; i < s.length(); i++) {
                    if ((int(s[i]) > 64) && (int(s[i]) < 91) && (int(s[i]) > 96) && (int(s[i]) < 123)) {
                        temp++;
                    }
                }
                if (temp > 0) {
                    cout << "Sorry, wrong input. Try one more time, please." << endl;
                    cin >> s;
                }
                else {
                    flag = 1;
                }
            }
            s4 = s4 + " " + s;
            n->adr = s4;

            cout << endl;
            cout << "Client added successfully." << endl;
            cout << endl;
        }
        else {
            cout << "Same client already is in base!" << endl;
        }
    }
    else {
        cout << "No clients with same number." << endl;
    }
}

void Clientdelete(vector<client>* clients, vector<rent>* rents) { //удаление клиента
    int i, flag, temp;
    string sf, ss, st, num, s2, s3, s4, s;
    cout << "Please, enter number of client you want to edit: (two gaps)";
    cin >> sf;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sf.length(); i++) {
            if ((int(sf[i]) > 47) && (int(sf[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sf.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sf;
        }
    }
    cin >> ss;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < ss.length(); i++) {
            if ((int(ss[i]) == 65) || (int(ss[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == ss.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> ss;
        }
    }
    cin >> st;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < st.length(); i++) {
            if ((int(st[i]) > 47) && (int(st[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == st.length()) && (temp == 6)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> st;
        }
    }
    num = sf + " " + ss + " " + st;
    if (getIndexByNum(num, clients) != -1) {
        if (getIndexByInf(num, rents) != -1) {
            cout << "Can't delete client, because he has a car now." << endl;
        }
        else {
            clients->erase(clients->begin() + getIndexByNum(num, clients));
            cout << "Client deleted." << endl;
        }
    }
    else {
        cout << "No clients with same number." << endl;
    }
}

void Caredit(vector<car>* cars, vector<rent>* rents) { //редактируем информацию об автомобиле
    bool b;
    b = false;
    int i, flag, temp, j;
    string sf, ss, st, num, s1, s2, s3, s4, s, stemp1, stemp2, sc;
    cout << "Please, enter number of car you want to edit: ";
    cout << "Please, enter numbers of your license number: (input format - NNNNN) ";
    cin >> sf;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sf.length(); i++) {
            if ((int(sf[i]) > 47) && (int(sf[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sf.length()) && (temp == 5)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sf;
        }
    }
    cout << "Please, enter letters of your license number: (input format - AAA) ";
    cin >> ss;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < ss.length(); i++) {
            if ((int(ss[i]) == 65) || (int(ss[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == ss.length()) && (temp == 3)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> ss;
        }
    }

    s1 = ss + " " + sf;
    for (i = 1; i < 3; i++) {
        stemp1 += ss[i];
    }
    for (i = 0; i < 3; i++) {
        stemp2 += sf[i];
    }
    j = 0;
    for (i = 4; i < 6; i++) {
        s1[i] = stemp1[j];
        j++;
    }
    j = 0;
    for (i = 1; i < 4; i++) {
        s1[i] = stemp2[j];
        j++;
    }
    for (i = 0; i < s1.length(); i++) {
        if (i == 6) {
            s1[i] = '-';
        }
    }
    num = s1;
    if (getIndexByNum(num, cars) != -1) {
        car* n = &cars->at(getIndexByNum(num, cars));

        cout << "Please, enter NEW driver's license number." << endl;
        cout << "Please, enter NEW numbers of license number: (input format - NNNNN) ";
        cin >> sf;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < sf.length(); i++) {
                if ((int(sf[i]) > 47) && (int(sf[i]) < 58)) {
                    temp++;
                }
            }
            if ((temp == sf.length()) && (temp == 5)) {
                flag = 1;
            }
            else {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> sf;
            }
        }
        cout << "Please, enter letters of your license number: (input format - AAA) ";
        cin >> ss;
        flag = 0;
        while (flag == 0) {
            temp = 0;
            for (i = 0; i < ss.length(); i++) {
                if ((int(ss[i]) == 65) || (int(ss[i]) == 66)) {
                    temp++;
                }
            }
            if ((temp == ss.length()) && (temp == 3)) {
                flag = 1;
            }
            else {
                cout << "Sorry, wrong input. Try one more time, please." << endl;
                cin >> ss;
            }
        }

        s1 = ss + " " + sf;
        stemp1 = "";
        stemp2 = "";
        for (i = 1; i < 3; i++) {
            stemp1 += ss[i];
        }
        for (i = 0; i < 3; i++) {
            stemp2 += sf[i];
        }
        j = 0;
        for (i = 4; i < 6; i++) {
            s1[i] = stemp1[j];
            j++;
        }
        j = 0;
        for (i = 1; i < 4; i++) {
            s1[i] = stemp2[j];
            j++;
        }
        for (i = 0; i < s1.length(); i++) {
            if (i == 6) {
                s1[i] = '-';
            }
        }
        sc = s1;
        if (getIndexByInf2(num, rents) != -1) {
            rent* m = &rents->at(getIndexByInf2(num, rents));
            m->carinf = sc;
            saveRentsInFile(*rents);
        }
        if (getIndexByNum(sc, cars) == -1) {
            n->num = sc;
            cout << "Please, enter NEW car brand: ";
            cin >> s2;
            n->br = s2;
            flag = 0;
            while (flag == 0) {
                temp = 0;
                for (i = 0; i < n->br.length(); i++) {
                    if ((int(n->br[i]) > 47) && (int(n->br[i]) < 58)) {
                        temp++;
                    }
                }
                if (temp > 0) {
                    cout << "Sorry, wrong input. Try one more time, please." << endl;
                    cin >> s2;
                    n->br = s2;
                }
                else {
                    flag = 1;
                }
            }
            cout << "Please, enter NEW car colour: ";
            cin >> s3;
            n->col = s3;
            flag = 0;
            while (flag == 0) {
                temp = 0;
                for (i = 0; i < n->col.length(); i++) {
                    if ((int(n->col[i]) > 64) && (int(n->col[i]) < 91) && (int(n->col[i]) > 96) && (int(n->col[i]) < 123)) {
                        temp++;
                    }
                }
                if (temp > 0) {
                    cout << "Sorry, wrong input. Try one more time, please." << endl;
                    cin >> s3;
                    n->col = s3;
                }
                else {
                    flag = 1;
                }
            }
            cout << "Please, enter NEW year: ";
            cin >> s4;
            flag = 0;
            while (flag == 0) {
                temp = 0;
                for (i = 0; i < s4.length(); i++) {
                    if ((int(s4[i]) > 64) && (int(s4[i]) < 91) && (int(s4[i]) > 96) && (int(s4[i]) < 123)) {
                        temp++;
                    }
                }
                if (temp > 0) {
                    cout << "Sorry, wrong input. Try one more time, please." << endl;
                    cin >> s4;
                }
                else {
                    flag = 1;
                }
            }
            n->year = stoi(s4);

            n->avail = 1;

            cout << endl;
            cout << "Car information changed successfully." << endl;
            cout << endl;
        }
        else {
            cout << "Same car already is in base!" << endl;
        }
    }
    else {
        cout << "No cars with same number." << endl;
    }
}

void Cardelete(vector<car>* cars, vector<rent>* rents) { //удаление автомобиля
    int i, flag, temp, j;
    string sf, ss, st, num, s1, s2, s3, s4, s, stemp1, stemp2;
    cout << "Please, enter number of car you want to edit: (two gaps)";
    cin >> sf;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sf.length(); i++) {
            if ((int(sf[i]) > 47) && (int(sf[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sf.length()) && (temp == 5)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sf;
        }
    }
    cout << "Please, enter letters of your license number: (input format - AAA) ";
    cin >> ss;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < ss.length(); i++) {
            if ((int(ss[i]) == 65) || (int(ss[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == ss.length()) && (temp == 3)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> ss;
        }
    }

    s1 = ss + " " + sf;
    for (i = 1; i < 3; i++) {
        stemp1 += ss[i];
    }
    for (i = 0; i < 3; i++) {
        stemp2 += sf[i];
    }
    j = 0;
    for (i = 4; i < 6; i++) {
        s1[i] = stemp1[j];
        j++;
    }
    j = 0;
    for (i = 1; i < 4; i++) {
        s1[i] = stemp2[j];
        j++;
    }
    for (i = 0; i < s1.length(); i++) {
        if (i == 6) {
            s1[i] = '-';
        }
    }
    num = s1;
    if (getIndexByNum(num, cars) != -1) {
        if (getIndexByInf2(num, rents) != -1) {
            cout << "Can't delete car, because it is in rent now." << endl;
        }
        else {
            cars->erase(cars->begin() + getIndexByNum(num, cars));
            cout << "Car deleted." << endl;
        }
    }
    else {
        cout << "No cars with same number." << endl;
    }
}

void CarforRep(vector<car> cars, vector<rent>* rents) { //сдать машину в ремонт
    rent n;
    ofstream out;
    out.open(PATH3);
    string sa, sb, sch, stemp1, stemp2, s1, scar, sc, sd1, sd2, sd3, sd, sdd;
    sc = "00 AA 000000";
    int flag, temp, i, j;
    cout << "Please, enter your driver's license number." << endl;
    cout << "Please, enter numbers of your license number: (input format - NNNNN) ";
    cin >> sa;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sa.length(); i++) {
            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sa.length()) && (temp == 5)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sa;
        }
    }
    cout << "Please, enter letters of your license number: (input format - AAA) ";
    cin >> sch;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sch.length(); i++) {
            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == sch.length()) && (temp == 3)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sch;
        }
    }
    s1 = sch + " " + sa;
    for (i = 1; i < 3; i++) {
        stemp1 += sch[i];
    }
    for (i = 0; i < 3; i++) {
        stemp2 += sa[i];
    }
    j = 0;
    for (i = 4; i < 6; i++) {
        s1[i] = stemp1[j];
        j++;
    }
    j = 0;
    for (i = 1; i < 4; i++) {
        s1[i] = stemp2[j];
        j++;
    }
    for (i = 0; i < s1.length(); i++) {
        if (i == 6) {
            s1[i] = '-';
        }
    }
    cout << endl;
    scar = s1;
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].num == scar) {
            printCarInfo(&cars[i]);
            if (cars[i].avail == 1) {
                cars[i].avail = 0;
                cout << "Please, enter the date when the machine ordered for repair." << endl;
                cout << "Please, enter the day: ";
                cin >> sd1;
                flag = 0;
                while (flag == 0) {
                    temp = 0;
                    if ((stoi(sd1) < 32) && (stoi(sd1) > 0)) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sd1;
                    }
                }
                cout << "Please, enter the month: ";
                cin >> sd2;
                flag = 0;
                while (flag == 0) {
                    temp = 0;
                    if ((stoi(sd2) < 13) && (stoi(sd2) > 0)) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sd2;
                    }
                }
                cout << "Please, enter the year: ";
                cin >> sd3;
                flag = 0;
                while (flag == 0) {
                    temp = 0;
                    if (stoi(sd3) == 2023) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sd3;
                    }
                }
                sd = sd1 + "." + sd2 + "." + sd3;
                sd1 = sd2 = sd3 = "";

                cout << "Please, enter the date when the machine will remove from repair." << endl;
                cout << "Please, enter the day: ";
                cin >> sd1;
                flag = 0;
                while (flag == 0) {
                    if ((stoi(sd1) < 32) && (stoi(sd1) > 0)) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sd1;
                    }
                }
                cout << "Please, enter the month: ";
                cin >> sd2;
                flag = 0;
                while (flag == 0) {
                    if ((stoi(sd2) < 13) && (stoi(sd2) > 0)) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sd2;
                    }
                }
                cout << "Please, enter the year: ";
                cin >> sd3;
                flag = 0;
                while (flag == 0) {
                    if (stoi(sd3) > 2022) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sd3;
                    }
                }
                sdd = sd1 + "." + sd2 + "." + sd3;

                saveCarsInFile(cars);
                n.clientinf = sc;
                n.carinf = scar;
                n.data = sd + "-" + sdd;
                rents->push_back(n);
                cout << "This car is in repair now." << endl;
            }
            else {
                cout << "This car is not available now." << endl;
            }
        }
    }
}

void CarfromRep(vector<car> cars, vector<rent>* rents) { //вернуть машину из ремонта
    rent n;
    ofstream out;
    out.open(PATH3);
    string sa, sb, sch, stemp1, stemp2, s1, scar, sc;
    sc = "00 AA 000000";
    int flag, temp, i, j;
    cout << "Please, enter your driver's license number." << endl;
    cout << "Please, enter numbers of your license number: (input format - NNNNN) ";
    cin >> sa;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sa.length(); i++) {
            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sa.length()) && (temp == 5)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sa;
        }
    }
    cout << "Please, enter letters of your license number: (input format - AAA) ";
    cin >> sch;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sch.length(); i++) {
            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == sch.length()) && (temp == 3)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sch;
        }
    }
    s1 = sch + " " + sa;
    for (i = 1; i < 3; i++) {
        stemp1 += sch[i];
    }
    for (i = 0; i < 3; i++) {
        stemp2 += sa[i];
    }
    j = 0;
    for (i = 4; i < 6; i++) {
        s1[i] = stemp1[j];
        j++;
    }
    j = 0;
    for (i = 1; i < 4; i++) {
        s1[i] = stemp2[j];
        j++;
    }
    for (i = 0; i < s1.length(); i++) {
        if (i == 6) {
            s1[i] = '-';
        }
    }
    cout << endl;
    scar = s1;
    if (getIndexByInf2(scar, rents) != -1) {
        rents->erase(rents->begin() + getIndexByInf2(scar, rents));
        cout << "Repair is over successfully." << endl;
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].num == scar) {
                //printCarInfo(&cars[i]);
                if (cars[i].avail == 0) {
                    cars[i].avail = 1;
                    saveCarsInFile(cars);
                }
                else {
                    cout << "This car is already available now." << endl;
                }
            }
        }
    }
    else {
        cout << "Now car with same number." << endl;
    }
}

void CartoClient(vector<car> cars, vector<client> clients, vector<rent>* rents) { //сдать машину в аренду
    rent n;
    ofstream out;
    out.open(PATH3);
    string sa, sb, sch, stemp1, stemp2, s1, scar, sd1, sd2, sd3, sd, sdd;
    int flag, temp, i, j;
    cout << "Please, enter your driver's license number." << endl;
    cout << "Please, enter numbers of your license number: (input format - NNNNN) ";
    cin >> sa;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sa.length(); i++) {
            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sa.length()) && (temp == 5)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sa;
        }
    }
    cout << "Please, enter letters of your license number: (input format - AAA) ";
    cin >> sch;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sch.length(); i++) {
            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == sch.length()) && (temp == 3)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sch;
        }
    }
    s1 = sch + " " + sa;
    for (i = 1; i < 3; i++) {
        stemp1 += sch[i];
    }
    for (i = 0; i < 3; i++) {
        stemp2 += sa[i];
    }
    j = 0;
    for (i = 4; i < 6; i++) {
        s1[i] = stemp1[j];
        j++;
    }
    j = 0;
    for (i = 1; i < 4; i++) {
        s1[i] = stemp2[j];
        j++;
    }
    for (i = 0; i < s1.length(); i++) {
        if (i == 6) {
            s1[i] = '-';
        }
    }
    cout << endl;
    scar = s1;
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].num == scar) {
            printCarInfo(&cars[i]);
            if (cars[i].avail == 1) {
                cars[i].avail = 0;
                saveCarsInFile(cars);
                cout << "Please, enter your driver's license number." << endl;
                cout << "Please, enter your region code: (input format - NN) ";
                cin >> sa;
                flag = 0;
                while (flag == 0) {
                    temp = 0;
                    for (i = 0; i < sa.length(); i++) {
                        if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                            temp++;
                        }
                    }
                    if ((temp == sa.length()) && (temp == 2)) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sa;
                    }
                }
                cout << "Please, enter your series: (input format - AA)";
                cin >> sch;
                flag = 0;
                while (flag == 0) {
                    temp = 0;
                    for (i = 0; i < sch.length(); i++) {
                        if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                            temp++;
                        }
                    }
                    if ((temp == sch.length()) && (temp == 2)) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sch;
                    }
                }
                cout << "Please, enter your number: (input format - NNNNNN)";
                cin >> sb;
                flag = 0;
                while (flag == 0) {
                    temp = 0;
                    for (i = 0; i < sb.length(); i++) {
                        if ((int(sb[i]) > 47) && (int(sb[i]) < 58)) {
                            temp++;
                        }
                    }
                    if ((temp == sb.length()) && (temp == 6)) {
                        flag = 1;
                    }
                    else {
                        cout << "Sorry, wrong input. Try one more time, please." << endl;
                        cin >> sb;
                    }
                }
                s1 = sa + " " + sch + " " + sb;
                cout << endl;
                for (int i = 0; i < clients.size(); i++) {
                    if (clients[i].num == s1) {
                        printClientInfo(&clients[i]);
                        if (out.is_open()) {
                            for (i = 0; i < clients.size(); i++) {
                                if (clients[i].num == s1) {
                                    cout << "Please, enter the date when the machine ordered for repair." << endl;
                                    cout << "Please, enter the day: ";
                                    cin >> sd1;
                                    flag = 0;
                                    while (flag == 0) {
                                        temp = 0;
                                        if ((stoi(sd1) < 32) && (stoi(sd1) > 0)) {
                                            flag = 1;
                                        }
                                        else {
                                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                                            cin >> sd1;
                                        }
                                    }
                                    cout << "Please, enter the month: ";
                                    cin >> sd2;
                                    flag = 0;
                                    while (flag == 0) {
                                        temp = 0;
                                        if ((stoi(sd2) < 13) && (stoi(sd2) > 0)) {
                                            flag = 1;
                                        }
                                        else {
                                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                                            cin >> sd2;
                                        }
                                    }
                                    cout << "Please, enter the year: ";
                                    cin >> sd3;
                                    flag = 0;
                                    while (flag == 0) {
                                        temp = 0;
                                        if (stoi(sd3) == 2023) {
                                            flag = 1;
                                        }
                                        else {
                                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                                            cin >> sd3;
                                        }
                                    }
                                    sd = sd1 + "." + sd2 + "." + sd3;
                                    sd1 = sd2 = sd3 = "";

                                    cout << "Please, enter the date when the machine will remove from repair." << endl;
                                    cout << "Please, enter the day: ";
                                    cin >> sd1;
                                    flag = 0;
                                    while (flag == 0) {
                                        if ((stoi(sd1) < 32) && (stoi(sd1) > 0)) {
                                            flag = 1;
                                        }
                                        else {
                                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                                            cin >> sd1;
                                        }
                                    }
                                    cout << "Please, enter the month: ";
                                    cin >> sd2;
                                    flag = 0;
                                    while (flag == 0) {
                                        if ((stoi(sd2) < 13) && (stoi(sd2) > 0)) {
                                            flag = 1;
                                        }
                                        else {
                                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                                            cin >> sd2;
                                        }
                                    }
                                    cout << "Please, enter the year: ";
                                    cin >> sd3;
                                    flag = 0;
                                    while (flag == 0) {
                                        if (stoi(sd3) > 2022) {
                                            flag = 1;
                                        }
                                        else {
                                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                                            cin >> sd3;
                                        }
                                    }
                                    sdd = sd1 + "." + sd2 + "." + sd3;

                                    n.clientinf = s1;
                                    n.carinf = scar;
                                    n.data = sd + "-" + sdd;
                                    rents->push_back(n);
                                }
                            }
                        }
                    }
                }
                cout << "This car is your for now." << endl;
            }
            else {
                cout << "This car is not available now." << endl;
            }
        }
    }
}

void CarfromClient(vector<car>* cars, vector<client> clients, vector<rent>* rents) { //вернуть машину из аренды
    ofstream out;
    out.open(PATH3);
    string sa, sb, sch, stemp1, stemp2, s1, scar;
    int flag, temp, i;
    cout << "Please, enter your driver's license number." << endl;
    cout << "Please, enter your region code: (input format - NN) ";
    cin >> sa;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sa.length(); i++) {
            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sa.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sa;
        }
    }
    cout << "Please, enter your series: (input format - AA)";
    cin >> sch;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sch.length(); i++) {
            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                temp++;
            }
        }
        if ((temp == sch.length()) && (temp == 2)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sch;
        }
    }
    cout << "Please, enter your number: (input format - NNNNNN)";
    cin >> sb;
    flag = 0;
    while (flag == 0) {
        temp = 0;
        for (i = 0; i < sb.length(); i++) {
            if ((int(sb[i]) > 47) && (int(sb[i]) < 58)) {
                temp++;
            }
        }
        if ((temp == sb.length()) && (temp == 6)) {
            flag = 1;
        }
        else {
            cout << "Sorry, wrong input. Try one more time, please." << endl;
            cin >> sb;
        }
    }
    s1 = sa + " " + sch + " " + sb;
    cout << endl;
    if (getIndexByInf(s1, rents) != -1) {
        rent* m = &rents->at(getIndexByInf(s1, rents));
        scar = m->carinf;
        if (getIndexByNum(scar, cars) != -1) {
            car* k = &cars->at(getIndexByNum(scar, cars));
            k->avail = 1;
            saveCarsInFile(*cars);
        }
        rents->erase(rents->begin() + getIndexByInf(s1, rents));
        cout << "Rent is over succesfully." << endl;
    }
    else {
        cout << "No clients with same number." << endl;
    }
}

int Rentcheck(vector<car> cars, vector<client> clients, vector<rent> rents) {
    string s, f;
    int flag = 0;
    int temp1, i, j, tempf, temps;
    int temp = 0;
    int ultratemp = 0;
    for (j = 0; j < rents.size(); j++) {
        s = serializeRentToString(&rents[j]);
        for (i = 0; i < 1; i++) {
            if ((int(s[i]) == 65) || (int(s[i]) == 66)) {}
            else {
                flag = 1;
                break;
            }
        }
        for (i = 1; i < 4; i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                flag = 1;
                break;
            }
        }
        for (i = 4; i < 6; i++) {
            if ((int(s[i]) == 65) || (int(s[i]) == 66)) {}
            else {
                flag = 1;
                break;
            }
        }
        for (i = 6; i < 7; i++) {
            if ((int(s[i]) != 45)) {
                flag = 1;
                break;
            }
        }
        for (i = 7; i < s.length(); i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                flag = 1;
                break;
            }
            if (s[i] == ';') {
                temp1 = i;
                break;
            }
        }
        if (flag == 1) {
            return flag;
            break;
        }
        flag = 0;
        temp = 0;
        s = serializeRentToString(&rents[j]);
        for (i = temp1 + 1; i < s.length(); i++) {
            if ((s[i] == ' ') && (temp == 0)) {
                tempf = i;
                temp++;
            }
            if ((s[i] == ' ') && (temp == 1)) {
                temps = i;
            }
            if (s[i] == ';') {
                break;
            }
        }
        for (i = temp1 + 1; i < tempf; i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                flag = 1;
                break;
            }
        }
        for (i = tempf + 1; i < temps; i++) {
            if ((int(s[i]) != 65) && (int(s[i]) != 66)) {
                //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                flag = 1;
                break;
            }
        }
        for (i = temps + 1; i < s.length(); i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                flag = 1;
                break;
            }
            if (s[i] == ';') {
                temp1 = i;
                break;
            }
        }
        if (flag == 1) {
            return flag;
            break;
        }
        flag = 0;
        for (i = temp1 + 1; i < s.length(); i++) {
            if (((int(s[i]) > 96) && (int(s[i]) < 123)) || ((int(s[i]) > 64) && (int(s[i]) < 91))) {
                //cout << "Error in file on " << j + 1 << " line!" << endl << endl;
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            return flag;
            break;
        }
        flag = 0;
    }
}

int Rentcheck2(vector<car> cars, vector<client> clients, vector<rent> rents) {
    string cl, s, ca;
    int flag = 0;
    int i, j;
    for (j = 0; j < rents.size(); j++) {
        s = serializeRentToString(&rents[j]);
        for (i = 0; i < 9; i++) {
            ca += s[i];
        }
        for (i = 10; i < 22; i++) {
            cl += s[i];
        }
    }
    if ((getIndexByNum(ca, &cars) == -1) || (getIndexByNum(cl, &clients) == -1)) {
        return 1;
    }
    else {
        return 0;
    }
}

//-------------------------------------------------

void menu() {
    cout << "1. Clients" << endl
        << "2. Cars" << endl
        << "3. Rent" << endl
        << "0. Exit" << endl;
}

void Clienthelp() {
    cout << "1. Add new client" << endl
        << "2. Edit existing client" << endl
        << "3. Delete existing client by license number" << endl
        << "4. Search for existing client" << endl
        << "5. Print all existing clients" << endl
        << "6. Load from file" << endl
        << "7. Save to file" << endl
        << "9. Return to main menu" << endl
        << "0. Exit" << endl;
}

void Carshelp() {
    cout << "1. Add new car" << endl
        << "2. Edit existing car" << endl
        << "3. Delete existing car" << endl
        << "4. Search for existing car by license number" << endl
        << "5. Print all existing cars" << endl
        << "6. Load from file" << endl
        << "7. Save to file" << endl
        << "8. Search for existing car by car brand" << endl
        << "9. Return to main menu" << endl
        << "0. Exit" << endl;
}

void Renthelp() {
    cout << "1. Car for repair" << endl
        << "2. Car from repair" << endl
        << "3. Rent out car to client" << endl
        << "4. Return car to rent" << endl
        << "5. Save rent changes" << endl
        << "9. Return to main menu" << endl
        << "0. Exit" << endl;
}

int Menu(vector<car> cars, vector<client> clients, vector<rent> rents) {
    int n = -1;
    int m = -1;
    string sa, sb, sch, s1, s2, stemp1, stemp2;
    int i, j, flag, temp;
    while (m != 3) {
        menu();
        cin >> m;
        while (cin.fail() || cin.get() != '\n') {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail());
            cout << "Sorry, wrong input, please try again.";
            cin >> m;
        }
        switch (m) {
        case 1: {
            while (n != 0) {
                cout << "Please, press any key to continue." << endl;
                _getch();
                system("cls");

                Clienthelp();
                cin >> n;
                while (cin.fail() || cin.get() != '\n') {
                    cin.clear();
                    cin.ignore(cin.rdbuf()->in_avail());
                    cout << "Sorry, wrong input, please try again.";
                    cin >> n;
                }
                switch (n) {
                case 1: {
                    Clientadd(&clients);
                    break;
                }
                case 2: {
                    Clientedit(&clients, &rents);
                    break;
                }
                case 3: {
                    Clientdelete(&clients, &rents);
                    break;
                }
                case 4: {
                    cout << "Please, enter your driver's license number." << endl;
                    cout << "Please, enter your region code: (input format - NN) ";
                    cin >> sa;
                    flag = 0;
                    while (flag == 0) {
                        temp = 0;
                        for (i = 0; i < sa.length(); i++) {
                            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                                temp++;
                            }
                        }
                        if ((temp == sa.length()) && (temp == 2)) {
                            flag = 1;
                        }
                        else {
                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                            cin >> sa;
                        }
                    }
                    cout << "Please, enter your series: (input format - AA)";
                    cin >> sch;
                    flag = 0;
                    while (flag == 0) {
                        temp = 0;
                        for (i = 0; i < sch.length(); i++) {
                            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                                temp++;
                            }
                        }
                        if ((temp == sch.length()) && (temp == 2)) {
                            flag = 1;
                        }
                        else {
                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                            cin >> sch;
                        }
                    }
                    cout << "Please, enter your number: (input format - NNNNNN)";
                    cin >> sb;
                    flag = 0;
                    while (flag == 0) {
                        temp = 0;
                        for (i = 0; i < sb.length(); i++) {
                            if ((int(sb[i]) > 47) && (int(sb[i]) < 58)) {
                                temp++;
                            }
                        }
                        if ((temp == sb.length()) && (temp == 6)) {
                            flag = 1;
                        }
                        else {
                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                            cin >> sb;
                        }
                    }
                    s1 = sa + " " + sch + " " + sb;
                    cout << endl;
                    for (int i = 0; i < clients.size(); i++) {
                        if (clients[i].num == s1) {
                            printClientInfo(&clients[i]);
                        }
                    }
                    break;
                }
                case 5: {
                    printClientList(&clients);
                    cout << "\nTask completed successfully." << endl;
                    break;
                }
                case 6: {
                    clients = loadClientsFromFile();
                    cout << "\nTask completed successfully." << endl;
                    break;
                }
                case 7: {
                    saveClientsInFile(clients);
                    cout << "\nTask completed successfully." << endl;
                    break;
                }
                case 9: {
                    cout << "Please, press any key to continue." << endl;
                    _getch();
                    system("cls");
                    Menu(cars, clients, rents);
                }
                case 0: {
                    return 0;
                }
                }
            }
        }
        case 2: {
            while (n != 0) {
                cout << "Please, press any key to continue." << endl;
                _getch();
                system("cls");

                Carshelp();
                cin >> n;
                while (cin.fail() || cin.get() != '\n') {
                    cin.clear();
                    cin.ignore(cin.rdbuf()->in_avail());
                    cout << "Sorry, wrong input, please try again.";
                    cin >> n;
                }
                switch (n) {
                case 1: {
                    Caradd(&cars);
                    break;
                }
                case 2: {
                    Caredit(&cars, &rents);
                    break;
                }
                case 3: {
                    Cardelete(&cars, &rents);
                    break;
                }
                case 4: {
                    cout << "Please, enter your driver's license number." << endl;
                    cout << "Please, enter numbers of your license number: (input format - NNNNN) ";
                    cin >> sa;
                    flag = 0;
                    while (flag == 0) {
                        temp = 0;
                        for (i = 0; i < sa.length(); i++) {
                            if ((int(sa[i]) > 47) && (int(sa[i]) < 58)) {
                                temp++;
                            }
                        }
                        if ((temp == sa.length()) && (temp == 5)) {
                            flag = 1;
                        }
                        else {
                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                            cin >> sa;
                        }
                    }
                    cout << "Please, enter letters of your license number: (input format - AAA) ";
                    cin >> sch;
                    flag = 0;
                    while (flag == 0) {
                        temp = 0;
                        for (i = 0; i < sch.length(); i++) {
                            if ((int(sch[i]) == 65) || (int(sch[i]) == 66)) {
                                temp++;
                            }
                        }
                        if ((temp == sch.length()) && (temp == 3)) {
                            flag = 1;
                        }
                        else {
                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                            cin >> sch;
                        }
                    }

                    s1 = sch + " " + sa;
                    for (i = 1; i < 3; i++) {
                        stemp1 += sch[i];
                    }
                    for (i = 0; i < 3; i++) {
                        stemp2 += sa[i];
                    }
                    j = 0;
                    for (i = 4; i < 6; i++) {
                        s1[i] = stemp1[j];
                        j++;
                    }
                    j = 0;
                    for (i = 1; i < 4; i++) {
                        s1[i] = stemp2[j];
                        j++;
                    }
                    for (i = 0; i < s1.length(); i++) {
                        if (i == 6) {
                            s1[i] = '-';
                        }
                    }
                    cout << endl;
                    for (int i = 0; i < cars.size(); i++) {
                        if (cars[i].num == s1) {
                            printCarInfo(&cars[i]);
                        }
                    }
                    break;
                }
                case 5: {
                    printCarList(&cars);
                    cout << "\nTask completed successfully." << endl;
                    break;
                }
                case 6: {
                    cars = loadCarsFromFile();
                    cout << "\nTask completed successfully." << endl;
                    break;
                }
                case 7: {
                    saveCarsInFile(cars);
                    cout << "\nTask completed successfully." << endl;
                    break;
                }
                case 8: {
                    cout << "Please, enter your car brand." << endl;
                    cin >> s2;
                    flag = 0;
                    while (flag == 0) {
                        temp = 0;
                        for (i = 0; i < s2.length(); i++) {
                            if ((int(s2[i]) > 47) && (int(s2[i]) < 58)) {
                                temp++;
                            }
                        }
                        if (temp > 0) {
                            cout << "Sorry, wrong input. Try one more time, please." << endl;
                            cin >> s2;
                        }
                        else {
                            flag = 1;
                        }
                    }
                    cout << endl;
                    for (int i = 0; i < cars.size(); i++) {
                        if (cars[i].br == s2) {
                            printCarInfo(&cars[i]);
                        }
                    }
                    break;
                }
                case 9: {
                    cout << "Please, press any key to continue." << endl;
                    _getch();
                    system("cls");
                    Menu(cars, clients, rents);
                }
                case 0: {
                    return 0;
                }
                }
            }
        }
        case 3: {
            while (n != 0) {
                cout << "Please, press any key to continue." << endl;
                _getch();
                system("cls");

                Renthelp();
                cin >> n;
                while (cin.fail() || cin.get() != '\n') {
                    cin.clear();
                    cin.ignore(cin.rdbuf()->in_avail());
                    cout << "Sorry, wrong input, please try again.";
                    cin >> n;
                }
                switch (n) {
                case 1: {
                    CarforRep(cars, &rents);
                    break;
                }
                case 2: {
                    CarfromRep(cars, &rents);
                    break;
                }
                case 3: {
                    CartoClient(cars, clients, &rents);
                    break;
                }
                case 4: {
                    CarfromClient(&cars, clients, &rents);
                    break;
                }
                case 5: {
                    saveRentsInFile(rents);
                    break;
                }
                case 9: {
                    cout << "Please, press any key to continue." << endl;
                    _getch();
                    system("cls");
                    Menu(cars, clients, rents);
                }
                case 0: {
                    return 0;
                }
                }
            }
        }
        case 0: {
            return 0;
        }
        }
    }
}

//--------------------------------------------

int main()
{
    //setlocate(LC_ALL, "Russian");
    cout << "Conventions:\nN - number (0-9)\nA - letter (A, B)" << endl;
    cout << endl;

    vector<client> clients = loadClientsFromFile();
    vector<car> cars = loadCarsFromFile();
    vector<rent> rents = loadRentsFromFile();

    Clientcheck(clients);
    if (Clientcheck(clients) == 1) {
        cout << "Error in CLIENTS file!" << endl;
        return 1;
    }
    else {
        //cout << "File is Ok." << endl;
    }

    Carcheck(cars);
    if (Carcheck(cars) == 1) {
        cout << "Error in CARS file!" << endl;
        return 1;
    }
    else {
        //cout << "File is Ok." << endl;
    }
    Rentcheck(cars, clients, rents);
    if (Rentcheck(cars, clients, rents) == 1) {
        cout << "Error in RENTS file!" << endl;
        return 1;
    }
    else {
        //cout << "File is Ok." << endl;
    }

    Rentcheck2(cars, clients, rents);
    if (Rentcheck2(cars, clients, rents) == 1) {
        cout << "Error in RENTS file!" << endl;
        return 1;
    }
    else {
        //cout << "File is Ok." << endl;
    }

    int m;
    string sss, fff, sa, sb, s1, sch, s2, stemp1, stemp2;

    string* a = new string[clients.size()];
    string* b = new string[clients.size()];
    fff = "";
    for (int i = 0; i < clients.size(); i++) {
        sss = serializeClientToString(&clients[i]);
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
    for (int i = 0; i < clients.size(); i++) {
        for (int j = i + 1; j < clients.size(); j++) {
            if (a[i] == a[j]) {
                b[i] = a[i];
                //cout << "Совпадение ФИО в файле!" << endl;
                delIndexByNum(b[i], &clients);
                break;
            }
        }
    }

    string* c = new string[cars.size()];
    string* d = new string[cars.size()];
    fff = "";
    for (int i = 0; i < cars.size(); i++) {
        sss = serializeCarToString(&cars[i]);
        for (int i = 0; i < sss.length(); i++) {
            if (sss[i] == ';') {
                break;
            }
            else {
                fff += sss[i];
            }
        }
        c[i] = fff;
        fff = "";
    }
    for (int i = 0; i < cars.size(); i++) {
        for (int j = i + 1; j < cars.size(); j++) {
            if (c[i] == c[j]) {
                d[i] = c[i];
                //cout << "Совпадение ФИО в файле!" << endl;
                delIndexByNum(d[i], &cars);
                break;
            }
        }
    }

    m = -1;
    int n = -1;
    int k = 0;
    while (k == 0) {
        if (Menu(cars, clients, rents) == 0) {
            k++;
        }
        else {
            Menu(cars, clients, rents);
        }
    }

    return 0;
}
