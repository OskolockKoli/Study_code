import random
import matplotlib.pyplot as plt
from itertools import permutations
import timeit

class Ant:
    def __init__(self, graph):
        self.graph = graph
        self.path = []
        self.current_city = None
    
    def start(self, start_city):
        self.current_city = start_city
        self.path.append(start_city)
        
    def move_to_next_city(self):
        next_cities = list(set(range(len(self.graph))) - set(self.path))
        probabilities = [self.graph[self.current_city][city]['pheromone'] for city in next_cities]
        total_pheromone = sum(probabilities)
        if total_pheromone == 0:
            return random.choice(next_cities)
        probabilities = [p / total_pheromone for p in probabilities]
        next_city = random.choices(next_cities, weights=probabilities)[0]
        self.path.append(next_city)
        self.current_city = next_city
        return next_city
    
    def is_finished(self):
        return len(self.path) == len(self.graph)

    def path_length(self):
        distance = 0
        for i in range(len(self.path) - 1):
            distance += self.graph[self.path[i]][self.path[i+1]]['distance']
        return distance

def update_pheromones(graph, ants, decay_rate, Q):
    for i in range(len(graph)):
        for j in range(i + 1, len(graph)):
            pheromone = graph[i][j]['pheromone']
            delta_pheromone = sum([Q / ant.path_length() for ant in ants if (i, j) in zip(ant.path[:-1], ant.path[1:])])
            graph[i][j]['pheromone'] = (1 - decay_rate) * pheromone + delta_pheromone
            graph[j][i]['pheromone'] = graph[i][j]['pheromone']

def create_graph(cities):
    n = len(cities)
    graph = [[{'distance': abs(cities[i][0] - cities[j][0]) + abs(cities[i][1] - cities[j][1]), 'pheromone': 1} for j in range(n)] for i in range(n)]
    return graph

def find_hamiltonian_path(graph, num_ants, max_iterations, decay_rate, Q):
    best_ant = None
    best_path_length = float('inf')
    for _ in range(max_iterations):
        ants = [Ant(graph) for _ in range(num_ants)]
        for ant in ants:
            ant.start(random.randint(0, len(graph) - 1))
            while not ant.is_finished():
                ant.move_to_next_city()
        update_pheromones(graph, ants, decay_rate, Q)
        for ant in ants:
            path_length = ant.path_length()
            if path_length < best_path_length:
                best_path_length = path_length
                best_ant = ant
    return best_ant

def find_travelling_salesman_path(graph, num_ants, max_iterations, decay_rate, Q):
    best_ant = None
    best_path_length = float('inf')
    for _ in range(max_iterations):
        ants = [Ant(graph) for _ in range(num_ants)]
        for ant in ants:
            ant.start(random.randint(0, len(graph) - 1))
            while not ant.is_finished():
                ant.move_to_next_city()
            # Возвращение в начальную точку
            ant.path.append(ant.path[0])
        update_pheromones(graph, ants, decay_rate, Q)
        for ant in ants:
            path_length = ant.path_length()
            if path_length < best_path_length:
                best_path_length = path_length
                best_ant = ant
    return best_ant

def visualize_path(cities, path):
    plt.figure(figsize=(10, 10))
    for i in range(len(path) - 1):
        x1, y1 = cities[path[i]]
        x2, y2 = cities[path[i+1]]
        plt.plot([x1, x2], [y1, y2], color='b', marker='o')
    plt.show()

def compare_with_optimal(optimal_path, optimal_path_length, found_path, found_path_length):
    print("Длина оптимального пути:", optimal_path_length)
    if found_path_length == optimal_path_length:
        print("Найденное решение совпадает с оптимальным.")
    else:
        print("Найденное решение отличается от оптимального.")

def run_experiments(experiments):
    results = []
    for experiment in experiments:
        start_time = timeit.default_timer()
        best_ant = find_travelling_salesman_path(graph, **experiment)
        end_time = timeit.default_timer()
        execution_time = end_time - start_time
        results.append((best_ant.path_length(), execution_time))
    return results

# Данные о городах
cities = [
    (6734, 1453), (2233, 10), (5530, 1424), (401, 841), (3082, 1644),
    (7608, 4458), (7573, 3716), (7265, 1268), (6898, 1885), (1112, 2049),
    (5468, 2606), (5989, 2873), (4706, 2674), (4612, 2035), (6347, 2683),
    (6107, 669), (7611, 5184), (7462, 3590), (7732, 4723), (5900, 3561),
    (4483, 3369), (6101, 1110), (5199, 2182), (1633, 2809), (4307, 2322),
    (675, 1006), (7555, 4819), (7541, 3981), (3177, 756), (7352, 4506),
    (7545, 2801), (3245, 3305), (6426, 3173), (4608, 1198), (23, 2216),
    (7248, 3779), (7762, 4595), (7392, 2244), (3484, 2829), (6271, 2135),
    (4985, 140), (1916, 1569), (7280, 4899), (7509, 3239), (10, 2676),
    (6807, 2993), (5185, 3258), (3023, 1942)
]

graph = create_graph(cities)

# Параметры для эксперимента
experiments = [
    {'num_ants': 10, 'max_iterations': 100, 'decay_rate': 0.05, 'Q': 50},
    {'num_ants': 20, 'max_iterations': 150, 'decay_rate': 0.07, 'Q': 75},
    {'num_ants': 30, 'max_iterations': 200, 'decay_rate': 0.09, 'Q': 100}
]

# Запуск эксперимента
results = run_experiments(experiments)

# Вывод результатов
for result in results:
    print(f'Path length: {result[0]}, Execution time: {result[1]:.2f} seconds')

# Поиск гамильтонова пути
num_ants = 50
max_iterations = 200
decay_rate = 0.1
Q = 100

best_ant = find_hamiltonian_path(graph, num_ants, max_iterations, decay_rate, Q)
print("Лучший путь:", best_ant.path)
print("Длина лучшего пути:", best_ant.path_length())
visualize_path(cities, best_ant.path)

# Сравнение с оптимальным решением
optimal_path = [1, 8, 38, 31, 44, 18, 7, 28, 6, 37, 19, 27, 17, 43, 30, 36, 46, 33, 20, 47, 21, 32, 39, 48, 5, 42, 24, 10, 45, 35, 4, 26, 2, 29, 34, 41, 16, 22, 3, 23, 14, 25, 13, 11, 12, 15, 40, 9]

optimal_path_length = sum([graph[optimal_path[i]][optimal_path[i+1]]['distance'] for i in range(len(optimal_path)-1)])
compare_with_optimal(optimal_path, optimal_path_length, best_ant.path, best_ant.path_length())

# Поиск пути коммивояжёра
num_ants = 50
max_iterations = 200
decay_rate = 0.1
Q = 100

best_ant = find_travelling_salesman_path(graph, num_ants, max_iterations, decay_rate, Q)
print("Лучший путь:", best_ant.path)
print("Длина лучшего пути:", best_ant.path_length())
visualize_path(cities, best_ant.path)

# Сравнение с оптимальным решением
optimal_path = [1, 8, 38, 31, 44, 18, 7, 28, 6, 37, 19, 27, 17, 43, 30, 36, 46, 33, 20, 47, 21, 32, 39, 48, 5, 42, 24, 10, 45, 35, 4, 26, 2, 29, 34, 41, 16, 22, 3, 23, 14, 25, 13, 11, 12, 15, 40, 9, 1]

optimal_path_length = sum([graph[optimal_path[i]][optimal_path[i+1]]['distance'] for i in range(len(optimal_path)-1)])
compare_with_optimal(optimal_path, optimal_path_length, best_ant.path, best_ant.path_length())
