# *args, **kwargs
# arguments, keyword arguments

def func(*args, **kwargs): # ne sme (**b, *a)
    print('args: ', args)
    print('keyword args: ', kwargs)
    
func('Jedan', 'Dva', 'Tri', 'Četiri', peti='Šesti', sedmi='Osmi')

def curry(fun, *args, **kwargs):
    if (len(args) + len(kwargs)) < fun.__code__.co_argcount:
        return (lambda *x, **y: curry(fun, *(args + x), **dict(kwargs, **y)))
    return fun(*args, **kwargs)

def add(x, y, z): 
    return x + y + z

curryVersion = curry(add)

print(curryVersion(5)(6)(7))

def rec(func, *args):
    if len(args) == 2:
        return func(*args)
    a, b, *tail = args
    return rec(func, func(a, b), *tail)

def mul(a, b):
    return a * b

print(rec(mul, 1, 2, 3, 4, 5))