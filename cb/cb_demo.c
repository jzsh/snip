#include <stdio.h>
#include "show.h"

// call back function
// A call B's function1, when running in function1, function1 will call A's function2
// function2 is known as callback

void PrintNum(int n){
   printf("Test1 is called,the number is %d\n",n);
}

void PrintMessage1(){
   printf("This is the message 1!\n");
}

void PrintMessage2(){
   printf("This is the message 2!\n");
}

void PrintMessage3(){
   printf("This is the message 3!\n");
}

int main()
{
   ShowNum(11111,PrintNum);
   ShowNum(22222,PrintNum);
   ShowMessage(PrintMessage1);
   ShowMessage(PrintMessage2);
   ShowMessage(PrintMessage3);
   return 0;
}
