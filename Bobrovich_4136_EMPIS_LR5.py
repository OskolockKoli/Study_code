import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import time

# Функция Rotated Hyper-Ellisoid Function
def rotated_hyper_ellipsoid_function(X):
    n = X.shape[1]
    result = 0
    for i in range(n):
        sum_x = np.sum(X[:, :i+1], axis=1)
        result += np.square(sum_x)
    return result

# Генетический алгоритм
class GeneticAlgorithm:
    
    def __init__(self, population_size, mutation_probability, max_generations, elite_percentage, min_value=-65.536, max_value=65.536):
        self.population_size = population_size
        self.mutation_probability = mutation_probability
        self.max_generations = max_generations
        self.elite_percentage = elite_percentage
        self.min_value = min_value
        self.max_value = max_value
        
    # Генерация начальной популяции
    def generate_initial_population(self, n):
        population = np.random.uniform(low=self.min_value, high=self.max_value, size=(self.population_size, n))
        return population
    
    # Турнирный отбор
    def tournament_selection(self, population, fitness_values):
        new_population = []
        for _ in range(self.population_size):
            candidate_indices = np.random.choice(population.shape[0], size=2, replace=False)
            candidates = population[candidate_indices]
            fitnesses = fitness_values[candidate_indices]
            best_candidate_index = np.argmin(fitnesses)
            new_population.append(candidates[best_candidate_index])
        return np.array(new_population)
    
    # Одноточечный кроссовер
    def single_point_crossover(self, parent1, parent2):
        crossover_point = np.random.randint(1, len(parent1))
        child1 = np.concatenate((parent1[:crossover_point], parent2[crossover_point:]))
        child2 = np.concatenate((parent2[:crossover_point], parent1[crossover_point:]))
        return child1, child2
    
    # Мутация
    def mutate(self, individual):
        mutated_individual = individual.copy()
        for i in range(len(individual)):
            if np.random.rand() <= self.mutation_probability:
                mutated_individual[i] = np.random.uniform(low=self.min_value, high=self.max_value)
        return mutated_individual
    
    # Основная функция генетического алгоритма
    def run(self, n):
        population = self.generate_initial_population(n)
        best_fitness = float('inf')
        best_solution = None
        generation_count = 0
        convergence_counter = 0
        fitness_history = []
        
        while generation_count < self.max_generations and convergence_counter < 10:
            fitness_values = rotated_hyper_ellipsoid_function(population)
            
            # Найдем лучшее решение в текущей популяции
            current_best_fitness = np.min(fitness_values)
            current_best_index = np.argmin(fitness_values)
            current_best_solution = population[current_best_index]
            
            if current_best_fitness == best_fitness:
                convergence_counter += 1
            else:
                convergence_counter = 0
                
            if current_best_fitness < best_fitness:
                best_fitness = current_best_fitness
                best_solution = current_best_solution
            
            # Сохраняем историю лучших решений
            fitness_history.append(best_fitness)
            
            # Отбор родителей методом турнира
            parents = self.tournament_selection(population, fitness_values)
            
            # Кроссовер и мутация
            next_population = []
            for i in range(0, self.population_size, 2):
                parent1 = parents[i]
                parent2 = parents[(i + 1) % self.population_size]
                child1, child2 = self.single_point_crossover(parent1, parent2)
                next_population.extend([child1, child2])
            
            # Добавляем элитных особей
            elite_count = int(self.elite_percentage * self.population_size)
            elite_indices = np.argsort(fitness_values)[:elite_count]
            next_population[-elite_count:] = population[elite_indices]
            
            # Применяем мутацию к новым особям
            next_population = np.array([self.mutate(individual) for individual in next_population])
            
            population = next_population
            generation_count += 1
        
        return best_solution, best_fitness, fitness_history, generation_count

# Визуализация функции и найденного экстремума для n=2
def visualize_function_and_extremum(n, solution, fitness_history, generations):
    fig = plt.figure(figsize=(12, 6))
    ax1 = fig.add_subplot(121, projection='3d' if n==2 else 'rectilinear')
    ax2 = fig.add_subplot(122)
    
    # Построим поверхность функции
    if n == 2:
        x = y = np.arange(-65.536, 65.537, 0.25)
        X, Y = np.meshgrid(x, y)
        Z = rotated_hyper_ellipsoid_function(np.stack((X.ravel(), Y.ravel()), axis=1)).reshape(X.shape)
        ax1.plot_surface(X, Y, Z, cmap='viridis', alpha=0.7)
        
        # Отображаем точки популяции
        population = np.random.uniform(low=-65.536, high=65.536, size=(50, 2))
        z_population = rotated_hyper_ellipsoid_function(population).reshape(-1, 1)
        ax1.scatter(population[:, 0], population[:, 1], z_population, c='r', marker='o', s=20)
        
        # Отображаем найденную точку минимума
        ax1.scatter(solution[0], solution[1], fitness_history[-1], c='g', marker='*', s=200)
        
    elif n == 3:
        ax1.set_title("График функции для n=3 недоступен")
    
    # График изменения лучшей приспособленности
    ax2.plot(range(generations), fitness_history)
    ax2.set_xlabel('Поколения')
    ax2.set_ylabel('Лучшая приспособленность')
    ax2.grid(True)
    
    plt.show()

# Исследование влияния параметров
def investigate_parameters():
    population_sizes = [10, 20, 30, 40, 50]
    mutation_probabilities = [0.01, 0.05, 0.1, 0.15, 0.2]
    
    results = {}
    
    for population_size in population_sizes:
        for mutation_probability in mutation_probabilities:
            print(f"Исследование для population_size={population_size}, mutation_probability={mutation_probability}")
            start_time = time.time()
            ga = GeneticAlgorithm(population_size=population_size, mutation_probability=mutation_probability, max_generations=100, elite_percentage=0.1)
            best_solution, best_fitness, fitness_history, generations = ga.run(n=2)
            end_time = time.time()
            execution_time = end_time - start_time
            results[(population_size, mutation_probability)] = {
                'execution_time': execution_time,
                'generations': generations,
                'accuracy': best_fitness
            }
            print(f"Результат: Время выполнения {execution_time:.2f} сек., поколений {generations}, точность {best_fitness:.8f}\n")
    
    return results

if __name__ == "__main__":
    # Выполнение для n=2
    ga = GeneticAlgorithm(population_size=50, mutation_probability=0.1, max_generations=100, elite_percentage=0.1)
    best_solution, best_fitness, fitness_history, generations = ga.run(n=2)
    visualize_function_and_extremum(n=2, solution=best_solution, fitness_history=fitness_history, generations=generations)
    
    # Исследование параметров
    results = investigate_parameters()
    
    # Выполнение для n=3
    ga_n3 = GeneticAlgorithm(population_size=50, mutation_probability=0.1, max_generations=100, elite_percentage=0.1)
    start_time_n3 = time.time()
    best_solution_n3, best_fitness_n3, fitness_history_n3, generations_n3 = ga_n3.run(n=3)
    end_time_n3 = time.time()
    execution_time_n3 = end_time_n3 - start_time_n3
    
    print(f"\nРезультат для n=3:")
    print(f"Время выполнения: {execution_time_n3:.2f} сек.")
    print(f"Поколений: {generations_n3}")
    print(f"Точность: {best_fitness_n3:.8f}")
