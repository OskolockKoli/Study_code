#include <iostream>
#include <list>
#include <iterator>

using namespace std;

int r(int min, int max)
{
    int num = min + rand() % (max - min + 1);
    return num;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    list <int> mylist = {};
    list <int> mirlist = {};
    list <int> diflist = {};
    list <int> ::iterator it1;
    it1 = mylist.begin();
    int n, m, a, b, count;
    count = 0;
    cout << "Введите количество элементов: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        mylist.insert(it1, r(-100, 100));
    }
    copy(mylist.begin(), mylist.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "Если хотите добавить элемент, нажмите 1.\nЕсли хотите удалить элемент, нажмите 2.\nЕсли ничего не хотите, нажмите 0.\n";
    cin >> m;
    if ((m != 1) && (m != 2) && (m != 0)) {
        cout << "Error" << endl;
    }
    if (m == 1) {
        cout << "Введите значение элемента: ";
        cin >> a;
        cout << "Введите номер элемента: ";
        cin >> b;
        it1 = mylist.begin();
        advance(it1, b - 1);
        mylist.insert(it1, a);
        count++;
    }
    if (m == 2) {
        cout << "Введите номер элемента: ";
        cin >> b;
        it1 = mylist.begin();
        advance(it1, b - 1);
        mylist.erase(it1);
        count--;
    }
    if (m == 0) {
        cout << "Thanks" << endl;
    }
    copy(mylist.begin(), mylist.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    copy(mylist.begin(), mylist.end(), front_inserter(mirlist));
    copy(mirlist.begin(), mirlist.end(), ostream_iterator<int>(cout, " "));
    it1 = diflist.begin();
    for (int i = 0; i < n + count; i++) {
        diflist.insert(it1, mylist.front() - mirlist.front());
        mylist.pop_front();
        mirlist.pop_front();
    }
    cout << endl;
    copy(diflist.begin(), diflist.end(), ostream_iterator<int>(cout, " "));

    return 0;
}
