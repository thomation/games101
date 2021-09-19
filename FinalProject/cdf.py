# idx=1
# global n=0;
# for n=0:1/1023:1
# function y=f(r)
# global n;
# y=0
# y=1-0.25*exp(-r)-0.75*exp(-r/3)-n
# endfunction
# [r,fval,info]=fsolve(@f, 2)
# x(idx)=r
# idx=idx+1
# endfor

# for i=1:1024
# printf("%df, ", x(i));
# if mod(i,5)==0 printf("\n");
# endif
# endfor
    
from math import exp
from scipy import optimize

def F(r, xi):
    return 1.0 - 0.25 * exp(-r) - 0.75 * exp(-r/3) - xi
  
steps = 1024
x0 = 0
r = 0
R = []
XI= []
for i in range(steps):
    xi = 1.0 * i / steps
    r = optimize.newton(F,x0,args=(xi,))
    x0 = r
    XI.append(xi)
    R.append(r)
 
# print(R)
# print(len(R))
for i in range(steps):
    if i % 5 == 0 :
        print("")
    print(R[i], end = ",")
# print(XI)