# Compose

add = lambda a,b: a+b
sub = lambda a,b: a-b
mul = lambda a,b: a*b
div = lambda a,b: a//b

def compose(*funcs, acc = 0):
    headA, *tail = funcs
    
    if len(tail) >= 2:
        return lambda x, y: compose(*tail)(acc, headA(x, y))
    else:
        [first] = tail
        return lambda x, y: first(acc, headA(x, y))
    
print(compose(add, add, sub, add)(5, 6))