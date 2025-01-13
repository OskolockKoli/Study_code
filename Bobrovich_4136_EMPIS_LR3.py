import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.distance import cdist
import random
from copy import deepcopy

# Координаты городов
cities = [
    (1673, 1453), (2233, 10), (5530, 1424), (401, 841),
    (3082, 1644), (7608, 4458), (7573, 3716), (7265, 1268),
    (6898, 1885), (1112, 2049), (5468, 2606), (5989, 2873),
    (4706, 2674), (4612, 2035), (6347, 2683), (6107, 669),
    (7611, 5184), (7462, 3590), (7732, 4723), (5900, 3561),
    (4483, 3369), (6101, 1110), (5199, 2182), (1633, 2809),
    (4307, 2322), (675, 1006), (7555, 4819), (7541, 3981),
    (3177, 756), (7352, 4506), (7545, 2801), (3245, 3305),
    (6426, 3173), (4608, 1198), (23, 2216), (7248, 3779),
    (7762, 4595), (7392, 2244), (3484, 2829), (6271, 2135),
    (4985, 140), (1916, 1569), (7280, 4899), (7509, 3239),
    (10, 2676), (6807, 2993), (5185, 3258), (3023, 1942)
]

# Вычисление матрицы расстояний
def calculate_distance_matrix(cities):
    return cdist(cities, cities)

distance_matrix = calculate_distance_matrix(np.array(cities))

class GeneticAlgorithm:
    
    def __init__(self, distance_matrix, population_size=50, max_generations=200,
                 crossover_probability=0.85, mutation_probability=0.05):
        self.distance_matrix = distance_matrix
        self.population_size = population_size
        self.max_generations = max_generations
        self.crossover_probability = crossover_probability
        self.mutation_probability = mutation_probability
        
        # Генерация начальной популяции
        self.population = [np.random.permutation(len(distance_matrix)) for _ in range(population_size)]
        
    def fitness(self, individual):
        """Вычисляем длину маршрута"""
        total_distance = 0
        for i in range(len(individual)):
            j = (i + 1) % len(individual)
            city1 = individual[i]
            city2 = individual[j]
            total_distance += self.distance_matrix[city1][city2]
        return total_distance
    
    def selection(self):
        """Турнирный отбор"""
        selected = []
        for _ in range(self.population_size // 2):
            candidate1 = random.choice(self.population)
            candidate2 = random.choice(self.population)
            if self.fitness(candidate1) < self.fitness(candidate2):
                selected.append(deepcopy(candidate1))
            else:
                selected.append(deepcopy(candidate2))
        return selected
    
    def crossover(self, parent1, parent2):
        """Одноточечный кроссовер"""
        if random.random() > self.crossover_probability:
            return parent1, parent2
        
        cut_point = random.randint(1, len(parent1) - 1)
        child1 = np.concatenate([parent1[:cut_point], parent2[cut_point:]])
        child2 = np.concatenate([parent2[:cut_point], parent1[cut_point:]])
        
        # Убедимся, что все города присутствуют в маршруте
        missing_cities1 = set(range(len(parent1))) - set(child1)
        missing_cities2 = set(range(len(parent2))) - set(child2)
        
        for i, city in enumerate(child1):
            if city in missing_cities2:
                child2[i] = list(missing_cities2)[0]
                missing_cities2.remove(list(missing_cities2)[0])
                
        for i, city in enumerate(child2):
            if city in missing_cities1:
                child1[i] = list(missing_cities1)[0]
                missing_cities1.remove(list(missing_cities1)[0])
        
        return child1, child2
    
    def mutate(self, individual):
        """Перестановочная мутация"""
        if random.random() > self.mutation_probability:
            return individual
        
        pos1, pos2 = random.sample(range(len(individual)), 2)
        individual[pos1], individual[pos2] = individual[pos2], individual[pos1]
        return individual
    
    def run(self):
        best_fitness = float('inf')
        best_individual = None
        
        for generation in range(self.max_generations):
            offspring = []
            
            # Селекция
            parents = self.selection()
            
            # Кроссовер
            for i in range(0, len(parents), 2):
                parent1 = parents[i]
                parent2 = parents[(i + 1) % len(parents)]
                child1, child2 = self.crossover(parent1, parent2)
                offspring.extend([child1, child2])
            
            # Мутация
            for individual in offspring:
                self.mutate(individual)
            
            # Обновление популяции
            self.population = offspring
            
            # Оценка текущей популяции
            fitnesses = [self.fitness(individual) for individual in self.population]
            current_best_fitness = min(fitnesses)
            if current_best_fitness < best_fitness:
                best_fitness = current_best_fitness
                best_index = fitnesses.index(current_best_fitness)
                best_individual = self.population[best_index]
                
            print(f'Generation {generation+1}: Best Fitness = {best_fitness}')
        
        return best_fitness, best_individual

# Запуск генетического алгоритма
ga = GeneticAlgorithm(distance_matrix, population_size=100, max_generations=500)
best_fitness, best_route = ga.run()
print(f'Best Route: {list(best_route)}')
print(f'Total Distance: {best_fitness}')

# Графическое представление решения
plt.figure(figsize=(10, 10))
for i in range(len(best_route)):
    j = (i + 1) % len(best_route)
    city1 = cities[best_route[i]]
    city2 = cities[best_route[j]]
    plt.plot([city1[0], city2[0]], [city1[1], city2[1]], 'b-', lw=1)

plt.scatter(*zip(*cities), marker='o', color='r')
for i, city in enumerate(cities):
    plt.text(city[0]+10, city[1]+10, str(i+1), fontsize=10)

plt.title('Optimal Path Found by Genetic Algorithm')
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.show()
