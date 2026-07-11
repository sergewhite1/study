# 02. Formal vectorize approach
# Векторизация (не настоящая!). Чисто закос под векторизацию интерфейса ради,
# а циклы то внутри! Т.е. улучшения по производительности практически никакого
# и нет!

import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np


def func_z(x, y):
    return x + y


X = np.array([1,  2,  3,  4,  5], dtype=np.float64)
Y = np.array([10, 20, 30, 40], dtype=np.float64)

X, Y = np.meshgrid(X, Y)

print("meshgrid result:")

print(f"X.shape={X.shape}")
print(f"X={X}, X.dtype={X.dtype}")

print(f"Y.shape={Y.shape}")
print(f"Y={Y}, Y.dtype={Y.dtype}")

vec = np.vectorize(func_z)
Z = vec(X, Y)

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
