import sys
num = int(sys.argv[1])
print(num)

def fib(n):
    if n == 1 or n == 2:
        return 1
    else:
        return fib(n-1) + fib(n-2)

def fib_loop(n):
    if n == 1 or n == 2:
        return 1
    a=1
    b=1
    for i in range(3,n+1):
        fibSum = a + b
        a = b
        b = fibSum
    return fibSum


print(fib(num))
print(fib_loop(num))
