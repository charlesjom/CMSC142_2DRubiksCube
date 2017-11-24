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
#define CLOCKWISE 1
#define COUNTER_CLOCKWISE 0
#define TRUE 1
#define FALSE 0

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
	if(val == 'O') fprintf(stdout, "%s%s %c%s ", "\033[7m", MAG, val, MAG);
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

void assign(char src[3], char dest[3]) {
	int i;
	for(i=0; i<3; i++) {
		dest[i] = src[i];
	}
}

void swap(char *a, char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

void rotate_side(char cube[6][3][3], int side, int direction) {
	int i, j;
	int cube_side[3][3];

	// create a copy of that side of the cube
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			cube_side[i][j] = cube[side][i][j];
		}
	}
	
	// rotate based on direction given
	// side only but not the other affected sides
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			if (i!=1 || j!=1) {
				if (direction == CLOCKWISE) cube[side][i][j] = cube_side[2-j][i];
				else cube[side][i][j] = cube_side[j][2-i];
			}
		}
	}
}

int sideSolved(char cube[6][3][3], int side) {
	if ( (cube[side][0][0] == cube[side][1][1]) && (cube[side][0][1] == cube[side][1][1]) &&
		(cube[side][0][2] == cube[side][1][1]) && (cube[side][1][0] == cube[side][1][1]) &&
		(cube[side][1][2] == cube[side][1][1]) && (cube[side][2][0] == cube[side][1][1]) &&
		(cube[side][2][1] == cube[side][1][1]) && (cube[side][2][2] == cube[side][1][1]) ) {
		return TRUE;
	}
	return FALSE;
}

int cubeSolved(char cube[6][3][3]) {
	if ( sideSolved(cube, 0) && sideSolved(cube, 1) && sideSolved(cube, 2) &&
	sideSolved(cube, 3) && sideSolved(cube, 4) && sideSolved(cube, 5) ) {
		return TRUE;
	}
	return FALSE;
}

void rotate_cube(char cube[6][3][3], int side, int clockwise){
	char temp[3];
	int i, a, b;

	rotate_side(cube, side, clockwise);		// rotate side

	// rotate affected row/col of other sides
	if(side == 0 || side == 5) {
		if (side == 0) {
			a = 0;
		} else {
			a = 2;
		}

		assign(cube[1][a], temp);
		if (!clockwise) {
			assign(cube[2][a], cube[1][a]);
			assign(cube[3][a], cube[2][a]);
			assign(cube[4][a], cube[3][a]);
			assign(temp, cube[4][a]);

		} else {
			assign(cube[4][a], cube[1][a]);
			assign(cube[3][a], cube[4][a]);
			assign(cube[2][a], cube[3][a]);
			assign(temp, cube[2][a]);
		}
	}

	if(side == 1) {
		a = 0;
		b = 2;

		for(i=0; i<3; i++)
			temp[i] = cube[0][i][a];

		if(clockwise) {
			for(i=0; i<3; i++) {
				cube[0][i][a] = cube[4][i][b];
				cube[4][i][b] = cube[5][i][a];
				cube[5][i][a] = cube[2][i][a];
				cube[2][i][a] = temp[i];
			}
			swap(&cube[4][0][2], &cube[4][2][2]);
			swap(&cube[0][0][0], &cube[0][2][0]);
		}
		else {
			for(i=0; i<3; i++) {
				cube[0][i][a] = cube[2][i][a];
				cube[2][i][a] = cube[5][i][a];
				cube[5][i][a] = cube[4][i][b];
				cube[4][i][b] = temp[i];
			}
			swap(&cube[4][0][2], &cube[4][2][2]);
			swap(&cube[5][0][0], &cube[5][2][0]);
		}
	}

	if(side == 3) {
		a = 2;
		b = 0;

		for(i=0; i<3; i++)
			temp[i] = cube[0][i][a];

		if(clockwise) {
			for(i=0; i<3; i++) {
				cube[0][i][a] = cube[2][i][a];
				cube[2][i][a] = cube[5][i][a];
				cube[5][i][a] = cube[4][i][b];
				cube[4][i][b] = temp[i];
			}
			swap(&cube[4][0][0], &cube[4][2][0]);
			swap(&cube[5][0][2], &cube[5][2][2]);
		}
		else {
			for(i=0; i<3; i++) {
				cube[0][i][a] = cube[4][i][b];
				cube[4][i][b] = cube[5][i][a];
				cube[5][i][a] = cube[2][i][a];
				cube[2][i][a] = temp[i];
			}
			swap(&cube[4][0][0], &cube[4][2][0]);
			swap(&cube[0][0][2], &cube[0][2][2]);
		}
	}

	if (side == 2) {
		a = 2;
		b = 0;
		assign(cube[0][a], temp);
		if (clockwise) {
			for(i=0; i<3; i++) {
				cube[0][a][i] = cube[1][i][a];
				cube[1][i][a] = cube[5][b][i];
				cube[5][b][i] = cube[3][i][b];
				cube[3][i][b] = temp[i];
			}
			swap(&cube[0][2][0], &cube[0][2][2]);
			swap(&cube[5][0][0], &cube[5][0][2]);
		} else {
			for(i=0; i<3; i++) {
				cube[0][a][i] = cube[3][i][b];
				cube[3][i][b] = cube[5][b][i];
				cube[5][b][i] = cube[1][i][a];
				cube[1][i][a] = temp[i];
			}
			swap(&cube[1][0][2], &cube[1][2][2]);
			swap(&cube[3][0][0], &cube[3][2][0]);
		}
	}

	if (side == 4) {
		a = 0;
		b = 2;
		assign(cube[0][a], temp);
		if (clockwise) {
			for(i=0; i<3; i++) {
				cube[0][a][i] = cube[3][i][b];
				cube[3][i][b] = cube[5][b][i];
				cube[5][b][i] = cube[1][i][a];
				cube[1][i][a] = temp[i];
			}
			swap(&cube[1][0][0], &cube[1][2][0]);
			swap(&cube[3][0][2], &cube[3][2][2]);
		} else {
			for(i=0; i<3; i++) {
				cube[0][a][i] = cube[1][i][a];
				cube[1][i][a] = cube[5][b][i];
				cube[5][b][i] = cube[3][i][b];
				cube[3][i][b] = temp[i];
			}
			swap(&cube[0][0][0], &cube[0][0][2]);
			swap(&cube[5][2][0], &cube[5][2][2]);
		}
	}
}

int main() {
	char cube[6][3][3];
	int i, j;

	build_cube(cube);
	print_cube(cube);
	printf("%d\n", cubeSolved(cube));

	rotate_cube(cube, 3, CLOCKWISE);
	rotate_cube(cube, 1, !CLOCKWISE);
	rotate_cube(cube, 5, CLOCKWISE);
	rotate_cube(cube, 4, !CLOCKWISE);
	rotate_cube(cube, 3, CLOCKWISE);
	print_cube(cube);
	printf("%d\n", cubeSolved(cube));

	rotate_cube(cube, 3, !CLOCKWISE);
	rotate_cube(cube, 4, CLOCKWISE);
	rotate_cube(cube, 5, !CLOCKWISE);
	rotate_cube(cube, 1, CLOCKWISE);
	rotate_cube(cube, 3, !CLOCKWISE);
	print_cube(cube);
	printf("%d\n", cubeSolved(cube));

	rotate_cube(cube, 0, CLOCKWISE);
	rotate_cube(cube, 0, !CLOCKWISE);
	print_cube(cube);
	printf("%d\n", cubeSolved(cube));

	rotate_cube(cube, 2, CLOCKWISE);
	rotate_cube(cube, 2, !CLOCKWISE);
	print_cube(cube);
	printf("%d\n", cubeSolved(cube));
}
