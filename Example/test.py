from sys import path
path.append(r"C:/Users/u0101727/Documents/Software/CasADi/casadi-windows-py37-v3.5.1-64bit")
import casadi as ca

F = ca.external('F','./testBranching.dll')

in1 = [1,2,3,32] # True case
in2 = [-1,2,3,32] # False case

out1 = F(in1).full()
out2 = F(in2).full()

assert(out1[0][0] == 67)
assert(out2[0][0] == -3)
