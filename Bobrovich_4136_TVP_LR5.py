import sys

# Функция для чтения алфавита из регулярного выражения
def read_alphabet(regex):
    alphabet = []
    for i in range(len(regex)):  # Проходимся по каждому символу в регулярном выражении
        if regex[i] not in alphabet and regex[i] not in ['(', ')', '|', '<', '>']:  # Проверяем, является ли текущий символ символом алфавита
            alphabet.append(regex[i])  # Добавляем уникальный символ в алфавит
    return alphabet

# Функция для вывода матрицы переходов в файл
def print_output(output_matrix, conditions):
    with open('output.txt', 'w', encoding='utf-8') as f:
        original_stdout = sys.stdout  # Сохраняем стандартный вывод
        sys.stdout = f  # Перенаправляем вывод в файл
        print('   ', '  '.join(['q'+str(i+1) for i in range(0, len(conditions))]))
        for i in range(len(conditions)):
            print('q'+str(i+1), end=' ')
            for j in range(len(conditions)):
                print(output_matrix[i][j], end=' ')
            print()
        sys.stdout = original_stdout  # Восстанавливаем стандартный вывод

# Функция для определения правил подчинения в регулярном выражении
def subordination_rules(regex, markup, A):
    subordination_dependencies = [[] for _ in range(len(regex)+1)]
    for i in range(len(regex)):
        bracket_counter = 0
        if regex[i] == '(' or regex[i] == '<':
            subordination_dependencies[i+1].append(i)
            for j in range(i, len(regex)):
                if regex[j] == '(' or regex[j] == '<':
                    bracket_counter += 1
                if regex[j] == ')' or regex[j] == '>':
                    if bracket_counter == 1:
                        break
                    else:
                        bracket_counter -= 1
                if regex[j] == '|' and bracket_counter == 1:
                    subordination_dependencies[j+1].append(i)
        bracket_counter = 0
        if regex[i] == '(' or regex[i] == '<':
            helper = []
            if regex[i] == '<':
                helper.append(i)
            for j in range(i, len(regex)):
                if regex[j] == '(' or regex[j] == '<':
                    bracket_counter += 1
                if regex[j] == ')' or regex[j] == '>':
                    if bracket_counter == 1:
                        subordination_dependencies[j+1] = helper
                        break
                    else:
                        bracket_counter -= 1
                if (regex[j] in A and regex[j+1] not in A) or (regex[j] == '>' and i != 0) and bracket_counter == 1:
                    helper.append(j+1)
        bracket_counter = 0
        if regex[i] == '>':
            place = i+1
            for j in range(i, -1, -1):
                if regex[j] == '>':
                    bracket_counter += 1
                if regex[j] == '<':
                    if bracket_counter == 1:
                        break
                    else:
                        bracket_counter -= 1
                if (regex[j] in A or regex[j] == '<') and regex[j-1] not in A and bracket_counter == 1:
                    subordination_dependencies[j].append(place)

    for i in range(len(subordination_dependencies)):
        for j in range(len(subordination_dependencies)):
            if i in subordination_dependencies[j]:
                markup[j].extend(x for x in markup[i] if x not in markup[j])
    return markup  # Возвращаем обновленную разметку


def main():
    with open('input.txt', 'r', encoding='utf-8') as f:
        regex = f.readline().strip()
    A = read_alphabet(regex)
    markup = [[] for _ in range(len(regex)+1)]
    pre_primary_places = []
    counter = 1
    for i in range(len(regex)+1):
        if i == 0:
            markup[i].append(0)
            continue
        if regex[i-1] in A:
            markup[i].append(counter)
            pre_primary_places.append(i-1)
            counter += 1
    markup = subordination_rules(regex, markup, A)  # Применяем правила подчинения к разметке
    markup = subordination_rules(regex, markup, A)  # Повторяем применение правил подчинения
    conditions = [[0]]
    i = 0
    table = {a:[] for a in A}
    while i < len(conditions):
        for a in A:
            flag = False
            adding = []
            for c in conditions[i]:
                for p in pre_primary_places:
                    if c in markup[p] and regex[p] == a:
                        adding.extend(markup[p+1])
                        flag = True
            if not flag:
                table[a].append(None)
            else:
                table[a].append(adding)
                if adding not in conditions:
                    conditions.append(adding)
        i += 1
    print(table)
    exit_simbols = markup[-1]
    is_condition_in_regex = []  # Список для хранения информации о наличии условия в регулярном выражении
    for i in range(len(conditions)):
        help = False
        for c in conditions[i]:
            if c in exit_simbols:
                help = True
        if help:
            is_condition_in_regex.append(1)
        else:
            is_condition_in_regex.append(0)

    array_table = list(table.values())  # Преобразуем таблицу переходов в список значений

    output_matrix = [['   ' for _ in range(len(conditions))] for _ in range(len(conditions))]  # Создаем пустую матрицу переходов

    keys_list = list(table.keys())
    for key in keys_list:
        # Индексируем элементы в таблице
        for i, element in enumerate(table[key]):
            try:
                # Ищем индекс элемента в условиях
                index = conditions.index(element)
            except ValueError:
                continue
            output_matrix[i][index] = key + '/' + str(is_condition_in_regex[index])

    for row in output_matrix:
        print(row)

    print_output(output_matrix, conditions)

if __name__ == '__main__':
    main()
