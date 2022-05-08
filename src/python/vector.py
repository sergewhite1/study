# vector input and mult demo

def vector_input(name):
    ret = tuple(float(x.strip()) for x in input(name).split(','))
    return ret

def vector_mult(v, k):
    L = []
    for x in v:
        L.append(k * x)
    return tuple(L)

print('vector input and mult demo')
x = vector_input('Enter vector: ')
k = float(input('Enter coefficient: '))

x2 = vector_mult(x, k)

print('x2=', x2)
