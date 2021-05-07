import matplotlib.pyplot as plt

names = ['O1', 'O2', 'O3', 'Ofast','vect optim'] 

values = [1.685123001,1.620512059,1.560110090,1.160021331,1.084512360]

plt.xlabel('optimisation level')
plt.ylabel('time(seconds)')
plt.title("Compiler Clang after parallelisation ")

plt.bar(names, values)
plt.show() 
