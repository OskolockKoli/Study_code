#Часть 1

# Целевая функция
def objective_function(x1, x2):
    return 50 * x1 + 40 * x2

# Ограничения
def constraints(x1, x2):
    if 8 * x1 + 5 * x2 <= 40 and 5 * x1 + 6 * x2 <= 30 and 2 * x1 + 5 * x2 <= 20 and x1 >= 0 and x2 >= 0:
        return True
    else:
        return False

# Решение
max_value = 0
optimal_x1 = 0
optimal_x2 = 0

for x1 in range(6):
    for x2 in range(5):
        if constraints(x1, x2):
            value = objective_function(x1, x2)
            if value > max_value:
                max_value = value
                optimal_x1 = x1
                optimal_x2 = x2

print(f"Оптимальное решение:")
print(f"x1 = {optimal_x1}")
print(f"x2 = {optimal_x2}")
print(f"Z = {max_value}")

#Часть 2

def variational_problem():
    # Задание граничных условий
    x_min = -2
    x_max = -1
    y_left = 1/16
    y_right = 1

    # Определение подынтегральной функции
    def integrand(x, y, y_prime):
        return x**2 * y_prime**2 + 12 * y**2

    # Решение уравнения Эйлера-Лагранжа
    def euler_lagrange(x):
        # Дифференциальное уравнение Эйлера-Лагранжа
        a = 1
        b = 2 * x
        c = -12
        discriminant = b**2 - 4 * a * c
        if discriminant >= 0:
            def y1(x):
                return x**(-4)
            def y2(x):
                return x**3
            # Использование граничных условий для определения коэффициентов
            c1 = 1
            c2 = (y_left - c1 * y1(x_min)) / y2(x_min)
            return c1 * y1(x) + c2 * y2(x), c1, c2
        else:
            return None, None, None

    # Вычисление оптимального решения
    def optimal_solution(x):
        return euler_lagrange(x)[0]

    return optimal_solution, euler_lagrange(x_max)[1], euler_lagrange(x_min)[2]

# Получение оптимального решения и коэффициентов
optimal_solution, c1, c2 = variational_problem()
print(f"Коэффициент c1: {c1}")
print(f"Коэффициент c2: {c2}")
print(optimal_solution(-2))
print(optimal_solution(-1))
