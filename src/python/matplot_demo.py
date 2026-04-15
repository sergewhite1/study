import math
import matplotlib.pyplot as plt


X = []
Y = []

x_begin = 0.0
x_end = 10.0
point_count = 1000

dx = (x_end - x_begin) / point_count

for i in range(point_count):
    x = x_begin + i * dx
    y = math.sin(x)

    X.append(x)
    Y.append(y)

fig, ax = plt.subplots()
ax.plot(X, Y)
plt.show()
