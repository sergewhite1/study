import tkinter


def Call():
    msg = tkinter.Label(window, text="You pressed the button")
    msg.place(x = 30, y = 50)
    button["bg"] = "blue"
    button["fg"] = "white"

window = tkinter.Tk()

window.geometry("500x110")
button = tkinter.Button(text="Press me", command=Call)
button.place(x = 30, y = 20, width=120, height=25)

window.mainloop()