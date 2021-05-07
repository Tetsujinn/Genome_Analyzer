import matplotlib.pyplot as plt

names = ['O1', 'O2', 'O3', 'Ofast','vect optim'] 


values = [1.77212314,1.640121100,1.550012378,1.245612300,1.070132120]

plt.xlabel('optimisation level')
plt.ylabel('time(seconds)')
plt.title("Intel C++ Compiler Classic after parallelisation ")

plt.bar(names, values)
plt.show() 
