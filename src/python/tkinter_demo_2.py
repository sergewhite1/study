import tkinter


def on_button_press(window, button):
    msg = tkinter.Label(window, text="You pressed the button")
    msg.place(x=30, y=50)
    button["bg"] = "blue"
    button["fg"] = "white"


def main():
    window = tkinter.Tk()
    window.geometry("500x110")

    # Используем lambda, чтобы передать аргументы в функцию обратного вызова
    button = tkinter.Button(
        window,
        text="Press me",
        command=lambda: on_button_press(window, button)
    )
    button.place(x=30, y=20, width=120, height=25)

    window.mainloop()


if __name__ == "__main__":
    main()
