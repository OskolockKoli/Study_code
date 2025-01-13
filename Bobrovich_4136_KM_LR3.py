import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import minimize

# Данные
data = {'Year': [2009, 2010, 2011, 2012, 2013, 2014, 2015], 'Births': [1.767, 1.788, 1.796, 1.902, 1.895, 1.947, 1.944]}
years = data['Year']
births = data['Births']

# Функция для нахождения параметров полинома методом максимального правдоподобия
def mle(x, y):
    def f(beta):
        a0, a1, a2 = beta
        return lambda t: a2*t**2 + a1*t + a0
    
    def jacobian(beta):
        a0, a1, a2 = beta
        return lambda t: [2*a2*t + a1, t + 1, 1]
    
    def loss(beta):
        diff = list(map(lambda i: f(beta)(x[i]) - y[i], range(len(x))))
        return sum(diff)**2
    
    def func(beta):
        return loss(beta)
    
    def gradient(beta):
        g = np.zeros_like(beta)
        for i in range(len(beta)):
            new_beta = beta.copy()
            new_beta[i] += 1e-6
            g[i] = (func(new_beta) - func(beta)) / 1e-6
        return g
    
    res = minimize(func, x0=[0, 0, 0], method='BFGS', jac=gradient)
    return res.x

# Подбор степени полинома и построение графиков различных вариантов
degrees = range(1, 5)
for degree in degrees:
    coefs = np.polyfit(years, births, deg=degree)
    poly = np.poly1d(coefs)
    plt.figure()
    plt.plot(years, poly(years), label=f'Degree {degree}')
    plt.scatter(years, births, color='red', marker='o', label='Data points')
    plt.legend()
    plt.title(f'Polynomial Fit of Birth Data (Degree {degree})')
    plt.xlabel('Year')
    plt.ylabel('Number of Births (millions)')
    plt.show()

# Нахождение параметров полинома второго порядка
coefs = mle(years, births)
poly = np.poly1d(coefs)
x_range = np.linspace(min(years), max(years), num=100)

# Прогнозирование следующего года и оценка ошибки
forecasted_value = poly(max(years)+1)
if forecasted_value == 0:
    print("Forecasted value for next year: 0.0")
    print("Error estimate: cannot be calculated.")
else:
    error = abs(forecasted_value - births[-1]) / forecasted_value * 100
    print("Forecasted value for next year:", forecasted_value)
    print("Error estimate:", error, "%")

# Оценка достоверности модели
def adj_r_squared(r_squared, n, k):
    return 1 - ((1 - r_squared) * (n - 1)) / (n - k - 1)

def r_squared(y, yhat):
    ss_tot = sum((y - np.mean(y)) ** 2)
    ss_res = sum((y - yhat) ** 2)
    return 1 - (ss_res / ss_tot)

# Полиномы первой и второй степени
polynomial_first_order = np.poly1d([np.polyfit(years, births, 1)[0]])
polynomial_second_order = np.poly1d(coefs)

# Вычисление значений функций для каждого года
y_first_order = polynomial_first_order(years)
y_second_order = polynomial_second_order(years)

# Вычисление коэффициентов детерминации
r_squared_first_order = r_squared(births, y_first_order)
r_squared_second_order = r_squared(births, y_second_order)

# Вычисление скорректированных коэффициентов детерминации
adj_r_squared_first_order = adj_r_squared(r_squared_first_order, len(years), 1)
adj_r_squared_second_order = adj_r_squared(r_squared_second_order, len(years), 2)

# Выбор лучшей модели
if adj_r_squared_first_order > adj_r_squared_second_order:
    best_model = 'First order polynomial'
else:
    best_model = 'Second order polynomial'

print(f"The best model is {best_model}.")

# Пример оценки точности прогноза
predictions = np.poly1d(coefs)(years)
actual_values = births

# Вычисление MSE и R^2
mse = np.mean((actual_values - predictions) ** 2)
r2 = 1 - mse / np.var(actual_values)

# Печатаем результаты
print(f"MSE: {mse}")
print(f"R^2: {r2}")
