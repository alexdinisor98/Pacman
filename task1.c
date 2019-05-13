#include<stdio.h>

void print_triangle(int N, int c){

		int x=N;

	while (N >= 1){
		//afisare de spatii inainte de caracter
		for(int j = 1; j <= 2* (x-N); j++)
		printf(" ");
	// afisare caracter si spatiile dintre caractere
	for (int i = 1; i < N; i++){
		printf("%c ",c);
	}

	printf("%c",c);
	// se trece la urmatorul rand
	printf("\n");

	N--;
	
	}
}

int main() {

	int N;
	
	char c;
	
	scanf("%d %c",&N,&c);

	print_triangle(N,c);

return 0;

}
