from typing import Callable

def kvadratPP(arg: int) -> tuple([int, str]):
    broj = "Broj: " + str(arg)
    return (arg ** 2, broj)

# print(kvadratPP(kvadratPP((2, ""))))
# Ne može da se pozove, jer ne prihvata tuple kao argument

#Rešenje je bind i unit
def unit(x: int) -> tuple([int, str]):
    return (x, "")

def bind(f: Callable[[int], tuple[int, str]], arg: tuple([int, str])) -> tuple([int, str]):
    res = f(arg[0])
    return (res[0], arg[1] + (", " if bool(arg[1]) else "") + res[1])

print(bind(kvadratPP, bind(kvadratPP, bind(kvadratPP, bind(kvadratPP, unit(2))))))


# Ili ako ste ja....
def kvadratPPStef(arg: tuple([int, str])) -> tuple([int, str]):
    arg = (arg[0], arg[1] + (", " if arg[1] else "") + "Broj: " + str(arg[0]))
    return (arg[0] ** 2, arg[1])

print(kvadratPPStef(kvadratPPStef((kvadratPPStef(kvadratPPStef((2, "")))))))