# Very simple class for ordered dictionary

class ODict:
    def __init__(self):
        self.dict = {}
        self.keys = []

    def __setitem__(self, str, val):
        self.dict[str] = val
        self.keys.append(str)

    def __getitem__(self,str):
        return self.dict[str]
