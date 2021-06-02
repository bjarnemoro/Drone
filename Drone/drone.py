import ctypes

class Foo:
    def __init__(self, c_lib, x):
        self.__c_lib = c_lib
        c_lib.Foo_init.argtypes = [ctypes.c_int]
        c_lib.Foo_init.restype = ctypes.c_void_p
        c_lib.Foo_val.argtypes = [ctypes.c_void_p]
        c_lib.Foo_val.restype = ctypes.c_int
        self.obj = c_lib.Foo_init(x)

    @property
    def val(self):
        return self.__c_lib.Foo_val(self.obj)

class State(ctypes.Structure):
    _fields_ = [
        ("X", ctypes.c_int)]

    def __str__(self):
        return "X: {}".format(self.X)

class Action(ctypes.Structure):
    _fields_ = [
        ("X", ctypes.c_float),
        ("Y", ctypes.c_float),
        ("Z", ctypes.c_float)]

    def __str__(self):
        return "X: {}, Y: {}, Z: {}".format(self.X, self.Y, self.Z)

class SARD(ctypes.Structure):
    _fields_ = [
        ("state", State),
        ("action", Action),
        ("reward", ctypes.c_float),
        ("done", ctypes.c_bool)]

class Environment:
    def __init__(self, c_lib):
        self.__c_lib = c_lib
        c_lib.ENV_init.argtypes = []
        c_lib.ENV_init.restype = ctypes.c_void_p
        c_lib.ENV_step.argtypes = [ctypes.c_void_p]
        c_lib.ENV_step.restype = ctypes.c_void_p

        self.__obj = c_lib.ENV_init()

    def step(self):
        #sard = SARD.from_address(self.__c_lib.ENV_step(self.__obj))
        #state = sard.state
        #print(state)
        #sard = SARD.from_address(self.__c_lib.ENV_step(self.__obj))
        #action = sard.action
        #print(action)
        #sard = SARD.from_address(self.__c_lib.ENV_step(self.__obj))
        #reward = sard.reward
        #print(reward)
        #done = SARD.from_address(self.__c_lib.ENV_step(self.__obj))
        #done = sard.done
        #print(done)

        sard = SARD.from_address(self.__c_lib.ENV_step(self.__obj))
        stateX = sard.state.X
        actionX = sard.action.X
        actionY = sard.action.Y
        actionZ = sard.action.Z
        done = sard.done
        reward = sard.reward

        print(stateX)
        print(actionX)
        print(actionY)
        print(actionZ)
        print(reward)
        print(done)



def main():
    cpp_lib = "C:/Users/bjarn/source/repos/DLL_Test/x64/Debug/DLL_Test.dll"
    c_lib = ctypes.CDLL(cpp_lib)

    env = Environment(c_lib)
    env.step()

if __name__ == "__main__":
    main()