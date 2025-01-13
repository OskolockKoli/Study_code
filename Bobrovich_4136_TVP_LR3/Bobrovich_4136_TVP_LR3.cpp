#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для проверки принадлежности символа к алфавиту
bool isInAlphabet(const char c, const vector<char>& alphabet) {
    return find(alphabet.begin(), alphabet.end(), c) != alphabet.end();
}

// Функция для проверки принадлежности переменной к множеству переменных
bool isInVariables(const string& var, const vector<string>& variables) {
    return find(variables.begin(), variables.end(), var) != variables.end();
}

// Основная функция для эмуляции вычислений
void emulate(const vector<char>& alphabet, const vector<string>& variables, const vector<string>& rules, const string& input, ofstream& outputFile) {
    // Проверка правильности входной строки
    bool validInput = true;
    for (char c : input) {
        if (!isInAlphabet(c, alphabet)) {
            cout << "Ошибка: найден символ не входящий в алфавит." << endl;
            validInput = false;
            break;
        }
    }

    if (!validInput) {
        return;
    }

    // Эмуляция вычислений
    string currentString = input;
    size_t currentStringsize = input.size();
    for (const auto& rule : rules) {
        size_t pos = rule.size() - 1;
        string before = currentString.substr(0, pos);
        string after = currentString.substr(pos, input.size());
        string newString = after + after;

        // Запись результата в выходной файл
        outputFile << "Исходная строка: " << currentString << endl;
        outputFile << "Применяемое правило: " << rule << endl;
        outputFile << "Результат применения правила: " << newString << endl << endl;

        currentString = newString;
        cout << "Вычисление прошло успешно" << endl;
        break;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Чтение входных данных из файла
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл input.txt" << endl;
        return 1;
    }

    vector<char> alphabet;
    vector<string> variables;
    vector<string> rules;
    vector<string> axioms;

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        if (line.find("A =") == 0) { // Собственный алфавит
            size_t startPos = line.find('{') + 1;
            size_t endPos = line.rfind('}');
            string elements = line.substr(startPos, endPos - startPos);

            istringstream iss(elements);
            char c;
            while (iss >> c) {
                alphabet.push_back(c);
            }
        }
        else if (line.find("X =") == 0) { // Множество переменных
            size_t startPos = line.find('{') + 1;
            size_t endPos = line.rfind('}');
            string elements = line.substr(startPos, endPos - startPos);

            istringstream iss(elements);
            string var;
            while (iss >> var) {
                variables.push_back(var);
            }
        }
        else if (line.find("A1 =") == 0) { // Множество аксиом
            size_t startPos = line.find('{') + 1;
            size_t endPos = line.rfind('}');
            string elements = line.substr(startPos, endPos - startPos);

            istringstream iss(elements);
            string axiom;
            while (iss >> axiom) {
                axioms.push_back(axiom);
            }
        }
        else if (line.find("R =") == 0) { // Конечное множество продукций
            size_t startPos = line.find('{') + 1;
            size_t endPos = line.rfind('}');
            string elements = line.substr(startPos, endPos - startPos);

            istringstream iss(elements);
            string rule;
            while (iss >> rule) {
                bool validRule = true;

                // Проверим каждый символ правила
                for (size_t i = 0; i < rule.length(); ++i) {
                    char c = rule[i];

                    if (c == '-' && i + 1 < rule.length() && rule[i + 1] == '>') {
                        i++;
                        continue;
                    }

                    if (!isInAlphabet(c, alphabet) && !isInVariables(string(1, c), variables)) {
                        validRule = false;
                        break;
                    }
                }

                if (validRule) {
                    rules.push_back(rule);
                }
                else {
                    cout << "Найдена переменная не входящая в заданное множество переменных." << endl;
                    break;
                }
            }
        }
    }

    inputFile.close();

    // Открытие файла для записи результатов
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "Не удалось создать файл output.txt" << endl;
        return 1;
    }

    // Выполнение эмуляции для каждой аксиомы
    for (const auto& axiom : axioms) {
        emulate(alphabet, variables, rules, axiom, outputFile);
    }

    outputFile.close();

    return 0;
}