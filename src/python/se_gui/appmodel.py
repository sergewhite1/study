from solve_square_eq import solve_square_eq


class AppModel:
    def __init__(self):
        self.a_ = 1
        self.b_ = 2
        self.c_ = -3

        self.D_ = 0
        self.x1_ = 0
        self.x2_ = 0

        self.need_update_ = True

        self.update()

    def update(self):
        if self.need_update_:
            self.D_, self.x1_, self.x2_ = solve_square_eq(self.a_,
                                                          self.b_,
                                                          self.c_)
            self.need_update_ = False

    def get_need_update(self):
        return self.need_update_

    def get_a(self):
        return self.a_

    def get_a_str(self):
        return str(self.a_)

    def set_a(self, value):
        if self.a_ != value:
            self.a_ = value
            self.need_update_ = True

    def set_a_from_str(self, s: str):
        val = float(s)
        self.set_a(val)

    def get_b(self):
        return self.b_

    def get_b_str(self):
        return str(self.b_)

    def set_b(self, value):
        if self.b_ != value:
            self.b_ = value
            self.need_update_ = True

    def set_b_from_str(self, s: str):
        val = float(s)
        self.set_b(val)

    def get_c(self):
        return self.c_

    def get_c_str(self):
        return str(self.c_)

    def set_c(self, value):
        if self.c_ != value:
            self.c_ = value
            self.need_update_ = True

    def set_c_from_str(self, s: str):
        val = float(s)
        self.set_c(val)

    def get_D(self):
        return self.D_

    def get_D_str(self):
        return str(self.D_)

    def get_x1(self):
        return self.x1_

    def get_x1_str(self):
        if self.D_ >= 0:
            return str(self.x1_)

        return ""

    def get_x2(self):
        return self.x2_

    def get_x2_str(self):
        if self.D_ >= 0:
            return str(self.x2_)

        return ""
