# Lambda

kvadrat = lambda x: x ** 2

def kvadratFunc(x : int) -> int:
    return x ** 2

print(kvadrat(4))
print(kvadratFunc(4))

iife = (lambda y: "Paran" if y % 2 == 0 else "Neparan") (4)
print(iife)

jedanMaliTrik = lambda x: x % 2 == 0 and "Paran" or "Neparan"
print(f'3 je {jedanMaliTrik(3)}')


print("\n\nLazy Evaluation")
# Lazy Evaluation

def metoda() -> int:
    for i in range(1, 100):
        if i % 4 == 0:
            yield i

x = metoda()
for i in range(1, 100 // 4):
    print(next(x), "")