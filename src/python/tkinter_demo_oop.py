import tkinter as tk
from tkinter import ttk


class SimpleApp:
    def __init__(self, root):
        self.root = root
        self.root.geometry("500x110")
        self.root.title("OOP Tkinter Example")

        self.button = ttk.Button(self.root, text="Press me", command=self.on_button_press)
        self.button.place(x=30, y=20, width=120, height=25)

        # Сообщение создадим заранее, но скроем
        self.message = ttk.Label(self.root, text="You pressed the button")
        self.message.place(x=30, y=50)
        self.message.place_forget()  # Скрываем изначально

    def on_button_press(self):
        self.message.place(x=30, y=50)  # Показываем сообщение
        self.button.configure(style="Pressed.TButton")  # Меняем стиль кнопки


def main():
    root = tk.Tk()

    # Настраиваем стиль для нажатой кнопки
    style = ttk.Style()
    style.configure("Pressed.TButton", background="blue", foreground="white")

    app = SimpleApp(root)
    root.mainloop()


if __name__ == "__main__":
    main()
