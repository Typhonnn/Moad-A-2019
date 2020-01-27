#include <stdio.h>
#include <stdlib.h>
#include "q2.h"



// Prints two dimensional matrix by rows
void printMatrix(int *matrix, int rows, int columns) {

	for (int i = 0;   i < rows;   i++) {
		for (int j = 0;   j < columns;   j++)
			printf(" %d", *(matrix + i*columns + j));
		printf("\n");
	}
}

// Sort a matrix using "sum of elements in row" criteria
void   sortMatrixRowsBySum ( int *matrix, int rows, int columns) {

}

// Sort a matrix using "number of non zero bits in row" criteria
void   sortMatrixRowsByBits ( int *matrix, int rows, int columns) {

}


int Q2(void) {

	int matrixSum[4][3] = {{10, 20, 30}, {2, 4, 3}, {100, 200, 300}, {50, 60, 70}};

	int matrixBits[4][3] = {{0, 0, 7}, {1, 1, 3}, {7, 7, 7}, {1, 0, 1}};

	// Sort matrixSum by the sum of elements in row
	printf("Before sorting\n");



	printf("After sorting\n");



	printf("\n========\n\n");

	// Sort matrixBits by the sum of non zero bits of all elements in row
	printf("Before sorting\n");



	printf("After sorting\n");



	return EXIT_SUCCESS;
}

