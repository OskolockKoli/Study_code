
from dataclasses import replace
from itertools import count
import numpy as np
from prettytable import PrettyTable
from scipy.stats import f, t


#__________ Task_1 __________________

def GenGeomForm(depth):
    if depth == 1:
        return "p"
    elif depth == 2:
        return "(1-p) * p"
    else:
        return f"(1-p)^{ depth - 1 } * p"

def CountDeomForm(depth, p):
    if depth == 1:
        return p
    else:
        return round(( p * (1 - p) ** (depth - 1) ), 5)

class Task_1():
    def __init__(self, p, n):
        self.p = p
        self.n = n

        self.M = 1/p
        self.D = (1-p) / (p**2)
        self.STD = np.sqrt(1-p) / p
    
    def ShowSolution(self):

        print("_" * 25 + "Task 1 solution" + "_" * 25)

        print("Since there is a sequence of n independent trials,\n in each of which some event can occur with probability p\n and the opposite with probability q, then the task\n satisfies the Bernoulli scheme")
        print("\nSince a random variable has a geometric distribution, then its distribution law is found as follows:")

        table = PrettyTable()
        head = ["X"]
        data = ["Pn"]
        numbers = ["Pn"]
        for i in range(1, self.n + 1):
            head.append(str(i))
            data.append(GenGeomForm(i))
            numbers.append(str(CountDeomForm(i,self.p)))

        table.field_names = head
        table.add_row(data)
        table.add_row(numbers)

        print(table)

        print(f"\n MX = { round(self.M , 5) }\t\tDX = {round(self.D, 5)}\t\tStdX = { round(self.STD, 5) }\n")

#__________ Task_2 __________________

def Get_M(k1, k2, m):
    return ( k1 * m + k2)

def Get_D(k1, d):
    return ( (k1 ** 2) * d )

class Task_2():
    def __init__(self, m, d):
        self.M = m
        self.D = d

    def ShowSolution(self):
        print("_" * 25 + "Task 2 solution" + "_" * 25)

        print("\n\nknowing the following formulas:")
        print("\n M(cX) = c * MX\n M(X+c) = c + MX\n D(cX) = c^2 * DX\n D(X + c) = DX")

        print("\n\nwe get:")
        print(f"\nfor X - 4 : M = { Get_M(1, -4, self.M)}\tD = { Get_D(1, self.D) } ")
        print(f"\nfor X + 6 : M = { Get_M(1, 6, self.M)}\tD = { Get_D(1, self.D) } ")
        print(f"\nfor 3X - 4 : M = { Get_M(3, -4, self.M)}\tD = { Get_D(3, self.D) } ")
        print(f"\nfor 4X + 3 : M = { Get_M(4, 3, self.M)}\tD = { Get_D(4, self.D) } ")

#__________ Task_3 __________________

class Task_3():
    def __init__(self, a, b):
        self.a = a
        self.b = eval(b.replace('a', str(self.a)))

        self.number = eval("b - 1.3 * a".replace('a', str(self.a)).replace('b', str(self.b)))
        

    def ShowSolution(self):
        rez = self.number / ( self.b - self.a )

        print("_" * 25 + "Task 3 solution" + "_" * 25)

        print("\n solution: ( ( a + a / 10 ) - ( b - a / 5 ) ) / ( a - b )")
        print(f"\n solution: {rez}")

#__________ Task_4 __________________

class Task_4():
    def __init__(self, S1, n2):
        self.S1 = S1
        self.S2 = 4.5
        self.n1 = 10
        self.n2 = n2

    def ShowSolution(self):
        Fkp = 0;
        F = 0
        if(self.S1 > self.S2):
            Fkp = f.isf(0.1 , self.n1 - 1, self.n2 - 1)
            
            F = self.S1 / self.S2
        else:
            Fkp = f.isf(0.1 , self.n2 - 1, self.n1 - 1)
            F = self.S2 / self.S1

        print("_" * 25 + "Task 4 solution" + "_" * 25)

        print("\nThis hypothesis is tested using Fisher's F-test")
        print(f"\n\t Fkp = { Fkp }\t\tF = { F }")

        if Fkp > F:
            print("\nWe accept this hypothesis")
        else:
            print("\nWe don't accept this hypothesis")


#__________ Task_5 __________________

class Task_5():
    def __init__(self, data_X, data_Y):
        self.dataX = data_X
        self.dataY = data_Y
        self.dataXexp = []

        self.MX = np.mean(data_X)
        self.MY = np.mean(data_Y)
        self.MXY = 0

        for i in range(len(data_X)):
            self.MXY += ( data_X[i] - self.MX) * (data_Y[i] - self.MY)

        self.StdX = np.std(data_X)
        self.StdY = np.std(data_Y)

        self.b0 = 0
        self.b1 = 0
        self.FunReg = ""

        
        self.F = 0
        self.Fkp = 0
        self.H0 = False

        self.interval = ""
        self.r = 0

    def Counting(self):
        # Y = bo + b1X
        
        r = np.corrcoef(self.dataX, self.dataY)[0][1]
        self.r = r
        skoX = np.std(self.dataX)
        skoY =np.std(self.dataY)
        
        self.b1 = r * skoY / skoX
        self.b0 = self.MY -  self.b1 * self.MX
        self.FunReg = f"Y = { str(round(self.b0, 5)) } + ( {str(round(self.b1, 5))} ) * X "

        dataYexp = []
        SS0 = 0
        SSreg = 0
        SSz = 0
        for i in range(len(self.dataY)):
            dataYexp.append(self.b0 + self.b1 * self.dataX[i])

            SS0 += ( self.dataY[i] - self.MY )**2
            SSreg += ( dataYexp[i] - self.MY )**2
            SSz += (self.dataY[i] - dataYexp[i] ) ** 2

        #print(SS0)
        #print(SSreg + SSz)
        MSr = SSreg
        SSz2 = SSz / (len(self.dataX)-2)

        F = MSr / SSz2
        Fkr = f.ppf(0.95,1,4)

        if F < Fkr:
            self.H0 = True

        self.F = F
        self.Fkp = Fkr




        t_cstd = t.ppf(0.05/2, len(self.dataX)-2)

        kx0 = 0
        for i in range(len(self.dataX)):
            kx0 += ( self.dataX[i] - self.MX) ** 2

        kx0 =  ( 1 / len(self.dataX) ) + ( (self.dataX[3] - self.MX)**2 / kx0 )
         
        k = np.sqrt(SSz2) * np.sqrt( kx0 )
        point = self.b0 + self.dataX[3]* self.b1

        self.interval = f"[ {point - t_cstd * k } ; {point + t_cstd * k } ]"

    def ShowSolution(self):
        
        
        print("_" * 25 + "Task 5 solution" + "_" * 25 + "\n")

        print(self.FunReg)
        

        print(f"\n\tF = { str(round( self.F ,5)) }\t\tFkp = { str(round( self.Fkp ,5)) }\t\tr = { str(round( self.r ,5)) }")
        if self.H0 == True:
            print("the regression equation is significant")
        else:
            print("the regression equation is not significant")

        print(f"\nconfidence interval for Y at X = x4 = { self.dataX[3] }:")
        print(self.interval)

def main():
    p = 0.6
    n = 5
    n1 = Task_1(p, n)
    n1.ShowSolution()
    
    a = 6
    D = 3
    n2 = Task_2(a,D)
    n2.ShowSolution()

    a = 7
    b = "a + 7"
    n3 = Task_3(a, b)
    n3.ShowSolution()

    s1 = 3.6
    n2 = 12
    n4 = Task_4(s1, n2)
    n4.ShowSolution()
    
    X = [10.9 , 12.4 , 12.8 , 12.9 , 13.4 , 13.8]
    Y = [1.4 ,  1.7 ,  1.8 ,    2.1 ,  2.1 ,  2.1]
    n5 = Task_5(X, Y)
    n5.Counting()
    n5.ShowSolution()
   

if __name__ == '__main__':
    main()
