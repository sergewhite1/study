#se - Square Education Solver

import math

print('Square Education Solver')

a = float(input('a='))
b = float(input('b='))
c = float(input('c='))

print('a=', a, ' b=', b, 'c=', c)

D = b ** 2 - 4 * a * c

print(f'D={D}')

if D > 0 :
    x1 = (-b - math.sqrt(D)) / (2 * a)
    x2 = (-b + math.sqrt(D)) / (2 * a)
    print('x1=', x1)
    print('x2=', x2)
elif D == 0 :
    x1 = -b / (2 * a)
    print('x1=x2=', x1)
else:
    print('D<0')
