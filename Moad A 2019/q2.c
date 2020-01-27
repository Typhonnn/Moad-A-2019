#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q2.h"



// Prints two dimensional matrix by rows
void printMatrix(int *matrix, int rows, int columns) {

	for (int i = 0;   i < rows;   i++) {
		for (int j = 0;   j < columns;   j++)
			printf(" %d", *(matrix + i*columns + j));
		printf("\n");
	}
}

int sumRowNumbers(void* row, int size) {
	int* tempRow = (int*)row;
	int i, sum = 0;
	for ( i = 0; i < size; i++)	{
		sum += tempRow[i];
	}
	return sum;
}

int sumRowBits(void* arr, int size) {
	int* tempRow = (int*)arr;
	int i, j, sum = 0;
	for (i = 0; i < size; i++) {
		int num = tempRow[i];
		for (j = 0; j < 32; j++) {
			sum += num & 1;
			num = num >> 1;
		}
	}
	return sum;
}

int compareRows(const void* row1, const void* row2) {
	Row tempRow1 = *(Row*)row1;
	Row tempRow2 = *(Row*)row2;
	if (tempRow1.key > tempRow2.key) {
		return 1;
	}
	else if (tempRow1.key < tempRow2.key) {
		return -1;
	}
	else {
		return 0;
	}
}

void sortMatrixRows(int* matrix, int rows, int columns, int(*func)(void *, int)) {
	int i, size = columns * rows, size2 = 0;
	int* tempMat = calloc(size, sizeof(int));
	if (tempMat == NULL) {
		return;
	}
	Row* rowList = calloc(rows, sizeof(Row));
	if (rowList == NULL) {
		return;
	}
	for (i = 0; i < rows; i++) {
		rowList[i].rowNum = i;
		size = i * columns;
		rowList[i].key = func(matrix + size, columns);
	}
	qsort(rowList, rows, sizeof(Row), compareRows);
	for (i = 0; i < rows; i++) {
		size = i * columns;
		size2 = rowList[i].rowNum * columns;
		memcpy(tempMat + size, matrix + size2, columns * sizeof(int));
	}
	size = columns * rows;
	memcpy(matrix, tempMat, size * sizeof(int));
	free(tempMat);
}


// Sort a matrix using "sum of elements in row" criteria
void   sortMatrixRowsBySum ( int *matrix, int rows, int columns) {
	sortMatrixRows(matrix, rows, columns, sumRowNumbers);
}

// Sort a matrix using "number of non zero bits in row" criteria
void   sortMatrixRowsByBits ( int *matrix, int rows, int columns) {
	sortMatrixRows(matrix, rows, columns, sumRowBits);
}


int Q2(void) {

	int matrixSum[4][3] = {{10, 20, 30}, {2, 4, 3}, {100, 200, 300}, {50, 60, 70}};

	int matrixBits[4][3] = {{0, 0, 7}, {1, 1, 3}, {7, 7, 7}, {1, 0, 1}};

	// Sort matrixSum by the sum of elements in row
	printf("Before sorting\n");
	printMatrix(matrixSum, 4, 3);

	printf("After sorting\n");
	sortMatrixRowsBySum(&matrixSum[0][0], 4, 3);
	printMatrix(matrixSum, 4, 3);


	printf("\n========\n\n");

	// Sort matrixBits by the sum of non zero bits of all elements in row
	printf("Before sorting\n");
	printMatrix(matrixBits, 4, 3);

	printf("After sorting\n");
	sortMatrixRowsByBits(&matrixBits[0][0], 4, 3);
	printMatrix(matrixBits, 4, 3);

	return EXIT_SUCCESS;
}

