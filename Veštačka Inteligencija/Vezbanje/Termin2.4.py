# Currying

def dodaj(a, b, c):
    return a + b + c

# I način
curry = lambda a: lambda b: lambda c: dodaj(a, b, c)
print(curry(5)(6)(7))

# II način
def g(x):
    def h(y):
        def i(z):
            return dodaj(x, y, z)
        return i
    return h

curry = g
print(curry(5)(6)(7))


# Uncurry

uncurry = lambda a, b, c: curry(a)(b)(c)
print(uncurry(5,6,7))