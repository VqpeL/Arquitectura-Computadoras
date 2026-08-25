#include <stdio.h>
#include <stdlib.h>

int main(){
	int a = 0, b = 1, res = 0, tope = 0;
 	printf("Ingrese el tope: ");
	scanf("%d", &tope);
	if(tope == 0){
		printf("Fibonacci: %d.\n", a);	
		}
	else{
		printf("Fibonacci: %d, ", a);
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
