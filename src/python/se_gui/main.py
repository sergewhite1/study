import tkinter as tk
from appmodel import AppModel
from iappview import IAppView
from appview import AppView
from appcontroller import AppController


def display_model(model: AppModel, view: IAppView):
    view.set_a_text(model.get_a_str())
    view.set_b_text(model.get_b_str())
    view.set_c_text(model.get_c_str())
    view.set_D_text(model.get_D_str())
    view.set_x1_text(model.get_x1_str())
    view.set_x2_text(model.get_x2_str())


def main():
    window = tk.Tk()

    model = AppModel()
    view = AppView(window)

    display_model(model, view)

    AppController(model, view)
    window.mainloop()


if __name__ == "__main__":
    main()
