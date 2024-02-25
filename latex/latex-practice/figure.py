import os
import msvcrt

def draw_rect(x, y, width, height):
    ind_y = 0
    while ind_y < y:
        print("")
        ind_y += 1

    ind_y = 0
    while ind_y < height:
        s = ""

        ind_x = 0        
        while ind_x < x:
            s += " "
            ind_x += 1
    
        ind_x = 0
        while ind_x < width:
            s += "*"
            ind_x += 1
        
        print(s)
        ind_y += 1

x = 0
y = 0
width = 20
height = 7

is_224 = False

while (True):
    os.system("cls")
    draw_rect(x, y, width, height)

    # Wait for symbol from keyboard
    cb = msvcrt.getch()
    c = int.from_bytes(cb)

    # ESCAPE
    if c == 27: 
        break

    if c == 224:
        is_224 = True
        continue

    if not is_224:
        continue

    is_224 = False

    # UP
    if c == 72:
        y -= 1

        if y < 0:
            y = 0

    # DOWN
    elif c == 80:
        y += 1
    
    # RIGHT
    elif c == 77:
        x += 1

    # LEFT
    elif c == 75:
        x -= 1
        if x < 0:
            x = 0