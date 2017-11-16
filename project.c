#include <stdio.h>
#include <string.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void build_cube(char cube[6][3][3]) {
	FILE * fp;
	int i, j;

	fp = fopen("input.txt", "r");

	for(i=0; i<6; i++){
		for(j=0; j<3; j++){
			fscanf(fp, "%c%c%c\n", &cube[i][j][0], &cube[i][j][1], &cube[i][j][2]);
		}
	}

	fclose(fp);
}

void printValue(char val){
	if(val == 'R') fprintf(stdout, "%s%s %c%s ", "\033[7m", RED, val, RED);
	if(val == 'O') fprintf(stdout, "%s%s %c%s ", "\033[7m", CYN, val, CYN);
	if(val == 'B') fprintf(stdout, "%s%s %c%s ", "\033[7m", BLU, val, BLU);
	if(val == 'G') fprintf(stdout, "%s%s %c%s ", "\033[7m", GRN, val, GRN);
	if(val == 'Y') fprintf(stdout, "%s%s %c%s ", "\033[7m", YEL, val, YEL);
	if(val == 'W') fprintf(stdout, "%s%s %c%s ", "\033[7m", WHT, val, WHT);
	printf(RESET);
}

void print_cube(char cube[6][3][3]) {
	int i, j;
	char x;

	for(j=0; j<3; j++){
		printf("         ");
		printValue(cube[0][j][0]);
		printValue(cube[0][j][1]);
		printValue(cube[0][j][2]);
		printf("\n");
	}

	for(j=0; j<3; j++){
		for(i=1; i<5; i++){
			printValue(cube[i][j][0]);
			printValue(cube[i][j][1]);
			printValue(cube[i][j][2]);
		}
		printf("\n");
	}

	for(j=0; j<3; j++){
		printf("         ");
		printValue(cube[5][j][0]);
		printValue(cube[5][j][1]);
		printValue(cube[5][j][2]);
		printf("\n");
	}
	printf("\n");
}

int main() {
	char cube[6][3][3];
	int i, j;

	build_cube(cube);
	print_cube(cube);
}
