#include <stdio.h>
#include <stdlib.h>

int main(){
	int a = 0, b = 1, res = 0, tope = 0;
 	printf("Ingrese el tope: ");
	scanf("%d", &tope);
	tope -= 2; 
	if(tope <= -2){
		printf("Invalido\n");
		}
	else if(tope == -1){
		printf("Fibonacci: %d.\n", a);	
		}
	else if(tope == 0){
		printf("Fibonacci: %d, %d.\n", a , b);
		}
	else{
		printf("Fibonacci: %d, %d, ", a , b);	
		}
	for(int i = 0; i < tope; i++){
		res = a+b;
		a=b;
		b=res;
		if(i != tope-1){
		printf("%d, ", res);
		}else{
		printf("%d.\n", res);	
			}
		}
	return 0;
}
