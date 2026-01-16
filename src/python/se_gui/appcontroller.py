from appmodel import AppModel
from iappview import IAppView


class AppController:
    def __init__(self, model: AppModel, view: IAppView):
        self.model = model
        self.view = view

        self.view.set_handler_calc(self.handler_calc)

    def handler_calc(self, *args):
        try:
            self.model.set_a_from_str(self.view.get_a_text())
            self.model.set_b_from_str(self.view.get_b_text())
            self.model.set_c_from_str(self.view.get_c_text())

            self.model.update()

            self.view.set_D_text(self.model.get_D_str())
            self.view.set_x1_text(self.model.get_x1_str())
            self.view.set_x2_text(self.model.get_x2_str())

        except Exception as e:
            self.view.set_D_text(e)
            self.view.set_x1_text("")
            self.view.set_x2_text("")
