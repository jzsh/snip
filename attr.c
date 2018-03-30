#include<stdio.h> 

void before_main() __attribute__((constructor));
void after_main() __attribute__((destructor));

void before_main() { 
	printf("before main\n"); 
} 

void after_main() { 
   printf("after main\n"); 
} 

int main(int argc, char **argv) { 
   printf("in main\n"); 
   return 0; 
}
