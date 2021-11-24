def fibonacciMemo(n, memo = {}):
    if n <= 1:
        memo[n] = n
    else:
        if (n - 1) not in memo.keys():
            memo[n - 1] = fibonacciMemo(n - 1, memo)
            
        if (n - 2) not in memo.keys():
            memo[n - 2] = fibonacciMemo(n - 2, memo)
            
        memo[n] = memo[n - 1] + memo[n - 2]
        
    return memo[n]

val = int(input("Unesite koji element Fibonacci sekvence želite da dobijete: "))
print("Rez je: " + str(fibonacciMemo(val)))

# fib = [1, 1]
# for i in range(1, val - 1):
#     fib.append(fib[i - 1] + fib[i])

# print("Fibonacci sequence:", fib)