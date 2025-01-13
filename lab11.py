import csv
from scipy import integrate, stats
import os.path
import math
import numpy as np
import matplotlib.pyplot as plt

def IntegrateFun(point, m, d):
    fu = (1 / (d * (2*np.pi) ** 0.5)  ) * np.exp(- ( ( (point - m )**2 ) / (2 * d ** 2) ) )

    def f(x, m, d):
        rez = (1 / (d * (2*np.pi) ** 0.5)) * np.exp(- (((x - m) ** 2) / (2 * d ** 2)))
    
        return rez

    
    if point == np.inf:
        return 1
    elif point == -np.inf:
        return 0
    else:
        result = integrate.quad(f, -np.inf, point, args = (m,d))
                       
        return result[0]

class PirsCret():
    def __init__(self, name_row, file_name):
        
        self.file_name = file_name
        self.name = name_row
        self.m = 0;
        self.d = 0;
        self.range = 0;
        self.range_list = [];
        self.p_value = 0;
        self.f_obs = [];
        self.f_exp = [];
        self.x_means = []
        
        self.data = [];
        file_path = os.path.join(os.path.dirname(__file__),'..', 'data', self.file_name)
        with open(file_path, encoding='utf-8', newline='') as f:
            reader = csv.DictReader(f)
            for row in reader:
                self.data.append(int(row.get(self.name)))

        self.range = math.ceil(1 + 3.322 * math.log10(len(self.data)))
        if self.range < 7 :
            self.range = 7

    def Counting(self):
        self.m = sum(self.data) / len(self.data)
        
        for i in range(len(self.data)):
            self.d = self.d + (self.data[i] - self.m) ** 2

        self.d = ( self.d/(len(self.data) - 1) ) ** 0.5
        
        step = (max(self.data) - min(self.data)) / self.range

        self.range_list.append(min(self.data))
        for i in range(self.range-1):
            self.range_list.append(self.range_list[i] + step)
        self.range_list.append(max(self.data))

        flag = 0
        for i in range(self.range):
            obs =  0
            for j in range(len(self.data)):

                if flag == 0:
                    if self.range_list[i+1] >= self.data[j] and self.data[j] >= self.range_list[i]:
                        obs += 1
                else:
                    if self.range_list[i+1] >= self.data[j] and self.data[j] > self.range_list[i]:
                        obs += 1
            flag = 1
            self.f_obs.append(obs)
        
        exp = len(self.data) * (IntegrateFun(self.range_list[1], self.m, self.d) - 0)
        self.f_exp.append(exp)

        for i in range(2, len(self.range_list)-1):
            exp = len(self.data) * (IntegrateFun(self.range_list[i], self.m, self.d) - IntegrateFun(self.range_list[i-1], self.m, self.d))
            self.f_exp.append(exp)

        exp = len(self.data) * (1 - IntegrateFun(self.range_list[len(self.range_list)-2], self.m, self.d))
        self.f_exp.append(exp)

        #for i in range(len(self.f_exp)):
        #    self.f_exp[i] *= np.sum(self.f_obs) / np.sum(self.f_exp)
        
        #sum_exp = sum(self.f_exp)
        #sum_obs = sum(self.f_obs)


        self.p_value = stats.chisquare(self.f_obs, self.f_exp)
        #print(self.p_value[1])

    def PrintSolv(self):
        self.Counting();

        for i in range(self.range):
            self.x_means.append(i)

        plt.figure(self.name + " " + self.file_name)
        plt.bar(self.x_means, self.f_obs, label="f_obs")
        plt.plot(self.x_means, self.f_exp,label="f_exp", linewidth=2.0, color = '#FF8C00')  
        plt.legend()
        plt.show()

        print(f"\n__________________{self.name} {self.file_name}______________________\n")
        print(f"t = {self.p_value[0]} ; p_value = {self.p_value[1]}\n")

        if (self.p_value[1] > 0.05):
            print("The data is distributed according to the normal law")
        else:
            print("The data is not distributed according to the normal law")
        print("\n________________________________________\n")


def main():

    cat = PirsCret("category_1", "4136.csv")
    cat_1 = PirsCret("category_1", "all.csv")
    cat.PrintSolv()
    cat_1.PrintSolv()

    cat = PirsCret("category_2", "4136.csv")
    cat_1 = PirsCret("category_2", "all.csv")
    cat.PrintSolv()
    cat_1.PrintSolv()

    cat = PirsCret("category_3", "4136.csv")
    cat_1 = PirsCret("category_3", "all.csv")
    cat.PrintSolv()
    cat_1.PrintSolv()

    cat = PirsCret("category_4", "4136.csv")
    cat_1 = PirsCret("category_4", "all.csv")
    cat.PrintSolv()
    cat_1.PrintSolv()

    cat = PirsCret("category_5", "4136.csv")
    cat_1 = PirsCret("category_5", "all.csv")
    cat.PrintSolv()
    cat_1.PrintSolv()
    

if __name__ == '__main__':
    main()
