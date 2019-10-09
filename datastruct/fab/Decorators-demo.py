import time

def timeit(func):
     def test():
         start = time.clock()
         func()
         end =time.clock()
         print("time used:", end - start)
     return test

@timeit
def sum1():
     sum = 1 + 2
     print (sum)

sum1()
