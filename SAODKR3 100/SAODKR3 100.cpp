#include <iostream>
#include <string>
#include <iomanip>

#define MAXOCH 10
#define MAXST 5
#define TL 10

using namespace std;

struct Task {
    string name = "";
    int priority = 0;
    int durationTime = 0;
    int startTime = 0;
};

int add_task_list(Task* lst) {
    int count;
    cout << "Введите количество задач" << endl;
    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << "Введите имя задачи - ";
        cin >> lst[i].name;
        cout << "Введите время начала входа задачи - ";
        cin >> lst[i].startTime;
        cout << "Введите время обработки задачи - ";
        cin >> lst[i].durationTime;
        cout << "Введите приоритет задачи - ";
        cin >> lst[i].priority;
    }
    return count;
}

void work_Proc(Task* Proc) {
    if (Proc->durationTime <= 0) {
        Proc->name = "";
    }
    else
        Proc->durationTime = Proc->durationTime - 1;
}

void displacement(Task* Ocher) {

    for (int i = 0; i < MAXOCH; i++) {
        if (i != MAXOCH - 1)
            Ocher[i] = Ocher[i + 1];
        else
            Ocher[MAXOCH - 1].name = "";
    }
}

void displacement_st(Task* Stack) {

    for (int i = 0; i < MAXST; i++) {
        if (i != MAXST - 1)
            Stack[i] = Stack[i + 1];
        else
            Stack[MAXST - 1].name = "";
    }
}

void displacement_task_list(Task* List) {
    for (int i = 0; i < TL; i++) {
        if (i != TL - 1)
            List[i] = List[i + 1];
        else
            List[TL - 1].name = "";
    }
}

void Stack_add(Task* Stack, Task Proc) {
    bool res = false;
    for (int k = 0; k < MAXST; k++) {
        if (Stack[k].name == "") {
            for (int j = k + 1; j > 0; j--) {
                Stack[j] = Stack[j - 1];
            }
            Stack[0] = Proc;
            res = true;
            break;
        }
    }
    if (res == false) {
        cout << "Стек переполнен!" << endl;
    }
}

bool check_for_emptiness(Task* Ocher) {
    bool tracker = true;
    for (int i = 0; i < MAXOCH; i++) {
        if (Ocher[i].name != "")
            tracker = false;
    }
    return tracker;
}

void print_stack(Task* Stack) {
    cout << "Стэк:" << endl;
    for (int i = 0; i < MAXST; i++) {
        if (Stack[i].name != "")
            cout << "Задача " << Stack[i].name << " с приоритетом " << Stack[i].priority << ". Осталось " << Stack[i].durationTime << " тактов" << endl;
    }
}

void print_ocher(Task* Ocher) {
    for (int i = 0; i < MAXOCH; i++) {
        if (Ocher[i].name != "") {
            cout << "Задача " << Ocher[i].name << " с приоритетом " << Ocher[i].priority << ". Осталось " << Ocher[i].durationTime << " тактов" << endl;
        }
    }
}

void print_proc(Task* Proc) {
    cout << "Работа процессоров" << endl;
    if (Proc->name != "") {
        cout << "Задача " << Proc->name << " с приоритетом " << Proc->priority << ". Осталось " << Proc->durationTime << " тактов" << endl;
    }
}

bool check1(Task* Proc, Task* Och1, Task* Och2, Task* Och3, Task* Stack, Task* TaskList) {
    if (Och1[0].name == "" && Och2[0].name == "" && Och3[0].name == "" && Stack[0].name == "" && TaskList[0].name == "" && Proc->name == "")
        return false;
    else
        return true;

}


int main()
{
    setlocale(LC_ALL, "Rus");
    Task F0[MAXOCH];
    Task F1[MAXOCH];
    Task F2[MAXOCH];
    int iOch = 0;
    Task Stack[MAXST];
    int iSt = 0;
    Task TaskList[TL];
    Task Proc;
    add_task_list(TaskList);
    int timer = 0;


    while (check1(&Proc, F0, F1, F2, Stack, TaskList)) {
        timer++;
        cout << "Идет " << timer << " такт" << endl;
        work_Proc(&Proc);
        if (timer == TaskList[0].startTime) {
            for (int j = 0; j < MAXOCH; j++) {
                if (F0[j].name == "") {
                    F0[j] = TaskList[0];
                    displacement_task_list(TaskList);
                }
                break;
            }
        }
        if (timer == TaskList[0].startTime) {
            for (int j = 0; j < MAXOCH; j++) {
                if (F1[j].name == "") {
                    F1[j] = TaskList[0];
                    displacement_task_list(TaskList);
                }
                break;
            }
        }
        if (timer == TaskList[0].startTime) {
            for (int j = 0; j < MAXOCH; j++) {
                if (F2[j].name == "") {
                    F2[j] = TaskList[0];
                    displacement_task_list(TaskList);
                }
                break;
            }
        }
        if (timer == TaskList[0].startTime) {
            for (int j = 0; j < MAXOCH; j++) {
                if (Stack[j].name == "") {
                    Stack[j] = TaskList[0];
                    displacement_task_list(TaskList);
                    //break;
                }
                break;
            }
        }

        if (Proc.durationTime <= 0) {
            if (F0[0].name != "") {
                Proc = F0[0];
                displacement(F0);
            }
        }
        if (Proc.durationTime <= 0) {
            if (F1[0].name != "") {
                Proc = F1[0];
                displacement(F1);
            }
        }
        if (Proc.durationTime <= 0) {
            if (F2[0].name != "") {
                Proc = F2[0];
                displacement(F2);
            }
        }

        switch (Stack[0].priority) {
        case 1:
            if (check_for_emptiness(F0)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            if (check_for_emptiness(F1)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            else {
                Proc = Stack[0];
                Stack[0] = F1[0];
                displacement(F1);
            }
            break;
        case 2:
            if (check_for_emptiness(F0)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            if (check_for_emptiness(F1)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            if (check_for_emptiness(F2)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            else {
                Proc = Stack[0];
                Stack[0] = F2[0];
                displacement(F2);
            }
            break;
        case 3:
            if (check_for_emptiness(F0)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            if (check_for_emptiness(F1)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            if (check_for_emptiness(F2)) {
                Proc = Stack[0];
                displacement_st(Stack);
            }
            break;
        default:
            cout << "Стек пустой" << endl;
        }

        if (F0[0].name != "") {
            cout << "Очередь 1: ";
            print_ocher(F0);
            cout << "\n";
        }
        if (F1[0].name != "") {
            cout << "Очередь 2: ";
            print_ocher(F1);
            cout << "\n";
        }
        if (F2[0].name != "") {
            cout << "Очередь 3: ";
            print_ocher(F2);
            cout << "\n";
        }
        if (Proc.name != "") {
            cout << "Процессор" << endl;
            print_proc(&Proc);
            cout << "\n";
        }
        if (Stack[0].name != "") {
            print_stack(Stack);
            cout << "\n";
        }

    }

}