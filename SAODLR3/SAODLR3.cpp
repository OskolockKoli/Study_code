#include <iostream>
#define MAXOCH 10
#define MAXST 1
#define TL 10

using namespace std;

struct Task {
	string name = "";
	int priority = 0;
	int type = 0;
	int durationTime = 0;
	int startTime = 0;
};

void add_task_list(Task* lst) {
	int count;
	cout << "Введите количество задач" << endl;
	cin >> count;
	for (int i = 0; i < count; i++) {
		cout << "Введите имя задача - ";
		cin >> lst[i].name;
		cout << "Введите тип задача (0-2)";
		cin >> lst[i].type;
		cout << "Введите время начала входа задача - ";
		cin >> lst[i].startTime;
		cout << "Введите время обработки задача - ";
		cin >> lst[i].durationTime;
		cout << "Введите приоритет задачи - ";
		cin >> lst[i].priority;
	}
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

bool Stack_add(Task* Stack, Task Proc) {
	bool res = false;
	for (int k = 0; k < MAXST; k++) {
		if (Stack[k].name == "") {
			for (int j = k; j > 0; j--) {
				Stack[j] = Stack[j - 1];
			}
			Stack[0] = Proc;
			res = true;
			break;
		}

	}
	if (res == false) {
		cout << "Стэк переполнен" << endl;
	}
	return res;
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
			cout << "Задача " << Stack[i].name << " типа " << Stack[i].type << " и приоритетом " << Stack[i].priority << ". Осталось " << Stack[i].durationTime << "тактов" << endl;
	}
}

void print_ocher(Task* Ocher) {
	cout << "Очередь:" << endl;
	for (int i = 0; i < MAXOCH; i++) {
		if (Ocher[i].name != "") {
			cout << "Задача " << Ocher[i].name << " типа " << Ocher[i].type << " и приоритетом " << Ocher[i].priority << ". Осталось " << Ocher[i].durationTime << "тактов" << endl;
		}
	}
}

void print_proc(Task* Proc) {
	cout << "Работа процессоров" << endl;
	if (Proc->name != "") {
		cout << "Задача " << Proc->name << " типа " << Proc->type << " и приоритетом " << Proc->priority << ". Осталось " << Proc->durationTime << "тактов" << endl;
	}
}

bool check1(Task* Proc, Task* Proc1, Task* Proc2, Task* Och, Task* Stack, Task* TaskList) {
	if (Och[0].name == "" && Stack[0].name == "" && TaskList[0].name == "" && Proc->name == "" && Proc1->name == "" && Proc2->name == "")
		return false;
	else
		return true;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	Task Ocher[MAXOCH];
	int iOch = 0;
	Task Stack[MAXST];
	int iSt = 0;
	Task TaskList[TL];
	Task Proc0, Proc1, Proc2;
	add_task_list(TaskList);
	int timer = 0;


	while (check1(&Proc0, &Proc1, &Proc2, Ocher, Stack, TaskList)) {
		timer++;
		cout << "Идет " << timer << " такт" << endl;
		work_Proc(&Proc0);
		work_Proc(&Proc1);
		work_Proc(&Proc2);
		if (timer == TaskList[0].startTime) {
			for (int j = 0; j < MAXOCH; j++) {
				if (Ocher[j].name == "") {
					Ocher[j] = TaskList[0];
					displacement_task_list(TaskList);
				}
				break;
			}
		}

		bool cheker = true;
		switch (Ocher[0].type) {
		case 0:
			if (Proc0.durationTime <= 0) {
				Proc0 = Ocher[0];
			}
			else {
				if
					(Proc0.priority < Ocher[0].priority) {
					if (Stack_add(Stack, Proc0) == false) {
						cheker = false;
						break;
					}
					Proc0 = Ocher[0];
				}
				else {
					if (Stack_add(Stack, Ocher[0]) == false) {
						cheker = false;
						break;
					}
				}
			}
			displacement(Ocher);
			break;
		case 1:
			if (Proc1.durationTime <= 0) {
				Proc1 = Ocher[0];
			}
			else {
				if (Proc1.priority < Ocher[0].priority) {
					if (Stack_add(Stack, Proc1) == false) {
						cheker = false;
						break;
					}
					Proc1 = Ocher[0];
				}
				else {
					if (Stack_add(Stack, Ocher[0]) == false) {
						cheker = false;
						break;
					}
				}
			}
			displacement(Ocher);
			break;
		case 2:
			if (Proc2.durationTime <= 0) {
				Proc2 = Ocher[0];

			}
			else {
				if (Proc2.priority < Ocher[0].priority) {
					if (Stack_add(Stack, Proc2) == false) {
						cheker = false;
						break;
					}
					Proc2 = Ocher[0];

				}
				else {
					if (Stack_add(Stack, Ocher[0]) == false) {
						cheker = false;
						break;
					}
				}
			}
			displacement(Ocher);
			break;
		}

		if (cheker == false) {
			cout << "Стэк переполнен" << endl;
			break;
		}
		if (check_for_emptiness(Ocher)) {
			switch (Stack[0].type) {
			case 0:
				if (Proc0.durationTime <= 0) {
					Proc0 = Stack[0];
					displacement_st(Stack);
				}
				break;
			case 1:
				if (Proc1.durationTime <= 0) {
					Proc1 = Stack[0];
					displacement_st(Stack);
				}
				break;
			case 2:
				if (Proc2.durationTime <= 0) {
					Proc2 = Stack[0];
					displacement_st(Stack);
				}
				break;
			}
		}
		if (Ocher[0].name != "") {
			print_ocher(Ocher);
			cout << "\n\n";
		}
		if (Proc0.name != "") {
			cout << "Процессор #1" << endl;
			print_proc(&Proc0);
			cout << "\n\n";
		}
		if (Proc1.name != "") {
			cout << "Процессор #2" << endl;
			print_proc(&Proc1);
			cout << "\n\n";
		}
		if (Proc2.name != "") {
			cout << "Процессор #3" << endl;
			print_proc(&Proc2);
			cout << "\n\n";
		}
		if (Stack[0].name != "") {
			print_stack(Stack);
			cout << "\n\n";
		}

	}

}
