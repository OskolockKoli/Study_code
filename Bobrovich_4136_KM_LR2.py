import numpy as np
from matplotlib import pyplot as plt
from scipy.stats import chi2_contingency, poisson

def generate_poisson_stream(T1, T2, lambda1, lambda2):
    """Функция для генерации пуассоновского потока"""
    # Генерация выборок для обоих потоков
    samples1 = np.random.poisson(lambda1 * (T2 - T1), size=(50,))
    samples2 = np.random.poisson(lambda2 * (T2 - T1), size=(50,))
    
    # Объединение выборок
    combined_samples = samples1 + samples2
    
    return samples1, samples2, combined_samples

# Исходные данные
N = 3
TT1 = N
TT2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)

# Генерация выборок
samples1, samples2, combined_samples = generate_poisson_stream(TT1, TT2, lambda1, lambda2)

# Визуализация потоков
plt.figure()
plt.subplot(311)
plt.title('Поток 1')
plt.hist(samples1, bins='auto', color='b')
plt.xlabel('Значение')
plt.ylabel('Частота')

plt.subplot(312)
plt.title('Поток 2')
plt.hist(samples2, bins='auto', color='g')
plt.xlabel('Значение')
plt.ylabel('Частота')

plt.subplot(313)
plt.title('Объединенный поток')
plt.hist(combined_samples, bins='auto', color='r')
plt.xlabel('Значение')
plt.ylabel('Частота')
plt.show()

# Проверка гипотезы о виде распределения для суммарного потока
unique_values, counts = np.unique(combined_samples, return_counts=True)
unique_values = list(set(unique_values))
observed = dict(zip(unique_values, counts))
observed = np.asarray(observed.values())

expected = np.array([len(combined_samples) * poisson.pmf(k, (lambda1 + lambda2)*(TT2 - TT1)) for k in unique_values])

stat, pvalue, dof, expected = chi2_contingency(expected, observed)
print("Статистический показатель Пирсона: {}".format(stat))
print("P-значение: {}".format(pvalue))

# Сравнение интенсивностей выборочных и теоретических интенсивностей потоков
mean1 = np.mean(samples1) / (TT2 - TT1)
mean2 = np.mean(samples2) / (TT2 - TT1)
mean_combined = np.mean(combined_samples) / (TT2 - TT1)

lambda1_theoretical = lambda1
lambda2_theoretical = lambda2
lambda_sum_theoretical = lambda1_theoretical + lambda2_theoretical

print("Выборочная интенсивность потока 1: {:.4f}".format(mean1))
print("Теоретическая интенсивность потока 1: {:.4f}".format(lambda1_theoretical))
print("Разница: {:.4f}".format(abs(mean1 - lambda1_theoretical)))

print("\nВыборочная интенсивность потока 2: {:.4f}".format(mean2))
print("Теоретическая интенсивность потока 2: {:.4f}".format(lambda2_theoretical))
print("Разница: {:.4f}".format(abs(mean2 - lambda2_theoretical)))

print("\nВыборочная интенсивность объединённого потока: {:.4f}".format(mean_combined))
print("Теоретическая интенсивность объединённого потока: {:.4f}".format(lambda_sum_theoretical))
print("Разница: {:.4f}".format(abs(mean_combined - lambda_sum_theoretical)))
