#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct nodeptr
{
    int key;
    char height;
    nodeptr* left;
    nodeptr* right;
    nodeptr(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

char height(nodeptr* p) {
    return p ? p->height : 0;
}

int balancefact(nodeptr* p) {
    return height(p->right) - height(p->left);
}

void balanceheight(nodeptr* p) {
    char hr = height(p->right);
    char hl = height(p->left);
    p->height = (hr > hl ? hr : hl) + 1;
}

// правый поворот вокруг p
nodeptr* rotateright(nodeptr* p)
{
    nodeptr* q = p->left;
    p->left = q->right;
    q->right = p;
    balanceheight(p);
    balanceheight(q);
    return q;
}

// левый поворот вокруг q
nodeptr* rotateleft(nodeptr* q)
{
    nodeptr* p = q->right;
    q->right = p->left;
    p->left = q;
    balanceheight(q);
    balanceheight(p);
    return p;
}

// балансировка узла p
nodeptr* balance(nodeptr* p)
{
    balanceheight(p);
    if (balancefact(p) == -2)
    {
        if (balancefact(p->left) > 0) {
            p->left = rotateleft(p->left);
            cout << "Сделан большой правый поворот" << endl;
        }
        return rotateright(p);
    }
    if (balancefact(p) == 2)
    {
        if (balancefact(p->right) < 0) {
            p->right = rotateright(p->right);
            cout << "Сделан большой левый поворот" << endl;
        }
        return rotateleft(p);
    }
    return p;
}

nodeptr* insert(nodeptr* p, int k)
{
    if (!p) {
        return new nodeptr(k);
    }
    if (k < p->key)
        p->left = insert(p->left, k);
    else if (k > p->key)
        p->right = insert(p->right, k);
    return balance(p);
}

void find_elem(nodeptr* p, int key, int go = 0) {
    if (!p) {
        cout << "Дерево пустое или такого элемента нет" << endl;
        return;
    }
    else if (p->key == key) {
        cout << "Элемент " << p->key << " найден за " << go << " шагов" << endl;
    }
    go++;
    if (p->key < key) {
        find_elem(p->right, key, go);
    }
    else {
        find_elem(p->left, key, go);
    }
}

int calc_height(nodeptr* p, int key, int go = 0) {
    if (!p) {
        return 0;
    }
    else if (p->key == key) {
        return go;
    }
    go++;
    if (p->key < key) {
        calc_height(p->right, key, go);
    }
    else {
        calc_height(p->left, key, go);
    }
}

nodeptr* findMin(nodeptr* p)
{
    if (!p)
        return NULL;
    else if (p->left == NULL)
        return p;
    else
        return findMin(p->left);
}

nodeptr* removeMin(nodeptr* p)
{
    if (p->left == nullptr)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

nodeptr* removeMax(nodeptr* p)
{
    if (p->right == nullptr)
        return p->left;
    p->right = removeMax(p->right);
    return balance(p);
}

nodeptr* remove(nodeptr* p, int k)
{
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else
    {
        nodeptr* q = p->left;
        nodeptr* r = p->right;
        delete p;
        if (!r)
            return q;
        nodeptr* min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

//Прямой обход дерева
void PreOpder(nodeptr* p, vector <int>& pr) {
    if (!p) {
        return;
    }
    pr.push_back(p->key);
    PreOpder(p->left, pr);
    PreOpder(p->right, pr);
}

struct Trunk
{
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

void showTrunks(Trunk* p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

void printTree(nodeptr* root, Trunk* prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->key << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}

void count_list(nodeptr* p, int& count_lists_p) {
    if (!p) {
        return;
    }
    if (p->left == nullptr && p->right == nullptr) {
        count_lists_p += 1;
    }
    count_list(p->left, count_lists_p);
    count_list(p->right, count_lists_p);
}

void fortask1(nodeptr* p, int& mx, nodeptr* p_d) {
    if (p->left || p->right) {
        if (p->left)
            fortask1(p->left, mx, p_d);
        if (p->right)
            fortask1(p->right, mx, p_d);
    }
    else {
        if (mx != calc_height(p_d, p->key)) {
            mx = max(calc_height(p_d, p->key), mx);
        }
    }
}

void fortask2(nodeptr* p, int& mx, nodeptr* p_d) {
    if (p->left || p->right) {
        if (p->left)
            if (!p->left && !p->right) {
                mx = calc_height(p_d, p->key);
            }
            else {
                fortask1(p->left, mx, p_d);
            }
        if (p->right)
            if (!p->left && !p->right) {
                mx = calc_height(p_d, p->key);
            }
            else {
                fortask1(p->left, mx, p_d);
            }
    }
}

void task(nodeptr* p) {
    int max_height = -1, count_lists = 0, min_height = -1;
    nodeptr* p_d = p;
    fortask1(p, max_height, p_d);
    fortask2(p, min_height, p_d);
    int tmp1 = max_height;
    int tmp2 = min_height;
    cout << "Высота самого верхнего листа = " << max_height << endl;
    cout << "Высота самого нижнего листа = " << min_height << endl;
    while (tmp1 != tmp2) {
        removeMax(p_d);
        max_height = -1;
        fortask1(p, max_height, p_d);
        if (tmp1 != max_height) {
            tmp1--;
        }
        printTree(p, nullptr, false);
        cout << endl;
    }
}

int main()
{
    setlocale(0, "");
    nodeptr* p = nullptr;
    for (;;) {
        cout << endl;
        cout << "1, Добавить элемент.\n";
        cout << "2, Вывести дерево.\n";
        cout << "3, Удалить элемент.\n";
        cout << "4, Найти элемент.\n";
        cout << "5, Прямой обход.\n";
        cout << "6, Основное задание варианта.\n";
        cout << "0, Выйти.\n";
        cout << endl;
        cout << "Выбирайте: ";
        int choise;
        cin >> choise;
        cout << endl;
        switch (choise) {
        case 1: {
            cout << "Введите число, котороые хотите добавить - ";
            int k;
            cin >> k;
            p = insert(p, k);
            break;
        }
        case 2: {
            printTree(p, nullptr, false);
            break;
        }
        case 3: {
            cout << "Введите элемент, который хотите удалить - ";
            int k;
            cin >> k;
            p = remove(p, k);
            break;
        }
        case 4: {
            int k;
            cout << "Введите элемент, который хотите найти - ";
            cin >> k;
            find_elem(p, k, 0);
            break;
        }
        case 5: {
            vector <int> pr;
            PreOpder(p, pr);
            for (int i = 0; i < pr.size(); i++) {
                cout << pr[i] << "\t";
            }
            break;
        }
        case 6: {
            task(p);
            printTree(p, nullptr, false);
            break;
        }
        case 0: {
            return 0;
        }
        }

    }

}