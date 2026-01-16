import tkinter as tk
from iappview import IAppView


class AppView(IAppView):
    def __init__(self, window: tk.Tk):
        self.PADX = 4
        self.PADY = 4
        self.TITLE = "Square Equation Solver"

        self.need_update_ = False

        self.window = window

        self.window.title(self.TITLE)
        # self.window.geometry("500x500")

        self.label_title_text = tk.StringVar()
        self.label_title_text.set(self.TITLE)
        self.label_title = tk.Label(self.window,
                                    textvariable=self.label_title_text)
        self.label_title.grid(row=1, column=1, columnspan=2,
                              sticky="W", padx=self.PADX, pady=self.PADY)

        self.label_a_text = tk.StringVar()
        self.label_a_text.set("a")
        self.label_a = tk.Label(self.window, textvariable=self.label_a_text)
        self.label_a.grid(row=2, column=1, padx=self.PADX, pady=self.PADY)

        self.entry_a_text = tk.StringVar()
        self.entry_a = tk.Entry(self.window, textvariable=self.entry_a_text)
        self.entry_a.grid(row=2, column=2, padx=self.PADX, pady=self.PADY)

        self.label_b_text = tk.StringVar()
        self.label_b_text.set("b")
        self.label_b = tk.Label(self.window, textvariable=self.label_b_text)
        self.label_b.grid(row=3, column=1, padx=self.PADX, pady=self.PADY)

        self.entry_b_text = tk.StringVar()
        self.entry_b = tk.Entry(self.window, textvariable=self.entry_b_text)
        self.entry_b.grid(row=3, column=2, padx=self.PADX, pady=self.PADY)

        self.label_c_text = tk.StringVar()
        self.label_c_text.set("c")
        self.label_c = tk.Label(self.window, textvariable=self.label_c_text)
        self.label_c.grid(row=4, column=1, padx=self.PADX, pady=self.PADY)

        self.entry_c_text = tk.StringVar()
        self.entry_c = tk.Entry(self.window, textvariable=self.entry_c_text)
        self.entry_c.grid(row=4, column=2, padx=self.PADX, pady=self.PADY)

        self.button_calc = tk.Button(self.window, text="Calc")
        self.button_calc.grid(row=5, column=1, columnspan=2,
                              sticky="NSEW", padx=self.PADX, pady=self.PADY)

        self.label_D_text = tk.StringVar()
        self.label_D_text.set("D")
        self.label_D = tk.Label(self.window, textvariable=self.label_D_text)
        self.label_D.grid(row=6, column=1, padx=self.PADX, pady=self.PADY)

        self.entry_D_text = tk.StringVar()
        self.entry_D = tk.Entry(self.window, textvariable=self.entry_D_text,
                                state="readonly")
        self.entry_D.grid(row=6, column=2, padx=self.PADX, pady=self.PADY)

        self.label_x1_text = tk.StringVar()
        self.label_x1_text.set("x1")
        self.label_x1 = tk.Label(self.window, textvariable=self.label_x1_text)
        self.label_x1.grid(row=7, column=1, padx=self.PADX, pady=self.PADY)

        self.entry_x1_text = tk.StringVar()
        self.entry_x1 = tk.Entry(self.window, textvariable=self.entry_x1_text,
                                 state="readonly")
        self.entry_x1.grid(row=7, column=2, padx=self.PADX, pady=self.PADY)

        self.label_x2_text = tk.StringVar()
        self.label_x2_text.set("x2")
        self.label_x2 = tk.Label(self.window, textvariable=self.label_x2_text)
        self.label_x2.grid(row=8, column=1, padx=self.PADX, pady=self.PADY)

        self.entry_x2_text = tk.StringVar()
        self.entry_x2 = tk.Entry(self.window, textvariable=self.entry_x2_text,
                                 state="readonly")
        self.entry_x2.grid(row=8, column=2, padx=self.PADX, pady=self.PADY)

    def get_need_update(self):
        return self.need_update_

    def set_need_update(self, value):
        self.need_update_ = value

    def get_a_text(self):
        return self.entry_a_text.get()

    def get_b_text(self):
        return self.entry_b_text.get()

    def get_c_text(self):
        return self.entry_c_text.get()

    def get_D_text(self):
        return self.entry_D.get()

    def get_x1_text(self):
        return self.entry_x1_text.get()

    def get_x2_text(self):
        return self.entry_x2_text.get()

    def set_a_text(self, value):
        self.entry_a_text.set(value)

    def set_b_text(self, value):
        self.entry_b_text.set(value)

    def set_c_text(self, value):
        self.entry_c_text.set(value)

    def set_D_text(self, value):
        self.entry_D_text.set(value)

    def set_x1_text(self, value):
        self.entry_x1_text.set(value)

    def set_x2_text(self, value):
        self.entry_x2_text.set(value)

    def set_handler_calc(self, command):
        self.button_calc.config(command=command)
        self.entry_a_text.trace_add("write", command)
        self.entry_b_text.trace_add("write", command)
        self.entry_c_text.trace_add("write", command)