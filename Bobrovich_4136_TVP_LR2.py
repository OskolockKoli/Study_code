class TuringMachine:
    def __init__(self, tape, states, initial_state, final_states, transitions):
        self.tape = list(tape)
        self.states = states
        self.initial_state = initial_state
        self.final_states = final_states
        self.transitions = transitions
        self.current_state = initial_state
        self.head_position = 0

    def step(self):
        if self.current_state in self.final_states:
            return False

        current_symbol = self.tape[self.head_position]
        transition = self.transitions.get((self.current_state, current_symbol))
        
        if not transition:
            raise ValueError(f"No transition defined for state {self.current_state} and symbol {current_symbol}")

        new_state, write_symbol, direction = transition
        self.tape[self.head_position] = write_symbol
        self.current_state = new_state

        if direction == '<':
            self.head_position -= 1
        elif direction == '>':
            self.head_position += 1

        # Если вышли за пределы ленты, добавляем пустые символы
        if self.head_position < 0 or self.head_position >= len(self.tape):
            self.tape.append('_')

        return True

    def run_and_log(self, log_file):
        with open(log_file, 'w') as f:
            while self.step():
                tape_str = ''.join(self.tape)
                head_marker = '^'
                command = f"{self.current_state} {self.tape[self.head_position]} -> {new_state} {write_symbol} {direction}"
                f.write(f"{tape_str}\n{head_marker:{self.head_position + 1}}\n{command}\n\n")

def read_input(file_path):
    with open(file_path, 'r') as file:
        return file.read().strip()

def read_alphabet(file_path):
    with open(file_path, 'r') as file:
        return set(file.read().split())

def read_commands(file_path):
    transitions = {}
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split('->')
            if len(parts) != 2:
                continue
            source, target = parts
            source_parts = source.split()
            if len(source_parts) != 2:
                continue
            source_state, source_symbol = source_parts
            target_parts = target.split()
            if len(target_parts) != 3:
                continue
            target_state, write_symbol, direction = target_parts
            transitions[(source_state, source_symbol)] = (target_state, write_symbol, direction)
    return transitions

def main():
    try:
        input_tape = read_input("input.txt")
        alphabet = read_alphabet("alphabet.txt")
        transitions = read_commands("commands.txt")

        states = set(transition[0][0] for transition in transitions.keys()) | \
                 set(transition[1][0] for transition in transitions.values())
        final_states = {'!'}

        machine = TuringMachine(input_tape, states, 'q0', final_states, transitions)
        machine.run_and_log("output.txt")

    except Exception as e:
        print(f"Ошибка: {e}")

if __name__ == "__main__":
    main()
