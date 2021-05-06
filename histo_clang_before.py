import matplotlib.pyplot as plt

names = ['O1', 'O2', 'O3', 'Ofast'] 

values = [1.87803920,1.844650595,1.79000012,1.40011222]

plt.xlabel('optimisation level')
plt.ylabel('time(seconds)')
plt.title("Compiler Clang Before parallelisation ")

plt.bar(names, values)
plt.show() 

