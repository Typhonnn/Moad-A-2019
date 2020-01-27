#ifndef Q2_H_
#define Q2_H_

// Prints two dimensional matrix by rows
void printMatrix(int *matrix, int rows, int columns);

// Sort a matrix using "sum of elements in row" criteria
void   sortMatrixRowsBySum ( int *matrix, int rows, int columns);

// Sort a matrix using "number of non zero bits in row" criteria
void   sortMatrixRowsByBits ( int *matrix, int rows, int columns);


int Q2(void);


#endif /* Q2_H_ */
