import matplotlib.pyplot as plt

names = ['O1', 'O2', 'O3', 'Ofast'] 

values = [1.98200000,1.861451002,1.795891129,1.550123122]

plt.xlabel('optimisation level')
plt.ylabel('time(seconds)')
plt.title("Intel C++ Compiler Classic Before parallelisation ")

plt.bar(names, values)
plt.show() 
