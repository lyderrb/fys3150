#! /usr/bin/python
import sys
import numpy as np
from subprocess import call
import matplotlib.pyplot as plt

if len(sys.argv) > 1:
    N = np.asarray([int(i) for i in sys.argv[1:]])
else:
    print "Usage: %s list of N" % sys.argv[0]
    sys.exit(1)

eps = np.zeros(len(N))
s = 0
for N_ in N:
    call(["./main.x", "%d" % N_])  # compute and write data
    data = open("data/v_solve_N_%d.dat" % N_, 'r')
    data = data.read()
    data = data.split("\n")
    v = np.zeros(N_)
    
    

    for i, line in enumerate(data):
        i -= 1
        if i < 1 or line == "": continue
        v[i] = float(line)
    
    x = np.linspace(0,1,N_)
    x_exact = np.linspace(0,1,N_)
    u_exact = x_exact * (np.exp(-10) - 1) - np.exp(-10*x_exact)  + 1
    
    eps[s] =max(np.log10(np.abs((v[1:-1]-u_exact[1:-1])/(u_exact[1:-1]))))
    s+=1

h_ = 1.0/(N-1)
plt.rc('text', usetex=True)
plt.semilogx(h_, eps); #label=r'$\epsilon$');
plt.title('Error estimation')
plt.xlabel(r'$ \log_{10} h$');
plt.ylabel(r'Max value of $\epsilon_i$')
plt.savefig("fig/c.png")
plt.show()
