#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

// Структура для представления одной команды машины Тьюринга
struct Command {
    string current_state;
    char read_symbol;
    string next_state;
    char write_symbol;
    char move_direction;
    string smth;
};

int main() {
    setlocale(LC_ALL, "Russian");
    // Чтение входных данных из файла input.txt
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Не удалось открыть файл input.txt!" << endl;
        return 1;
    }

    string tape;
    getline(input_file, tape);
    input_file.close();

    // Чтение алфавита из файла alphabet.txt
    ifstream alphabet_file("alphabet.txt");
    if (!alphabet_file.is_open()) {
        cerr << "Не удалось открыть файл alphabet.txt!" << endl;
        return 1;
    }

    vector<char> alphabet;
    string line;
    while (getline(alphabet_file, line)) {
        for (char c : line) {
            if (c != ' ') {
                alphabet.push_back(c);
            }
        }
    }
    alphabet_file.close();

    // Проверка наличия всех необходимых символов в алфавите
    bool valid_tape = true;
    for (char c : tape) {
        if (find(alphabet.begin(), alphabet.end(), c) == alphabet.end()) {
            cerr << "Символ '" << c << "' не найден в алфавите." << endl;
            valid_tape = false;
        }
    }
    if (!valid_tape) {
        return 1;
    }

    // Чтение команд из файла commands.txt
    ifstream commands_file("commands.txt");
    if (!commands_file.is_open()) {
        cerr << "Не удалось открыть файл commands.txt!" << endl;
        return 1;
    }

    map<string, map<char, Command>> transition_table;
    while (getline(commands_file, line)) {
        istringstream iss(line);

        string state, symbol, smth, new_state, write, direction;
        iss >> state >> symbol >> smth >> new_state >> write >> direction;

        Command command{ state, symbol[0], new_state, write[0], direction[0], smth };  // Передали значение smth
        transition_table[state][symbol[0]] = command;
    }
    commands_file.close();

    // Выполнение программы машины Тьюринга
    int head_position = 0;
    string current_state = "q0";
    ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        cerr << "Не удалось создать файл output.txt!" << endl;
        return 1;
    }

    while (current_state != "!") {
        // Выводим текущее состояние ленты и положение головки
        output_file << tape << endl;
        output_file << setw(head_position + 1) << '^' << endl;

        // Получаем текущую команду
        auto it = transition_table.find(current_state);
        if (it == transition_table.end()) {
            cerr << "Нет перехода для состояния " << current_state << endl;
            break;
        }

        auto command_it = it->second.find(tape[head_position]);
        if (command_it == it->second.end()) {
            cerr << "Нет команды для символа " << tape[head_position] << " в состоянии " << current_state << endl;
            break;
        }

        const Command& command = command_it->second;
        output_file << command.current_state << " " << command.read_symbol << " " << command.smth << " "
            << command.next_state << " " << command.write_symbol << " " << command.move_direction << endl;

        // Обновляем ленту и головку
        tape[head_position] = command.write_symbol;

        // Реализуем движение головки
        if (command.move_direction == '>') {
            if (head_position == tape.size() - 1) { // Если достигли конца ленты
                tape += "_";                        // Добавляем "_" справа
            }
            head_position++;                         // Двигаем голову вправо
        }
        else if (command.move_direction == '<') {
            if (head_position == 0) {                // Если достигли начала ленты
                tape.insert(0, 1, '_');              // Добавляем "_" слева
                head_position = 0;                   // Сдвигаемся на одну позицию вправо
            }
            else {
                head_position--;                     // Двигаем голову влево
            }
        }

        // Переходим в новое состояние
        current_state = command.next_state;
    }

    output_file.close();
    cout << "Результат выполнения программы записан в файл output.txt" << endl;
    return 0;
}