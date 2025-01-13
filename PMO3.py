import numpy as np
from scipy.optimize import linprog
import matplotlib.pyplot as plt

# Целевая функция: -3x1 - 2x2
c = [3, 2]

# Левые части ограничений
A = [
    [1, -1],
    [2, 2],
    [1, 1],
    [-2, 6]
]

# Правые части ограничений
b = [-3, 2, 6, 20]

# Границы переменных
x0_bounds = (0, None)  # x1 >= 0
x1_bounds = (0, None)  # x2 >= 0

res = linprog(c, A_ub=A, b_ub=b, bounds=[x0_bounds, x1_bounds], method='simplex')

print("Результат оптимизации:")
print("x1 =", res.x[0])
print("x2 =", res.x[1])
print("Значение целевой функции:", -res.fun)

# Графическая интерпретация

x = np.linspace(0, 10, 400)
y1 = -3 + x
y2 = (2 - 2 * x) / 2
y3 = 6 - x
y4 = (20 + 2 * x) / 6

plt.plot(x, y1, label=r'$x_1 \leq 4$')
plt.plot(x, y2, label=r'$x_2 \leq 5$')
plt.plot(x, y3, label=r'$x_1 + x_2 \geq 2$')
plt.plot(x, y4, label=r'$x_2 \geq 0$')
plt.xlim((0, 10))
plt.ylim((0, 10))
plt.xlabel(r'$x_1$')
plt.ylabel(r'$x_2$')
plt.fill_between(x, 0, y1, where=(y1 <= 0), interpolate=True, alpha=0.2)
plt.fill_between(x, 0, y2, where=(y2 >= 0), interpolate=True, alpha=0.2)
plt.fill_between(x, 0, y3, where=(y3 >= 0), interpolate=True, alpha=0.2)
plt.fill_between(x, 0, y4, where=(y4 <= 0), interpolate=True, alpha=0.2)
plt.legend(loc='upper right')
plt.scatter(res.x[0], res.x[1], color='red', marker='o', label='Оптимум')
plt.legend()
plt.show()
