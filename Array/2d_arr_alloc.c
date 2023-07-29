/*
 * Write a program to allocate 2d array
 * Memory Allocation using c programming.
 */
#include <stdio.h>
#include <stdlib.h>

#define ROW	3
#define COL	3


int main() {
	int **arr;

	arr = (int **)malloc(ROW * sizeof(int*));

	for (int i = 0; i < COL; i++) {
		arr[i] = (int*)malloc(sizeof(int)); 
	}

	for(int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			arr[i][j] = i * j;
		}
	}

	for(int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}
