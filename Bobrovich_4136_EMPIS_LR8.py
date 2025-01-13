import numpy as np
import matplotlib.pyplot as plt

all_projects = [
    {"L": 90.2, "Ef": 115.8},
    {"L": 46.2, "Ef": 96.0},
    {"L": 46.5, "Ef": 79.0},
    {"L": 54.5, "Ef": 909.8},
    {"L": 31.1, "Ef": 39.6},
    {"L": 67.5, "Ef": 98.4},
    {"L": 12.8, "Ef": 18.9},
    {"L": 10.5, "Ef": 10.3},
    {"L": 21.5, "Ef": 28.5},
    {"L": 3.1, "Ef": 7.0},
    {"L": 4.2, "Ef": 9.0},
    {"L": 7.8, "Ef": 7.3},
    {"L": 2.1, "Ef": 5.0},
    {"L": 5.0, "Ef": 8.4},
    {"L": 78.6, "Ef": 98.7},
    {"L": 9.7, "Ef": 15.6},
    {"L": 12.5, "Ef": 23.9},
    {"L": 100.8, "Ef": 138.3}
]


#Ошибку считаем MMRE среднее значение относительной погрешности
def fitness(a, b, projects):
    errors = []
    for project in projects:
        errors.append(abs(project["Ef"] - a*project["L"]**b) / project["Ef"])
    mmre = 1/len(projects) * sum(errors)
    return mmre


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
        if position[i] < -5:
            position[i] = -5
        # if position[i] > 20:
        #     position[i] = 20
    return position

def swarm_alg():
    projects = all_projects[0:13]
    num_particles = 100  # Количество частиц
    num_iterations = 1000  # Количество итераций
    c1 = 1  # Коэффициент личного опыта
    c2 = 2  # Коэффициент опыта группы
    # Инициализация частиц
    positions = np.random.uniform(0, 10, (num_particles, 2))  # Позиции частиц
    velocities = np.random.uniform(-1, 1, (num_particles, 2))  # Начальные скорости частиц
    personal_best_positions = positions.copy()  # Личные лучшие позиции
    personal_best_scores = np.array([fitness(p[0], p[1], projects) for p in positions])
    global_best_position = personal_best_positions[np.argmin(personal_best_scores)]  # Глобальная лучшая позиция
    print('Лучшая позиция в начале алгоритма:')
    print(global_best_position)
    for i in range(num_iterations):
        for j in range(num_particles):
            if fitness(positions[j][0], positions[j][1], projects) < fitness(personal_best_positions[j][0], personal_best_positions[j][1], projects):
                personal_best_positions[j] = positions[j].copy()
            if fitness(personal_best_positions[j][0], personal_best_positions[j][1], projects) < fitness(global_best_position[0], global_best_position[0], projects):
                global_best_position = personal_best_positions[j].copy()
            velocities[j] = correction_speed(velocities[j], positions[j], personal_best_positions[j], global_best_position, c1, c2)
            positions[j] = correction_position(positions[j], velocities[j])
    print('Лучшая позиция в конце алгоритма:')
    print(global_best_position)
    print_plot(projects, global_best_position)
    print('\n')
    return global_best_position


def print_plot(projects, global_best_positions):
    # Prepare data
    L_values = [proj["L"] for proj in projects]
    Ef_values = [proj["Ef"] for proj in projects]

    # Calculate Efm values
    Efm_values = [global_best_positions[0] * L ** global_best_positions[1] for L in L_values]

    # Create indices for uniform steps on x-axis
    x_indices = list(range(1, len(L_values) + 1))

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(x_indices, Ef_values, label="Ef (actual)", marker="o", color="blue", linestyle="-")
    plt.plot(x_indices, Efm_values, label=f"Efm", marker="x", color="red", linestyle="-")

    # Customize x-axis ticks
    plt.xticks(ticks=x_indices, labels=L_values)

    # Add labels, legend, and title
    plt.xlabel("Projects (L values)")
    plt.ylabel("Ef / Efm")
    plt.title("Graph of Ef and Efm values")
    plt.legend()
    plt.grid(True)

    # Show the plot
    plt.show()



if __name__ == '__main__':
    swarm_alg()
