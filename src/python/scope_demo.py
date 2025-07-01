class A:
    def __init__(self):
        self.x = 10


def proc_a():
    # It is valid working code!
    # Nevertheless variable aObj is declared further down in the text,
    # but during runtime variable aObj exists and it available in this code.
    # Of course it is bad practice.
    aObj.x = 100


aObj = A()

print(f"before proc_a aObj.x={aObj.x}")

proc_a()

print(f"after  proc_a aObj.x={aObj.x}")
