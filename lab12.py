import os.path
import csv
import scipy.stats as stats

class DispAnal():
    def __init__(self, name_row):
        
        self.data = []
        self.file_names = ["4131.csv" ,"4132.csv" ,"4133.csv" ,"4134.csv" ,"4136.csv"]
        self.name = name_row

        self.M_flow = 0
        self.M_groups = {}

        temp_len = 0
        temp_sum = 0

        for i in range(len(self.file_names)):
            file_path = os.path.join(os.path.dirname(__file__),'..', 'data', self.file_names[i])
            temp = []
            with open(file_path, encoding='utf-8', newline='') as f:
                reader = csv.DictReader(f)
                
                for row in reader:
                    temp.append(int(row.get(name_row)))
            
            self.data.append(temp)
            self.M_groups[self.file_names[i]] = sum(self.data[i]) / len(self.data[i])
            temp_len += len(self.data[i])
            temp_sum += sum(self.data[i])
                                         
        self.M_flow = temp_len / temp_sum

    def PrintSolv(self):
        
        f_stat, p_val = stats.f_oneway(self.data[0], self.data[1], self.data[2], self.data[3], self.data[4])

        print("\n" + "_"*45 + self.name + "_"*45 + "\n")

        text = ""
        for i in range(len(self.data)):
            text += f"\tM_{self.file_names[i]} = {round(self.M_groups[self.file_names[i]], 5)}"

        print(text)
        print(f"\n\tM_flow = { self.M_flow }")
        print(f"\n\tF = { f_stat }\t\tp_value = { p_val }")

        if (p_val > 0.05):
            print("\tthe mathematical expectations of all samples are equal\n")
        else:
            print("\tthe mathematical expectations of all samples are NOT equal\n")


def main():
   
    names = [ "category_1", "category_2", "category_3", "category_4", "category_5"]
   

    for i in range(len(names)):
        c = DispAnal(names[i])
        c.PrintSolv()

if __name__ == '__main__':
    main()
