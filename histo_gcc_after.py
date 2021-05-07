import matplotlib.pyplot as plt

names = ['O1', 'O2', 'O3', 'Ofast','vect optim'] 

values = [0.951202450,0.900180001,0.760123021,0.22062104,0.119011000]

plt.xlabel('optimisation level')
plt.ylabel('time(seconds)')
plt.title("Compiler GCC after parallelisation ")

plt.bar(names, values)
plt.show() 
