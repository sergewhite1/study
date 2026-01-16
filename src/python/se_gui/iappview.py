# Interface of AppView


class IAppView:
    def get_need_update(self) -> bool:
        raise NotImplementedError

    def get_a_text(self) -> str:
        raise NotImplementedError

    def get_b_text(self) -> str:
        raise NotImplementedError

    def get_c_text(self) -> str:
        raise NotImplementedError

    def get_D_text(self) -> str:
        raise NotImplementedError

    def get_x1_text(self) -> str:
        raise NotImplementedError

    def get_x2_text(self) -> str:
        raise NotImplementedError

    def set_need_update(self, value: bool):
        raise NotImplementedError

    def set_a_text(self, value: str):
        raise NotImplementedError

    def set_b_text(self, value: str):
        raise NotImplementedError

    def set_c_text(self, value: str):
        raise NotImplementedError

    def set_D_text(self, value: str):
        raise NotImplementedError

    def set_x1_text(self, value: str):
        raise NotImplementedError

    def set_x2_text(self, value: str):
        raise NotImplementedError

    def set_handler_calc(self, command):
        raise NotImplementedError
