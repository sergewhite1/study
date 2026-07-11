# 04. Type ArrayLike

import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import numpy.typing as npt


def func_z(x: npt.ArrayLike,
           y: npt.ArrayLike) -> np.ndarray:
    # ArrayLike - всё, что NumPy способен превратить в массив. Например:
    # func_z(1.0, 2.0)
    # func_z([1, 2, 3], [4, 5 6])
    # func_z((1, 2), (3, 4))
    # func_z(np.array[1, 2], np.array[3, 4])

    x = np.asarray(x)
    y = np.asarray(y)

    return x + y


X = np.array([1,  2,  3,  4,  5], dtype=np.float64)
Y = np.array([10, 20, 30, 40], dtype=np.float64)

X, Y = np.meshgrid(X, Y)

print("meshgrid result:")

print(f"X.shape={X.shape}")
print(f"X={X}, X.dtype={X.dtype}")

print(f"Y.shape={Y.shape}")
print(f"Y={Y}, Y.dtype={Y.dtype}")

Z = func_z(X, Y)

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
