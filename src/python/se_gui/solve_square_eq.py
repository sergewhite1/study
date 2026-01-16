import math


# Solve Square Equation
# Input - coefficients a, b, c
# Output - typle (D, x1, x2)
def solve_square_eq(a, b, c) -> tuple:
    D = b ** 2 - 4 * a * c

    x1 = x2 = 0

    if D >= 0:
        x1 = (-b - math.sqrt(D)) / (2 * a)
        x2 = (-b + math.sqrt(D)) / (2 * a)

    return (D, x1, x2)
