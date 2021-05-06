import matplotlib.pyplot as plt

names = ['O1', 'O2', 'O3', 'Ofast'] 

values = [1.132441875,1.111001800,0.996328000,0.511001001]

plt.xlabel('optimisation level')
plt.ylabel('time(seconds)')
plt.title("Compiler GCC Before parallelisation ")

plt.bar(names, values)
plt.show() 
