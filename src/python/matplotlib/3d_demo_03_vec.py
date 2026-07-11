# 03. Vectorize approach
# Настоящая векторизация. Функцию npz выкидываем. В NumPy операция "+"
# перегружена для массивов ndarray.
# Для того, чтобы в сигнатуре функции func_z подчеркнуть, что она пригода как
# для работы со скалярами, так и массивами, можно использовать аннотации типов

# Примеры функций, работающих с массивами:
# np.sin
# np.cos
# np.exp
# np.sqrt
# np.log
# np.maximum
# np.where

import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np


def func_z(x: float | np.ndarray,
           y: float | np.ndarray) -> np.ndarray:
    return x + y

# Примеры работы с if


def func_z2(x, y):
    if x > y:
        return x
    else:
        return y


def func_z3(x, y):
    return np.where(x > y, x, y)


def func_z4(x, y):
    return np.maximum(x, y)


X = np.array([1,  2,  3,  4,  5], dtype=np.float64)
Y = np.array([10, 20, 30, 40], dtype=np.float64)

X, Y = np.meshgrid(X, Y)

print("meshgrid result:")

print(f"X.shape={X.shape}")
print(f"X={X}, X.dtype={X.dtype}")

print(f"Y.shape={Y.shape}")
print(f"Y={Y}, Y.dtype={Y.dtype}")

Z = func_z(X, Y)

# vec2 = np.vectorize(func_z2)
# Z = vec2(X, Y)

# Z = func_z3(X, Y)
# Z = func_z4(X, Y)

print(f"Z.shape={Z.shape}")
print(f"Z={Z}, Z.dtype={Z.dtype}")

# Plot the surface
# plt.style.use('_mpl-gallery')
print(f"plt.style.available={plt.style.available}")
print(f"mpl.colormaps={mpl.colormaps}")

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
ax.plot_surface(X, Y, Z, vmin=Z.min() * 2, cmap="rainbow")

# ax.set(xticklabels=[],
#        yticklabels=[],
#        zticklabels=[])

plt.show()
