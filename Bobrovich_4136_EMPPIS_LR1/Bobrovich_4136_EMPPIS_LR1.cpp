#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <locale>
#include <codecvt>

// Целевая функция
double objective_function(double x) {
    if (x == 0.0) {
        return -std::numeric_limits<double>::infinity();
    }
    return std::cos(x) * (exp(-x) - exp(x)) / (exp(x) + exp(-x));
     // return std::cos(2*x) / abs(x);
}

// Турнирный отбор
int tournament_selection(std::vector<double>& population, std::vector<double>& fitness) {
    // Реализация турнирного отбора
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(population.size() - 1));

    int tournament_size = 3;
    int winner_index = 0;
    double winner_fitness = -std::numeric_limits<double>::infinity();

    for (int i = 0; i < tournament_size; i++) {
        int participant_index = dis(gen);
        double participant_fitness = fitness[participant_index];
            if (participant_fitness > winner_fitness) {
         // if (participant_fitness < winner_fitness) {
            winner_index = participant_index;
            winner_fitness = participant_fitness;
        }
    }

    return winner_index;
}

// Одноточечный кроссовер
void one_point_crossover(double& child1, double& child2, double parent1, double parent2) {
    // Реализация одноточечного кроссовера
    double crossover_point = static_cast<double>(rand()) / RAND_MAX;
    child1 = crossover_point * parent1 + (1 - crossover_point) * parent2;
    child2 = crossover_point * parent2 + (1 - crossover_point) * parent1;
}

// Мутация
void mutation(double& individual, double mutation_rate) {
    // Реализация мутации
    if (static_cast<double>(rand()) / RAND_MAX < mutation_rate) {
        individual += (static_cast<double>(rand()) / RAND_MAX - 0.5) * 2.0;
    }
}

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // Определение параметров ГА
    int population_size = 30;
    double crossover_rate = 0.8;
    double mutation_rate = 0.1;
    int max_generations = 1000;

    // Инициализация популяции
    std::vector<double> population(population_size);
    std::vector<double> fitness(population_size);

    // Основной цикл ГА
    for (int generation = 0; generation < max_generations; generation++) {
        // Вычисление значений функции приспособленности
        for (int i = 0; i < population_size; i++) {
            //population[i] = -10 + static_cast<double>(rand()) / RAND_MAX * (10 + 10);
            population[i] = -5 + static_cast<double>(rand()) / RAND_MAX * (5 + 5);
            fitness[i] = objective_function(population[i]);
        }

        // Отбор родителей
        std::vector<double> parents(population_size);
        for (int i = 0; i < population_size; i++) {
            parents[i] = population[tournament_selection(population, fitness)];
        }

        // Скрещивание и мутация
        for (int i = 0; i < population_size; i += 2) {
            double child1 = parents[i];
            double child2 = parents[i + 1];
            one_point_crossover(child1, child2, parents[i], parents[i + 1]);
            mutation(child1, mutation_rate);
            mutation(child2, mutation_rate);
            population[i] = child1;
            population[i + 1] = child2;
        }
    }

    // Вывод результата
    double best_x = *std::max_element(population.begin(), population.end(), [&](double x1, double x2) {
        return objective_function(x1) < objective_function(x2);
        });
    double best_f = objective_function(best_x);
    std::wcout << L"Найденный оптимум: x = " << best_x << L", f(x) = " << best_f << std::endl;

    return 0;
}
