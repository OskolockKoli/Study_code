import random
from math import sin, cos, exp, fabs
import numpy as np

def compare_float_and_complex(value, other_value):
    value_real = abs(value)
    other_value_real = abs(other_value)
    if value_real < other_value_real:
        return -1
    elif value_real > other_value_real:
        return 1
    elif value_real == other_value_real:
        return 0
    else:
        return 0

# Определение функциональных узлов
def add(a, b):
    return a + b

def sub(a, b):
    return a - b

def mul(a, b):
    return a * b

def div(a, b):
    if b == 0:
        return 9999  # большое число вместо деления на ноль
    else:
        return a / b

def power(a, b):
    return a ** b

def abs_val(a):
    return np.sqrt(np.abs(a))

def sin_val(a):
    return sin(a)

def cos_val(a):
    return cos(a)

def exp_val(a):
    return exp(a)

func_set = [add, sub, mul, div, power, abs_val, sin_val, cos_val, exp_val]

# Терминальные узлы
term_set = ['x']

class TreeNode:
    def __init__(self, data=None, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def evaluate(self, x):
        if isinstance(self.data, str):
            return x[0]  # Возвращаем первое значение из списка x
        elif callable(self.data):
            if self.data in [abs_val, sin_val, cos_val, exp_val]:
                if self.left is not None:
                    return self.data(self.left.evaluate(x))
                else:
                    raise ValueError("Left child is missing!")
            else:
                if self.left is not None and self.right is not None:
                    return self.data(self.left.evaluate(x), self.right.evaluate(x))
                else:
                    raise ValueError("One of the children is missing!")

    def __repr__(self):
        if isinstance(self.data, str):
            return self.data
        elif callable(self.data):
            name = self.data.__name__
            if self.data in [abs_val, sin_val, cos_val, exp_val]:
                return f"{name}({self.left})"
            else:
                return f"({self.left} {name} {self.right})"

def generate_random_tree(max_depth, func_set, term_set, depth=0):
    if depth >= max_depth or random.random() < 0.5:
        return TreeNode(random.choice(term_set))
    else:
        func = random.choice(func_set)
        if func in [abs_val, sin_val, cos_val, exp_val]:
            return TreeNode(func, generate_random_tree(max_depth, func_set, term_set, depth+1))
        else:
            left = generate_random_tree(max_depth, func_set, term_set, depth+1)
            right = generate_random_tree(max_depth, func_set, term_set, depth+1)
            return TreeNode(func, left, right)

def fitness(tree, target_function, X):
    total_error = 0
    for x in X:
        try:
            predicted_value = tree.evaluate(x)
            actual_value = target_function(x)
            error = (predicted_value - actual_value)**2
            total_error += error
        except Exception as e:
            total_error += 1000000  # большая ошибка за исключение
    return total_error

def tournament_selection(population, k=3):
    best = None
    for _ in range(k):
        candidate = random.choice(population)
        if not best or compare_float_and_complex(fitness(candidate, target_function, X), fitness(best, target_function, X)):
            best = candidate
    return best

def crossover(parent1, parent2):
    if random.random() < 0.7:
        subtree1 = random.choice([parent1.left, parent1.right])
        subtree2 = random.choice([parent2.left, parent2.right])
        
        # Проверяем, что выбранные узлы не являются пустыми
        if subtree1 is not None and subtree2 is not None:
            new_parent1 = TreeNode(parent1.data, parent1.left, parent1.right)
            new_parent2 = TreeNode(parent2.data, parent2.left, parent2.right)
            
            if subtree1 == parent1.left:
                new_parent1.left = subtree2
            else:
                new_parent1.right = subtree2
                
            if subtree2 == parent2.left:
                new_parent2.left = subtree1
            else:
                new_parent2.right = subtree1
                
            return new_parent1, new_parent2
    return parent1, parent2

def mutate(tree, func_set, term_set, max_depth):
    if random.random() < 0.05:
        node = tree
        while True:
            if node.left is None and node.right is None:
                break
            next_node = random.choice([node.left, node.right]) if node.right else node.left
            node = next_node
        if random.random() < 0.5:
            node.data = random.choice(term_set)
        else:
            node.data = random.choice(func_set)
            if node.data in [abs_val, sin_val, cos_val, exp_val]:
                node.left = generate_random_tree(max_depth, func_set, term_set)
                node.right = None
            else:
                node.left = generate_random_tree(max_depth, func_set, term_set)
                node.right = generate_random_tree(max_depth, func_set, term_set)
    return tree

def evolve(population, target_function, X, generations=50, max_depth=5):
    best_fitness = []
    for gen in range(generations):
        new_population = []
        for _ in range(len(population)):
            parent1 = tournament_selection(population)
            parent2 = tournament_selection(population)
            child1, child2 = crossover(parent1, parent2)
            mutated_child1 = mutate(child1, func_set, term_set, max_depth)
            mutated_child2 = mutate(child2, func_set, term_set, max_depth)
            new_population.append(mutated_child1)
            new_population.append(mutated_child2)
        
        population = new_population
        best_individual = min(population, key=lambda ind: fitness(ind, target_function, X))
        best_fitness.append(fitness(best_individual, target_function, X))
        print(f"Generation {gen}: Best Fitness = {best_fitness[-1]} | Program: {best_individual}")
    
    return best_individual, best_fitness

# Функция для тестирования
def target_function(x):
    result = 0
    for i in range(1, len(x)+1):
        result += sum(val**2 for val in x[:i])
    return result

# Генерация начальных значений x
N = 8
X = [[random.uniform(-5.536, 65.536)] for _ in range(N)]

# Начальная популяция
population_size = 20
max_depth = 5
initial_population = [generate_random_tree(max_depth, func_set, term_set) for _ in range(population_size)]

# Запуск эволюции
best_solution, best_fitness = evolve(initial_population, target_function, X, generations=30, max_depth=max_depth)

plt.figure(figsize=(10, 6))
plt.plot(range(len(best_fitness)), best_fitness, label="Fitness")
plt.xlabel("Generations")
plt.ylabel("Fitness Value")
plt.title("Evolution of Fitness over Generations")
plt.legend()
plt.show()

print("Best Solution:", best_solution)
print("Fitness History:", best_fitness)

