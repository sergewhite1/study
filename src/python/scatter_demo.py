import matplotlib.pyplot as plt

X = [10, 20, 30]
Y = [1, 2, 3]

fix, ax = plt.subplots()

ax.scatter(X, Y,
           marker='s',         # square
           # c='red',
           facecolors='none',  # empty inside
           edgecolors='red')

plt.xlabel("(X_n)_2")

plt.show()
