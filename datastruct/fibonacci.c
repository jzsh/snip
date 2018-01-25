#include <stdio.h>

/* very slow */
int Fib(int n)
{
	if(n < 2)
		return 1;
	else
		return Fib(n - 1) + Fib(n - 2);
}
int FibnonRe()
{
	
}
void main()
{
	int n = 10;
	printf("%d\n", Fib(n));
}
