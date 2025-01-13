#include <iostream>

using namespace std;

struct B1 {
    string data;
    B1() : data("B1") {}

    explicit B1(const string& data) : data(data + "::B1") {}

    virtual void show() {
        cout << data << ".show()" << endl;
    }
};

struct B2 {
    string data;

    B2() : data("B2") {}

    explicit B2(const string& data) : data(data + "::B2") {}

    virtual void show() {
        cout << data << ".show()" << endl;
    }
};

struct D1 : public B1 {
    explicit D1(const string& data) : B1(data + "::D1") {}

    D1() : B1("D1") {
        B1::show();
    }

    void show() override {
        B1::show();
    }
};

struct D2 : private B2, private D1 {
    explicit D2(const string& data) : B2(data + "::D2"), D1(data + "::D2") {}

    D2() : B2("D2"), D1("D2") {
        D1::show();
        B2::show();
    }

    // поскольку в этом задании нет виртуального наследования,
    // возникает два метода с одинаковым именем и надо решить, какой вызвать
    // показано, как вызывать оба, соответственно, строки вывода будут дублироваться
    void show() override {
        D1::show();
        B2::show();
    }
};

struct D3 : public D2 {
    D3() : D2("D3") {
        D2::show();
    }

    void show() override {
        D2::show();
    }
};

int main() {

    system("color F0");
    setlocale(0, "Rus");

    B1 b1;
    B2 b2;
    D1 d1;
    D2 d2;
    D3 d3;

    b1.show();
    b2.show();
    d1.show();
    d2.show();
    d3.show();

    return 0;
}