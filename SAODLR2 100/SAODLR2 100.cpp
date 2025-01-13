#include <iostream>

using namespace std;

struct node {
    int val;
    node* next;
};

class List {
    node* Head, * Tail;
public:
    List() {
        Head = NULL;
        Tail = NULL;
    }

    ~List() {
        while (Head != NULL) {
            node* temp = Head->next;
            delete Head;
            Head = temp;
            Tail->next = temp;
        }
    }

    void insert(int x, int pos) {
        if (pos == 1) {
            node* temp = new node;
            temp->val = x;
            temp->next = Head;
            Head = temp;
        }
        else {
            node* temp = new node;
            temp->val = x;
            if (Head == NULL) {
                Head = temp;
                Tail->next = temp;
            }
            else {
                node* tempNew = Head;
                int count = 1;
                while (tempNew->next != NULL && count < pos - 1) {
                    tempNew = tempNew->next;
                    count++;
                }
                node* tempNew2 = tempNew->next;
                tempNew->next = temp;
                temp->next = tempNew2;
            }
        }
    }

    void del(int pos) {
        node* temp = Head;
        if (pos == 1) {
            Head = Head->next;
            Tail->next = Head;
            delete temp;
        }
        else {
            node* del1;
            int count = 1;
            while ((Head != NULL) && (count < pos - 1)) {
                temp = temp->next;
                count++;
            }
            del1 = temp->next;
            temp->next = del1->next;
            delete del1;
        }
    }
    void print() {
        node* temp = Head;
        while (temp != NULL) {
            cout << temp->val << " ";
            temp = temp->next;
        }
    }
    int call(int pos) {
        int e, count;
        node* temp = new node;
        temp = Head;
        count = 1;
        while (count < pos) {
            temp = temp->next;
            count++;
        }
        e = temp->val;
        return e;
    }
};
void Equal(List& flist, List& slist, int n, int m) {
    int ftemp, stemp, i;
    ftemp = 0;
    stemp = 0;
    for (i = 0; i < n; i++) {
        ftemp += flist.call(i + 1);
    }
    for (i = 0; i < m; i++) {
        stemp += slist.call(i + 1);
    }
    if (ftemp > stemp) {
        cout << "Первый больше" << endl;
    }
    else {
        cout << "Второй больше" << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");

    List mylist, yourlist;
    int n, m, a, b, k, t, i, koef, ftemp, stemp;
    ftemp = 0;
    stemp = 0;
    cout << "Введите количество членов для первого многочлена: ";
    cin >> n;
    cout << "Введите количество членов для второго многочлена: ";
    cin >> t;
    cout << "Введите коэффициент многочлена: ";
    cin >> koef;
    cout << "Вводите элементы с первого для первого: ";
    for (i = 0; i < n; i++) {
        cin >> k;
        mylist.insert(k*pow(koef, n - 1 - i), i + 1);
    }
    cout << "Вводите элементы с первого для второго: ";
    for (i = 0; i < t; i++) {
        cin >> k;
        yourlist.insert(k * pow(koef, t - 1 - i), i + 1);
    }
    mylist.print();
    cout << endl;
    yourlist.print();
    cout << endl;
    Equal(mylist, yourlist, n, t);
    
    //tolko1spisok
    cout << "Если хотите добавить элемент, нажмите 1.\nЕсли хотите удалить элемент, нажмите 2.\nЕсли ничего не хотите, нажмите 0.\n";
    cin >> m;
    if ((m != 1) && (m != 2) && (m != 0)) {
        cout << "Error" << endl;
    }
    if (m == 1) {
        //dlyamnochhlenarabotaetkrivonorabotaet
        cout << "Введите значение элемента: ";
        cin >> a;
        cout << "Введите позицию элемента: ";
        cin >> b;
        mylist.insert(a*pow(koef, n - 1 - b), b);
    }
    if (m == 2) {
        cout << "Введите номер элемента: ";
        cin >> b;
        mylist.del(b);
    }
    if (m == 0) {
        cout << "Thanks" << endl;
    }

    mylist.print();
    cout << endl;
    cout << endl;
    Equal(mylist, yourlist, n, t);

    return 0;
}
