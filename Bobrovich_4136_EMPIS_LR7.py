import numpy as np
import matplotlib.pyplot as plt


def function(*args):
    return (-20 * np.exp(-0.2 * np.sqrt(1/len(args) * sum([arg**2 for arg in args]))) -
            np.exp(1/len(args) * sum([np.cos(2 * np.pi * arg) for arg in args])) + 20 + np.e)

# def function(x, y):
#     return (-20 * np.exp(-0.2 * np.sqrt(0.5 * (x ** 2 + y ** 2))) -
#             np.exp(0.5 * (np.cos(2 * np.pi * x) + np.cos(2 * np.pi * y))) + 20 + np.e)


def correction_speed(speed, position, personal_best_positions, global_best_position, c1=1.5, c2=1.5):
    n = len(speed)
    for i in range(n):
        speed[i]  += c1 * np.random.rand() * (personal_best_positions[i] - position[i]) + \
                        c2 * np.random.rand() * (global_best_position[i] - position[i])
        if speed[i] < -3:
            speed[i] = -3
        if speed[i] > 3:
            speed[i] = 3
    return speed

def correction_position(position, speed):
    n = len(position)
    for i in range(n):
        position[i] += speed[i]
        if position[i] < -20:
            position[i] = -20
        if position[i] > 20:
            position[i] = 20
    return position


def swarm_alg(n):
    num_particles = 20  # Количество частиц
    num_iterations = 500  # Количество итераций
    w = 0.5  # Вес инерции
    c1 = 1  # Коэффициент личного опыта
    c2 = 2  # Коэффициент опыта группы
    # Инициализация частиц
    #n = 2  # Количество переменных
    positions = np.random.uniform(-10, 10, (num_particles, n))  # Позиции частиц
    velocities = np.random.uniform(-1, 1, (num_particles, n))  # Начальные скорости частиц
    personal_best_positions = positions.copy()  # Личные лучшие позиции
    personal_best_scores = np.array([function(*p) for p in positions])
    global_best_position = personal_best_positions[np.argmin(personal_best_scores)]  # Глобальная лучшая позиция

    print(global_best_position)
    if n == 2:
        plot_with_particles(positions)
    for i in range(num_iterations):
        for j in range(num_particles):
            if function(*positions[j]) < function(*personal_best_positions[j]):
                personal_best_positions[j] = positions[j].copy()
            if function(*personal_best_positions[j]) < function(*global_best_position):
                global_best_position = personal_best_positions[j].copy()
            velocities[j] = correction_speed(velocities[j], positions[j], personal_best_positions[j], global_best_position, c1, c2)
            positions[j] = correction_position(positions[j], velocities[j])
    print(global_best_position)
    #print(positions)
    if n == 2:
        plot_with_particles(positions)
    return global_best_position


def plot_with_particles(positions, bounds=(-20, 20), resolution=100):
    """
    :param positions: Позиции частиц, массив размера (num_particles, 2).
    :param bounds: Кортеж с границами области (-bounds, bounds).
    :param resolution: Количество точек на ось для сетки.
    """
    # Создаем сетку координат для графика
    x = np.linspace(bounds[0], bounds[1], resolution)
    y = np.linspace(bounds[0], bounds[1], resolution)
    X, Y = np.meshgrid(x, y)

    # Вычисляем значения функции для сетки
    Z = function(X, Y)

    # Создаем объект графика
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')

    # Строим поверхность
    ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.6)

    # Извлекаем координаты частиц
    particle_x = positions[:, 0]
    particle_y = positions[:, 1]
    particle_z = np.array([function(px, py) for px, py in positions])

    # Отображаем только точки частиц
    ax.scatter(particle_x, particle_y, particle_z, color='red', s=50, label='Particles')

    # Настройка меток осей
    ax.set_xlabel('X axis')
    ax.set_ylabel('Y axis')
    ax.set_zlabel('Z axis')

    # Показать график
    plt.show()


if __name__ == '__main__':
    n = 2
    swarm_alg(n)
