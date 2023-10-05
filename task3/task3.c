#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int rows;
	int cols;
	int *data;
} matrix;

matrix* createMatrix(int rows, int cols) {
	matrix* m = (matrix*) malloc(sizeof(matrix));
	m->rows = rows;
	m->cols = cols;
	m->data = (int*)malloc(rows * cols * sizeof(int));

	int i;

	for (i = 0; i < rows * cols; i++) {
		m->data[i] = i;
	}

	return m;
}

void deleteMatrix(matrix* m) {
	free(m->data);
	free(m);
}

void matrixInfo(matrix* m) {
	printf("\nRows: %d    Columns: %d\n", m->rows, m->cols);
}

void setElement(matrix* m, int row, int col, int val) {
	m->data[m->cols * row + col] = val;
}

int getElement(matrix* m, int row, int col) {
	return m->data[m->cols * row + col];
}

void printMatrix(matrix* m) {
	int i, j;
	printf("\n");
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			printf("%d ", m->data[m->cols * i + j]);
		}
		printf("\n");
	}
}

matrix* sumMatrix(matrix* m1, matrix* m2, matrix* sum) {
	int row, col;

	for (col = 0; col < m1->cols; col++) {
		for (row = 0; row < m1->rows; row++) {
			sum->data[sum->cols * row + col] = m1->data[m1->cols * row + col] + m2->data[m2->cols * row + col];
		}
	}

	return sum;
}

matrix* subtractionMatrix(matrix* m1, matrix* m2, matrix* sum) {
	int row, col;

	for (col = 0; col < m1->cols; col++) {
		for (row = 0; row < m1->rows; row++) {
			sum->data[sum->cols * row + col] = m1->data[m1->cols * row + col] - m2->data[m2->cols * row + col];
		}
	}

	return sum;
}

matrix* multyplyByNumber(matrix* m, int val, matrix* out) {
	int row, col;

	for (col = 0; col < m->cols; col++) {
		for (row = 0; row < m->rows; row++) {
			out->data[out->cols * row + col] = m->data[m->cols * row + col] * val;
		}
	}

	return out;
}

void writeToFile(matrix* m) {
	FILE* outfile;

	outfile = fopen("matrix.txt", "wb");
	if (outfile == NULL) {
		printf("\nError opening file\n");
		return;
	}

	int flag = 0;

	flag = fwrite(m, sizeof(matrix), 1, outfile);

	if (flag) {
		printf("\nWritten successfully\n");
	}
	else {
		printf("\nError writing\n");
	}

	fclose(outfile);
}

matrix* readFromFile() {
	FILE* infile;

	infile = fopen("matrix.txt", "wb+");
	if (infile == NULL) {
		printf("\nError opening file to read\n");
		return;
	}
	matrix* m = (matrix*) malloc(sizeof(matrix));

	fread(m, sizeof(matrix), 1, infile);
	printf("%d", m->data[0]);
	printf("\nRead matrix:");
	printMatrix(m);

	return m;
}

int main() {
	matrix* test = createMatrix(3, 3);
	matrix* test2 = createMatrix(3, 3);
	matrix* sum = createMatrix(3, 3);
	matrix* sub = createMatrix(3, 3);
	matrix* multyNum = createMatrix(3, 3);



	int i, j;

	for (i = 0; i < test->rows * test->cols; i++) {
		test->data[i] = i;
		test2->data[i] = i;
	}

	//setElement(test, 0, 0, 100);
	//printf("\nEl: %d", getElement(test, 0, 0));

	printMatrix(test);
	printMatrix(test2);

	sum = sumMatrix(test, test2, sum);

	printMatrix(sum);

	sub = subtractionMatrix(test, test2, sub);

	printMatrix(sub);

	multyNum = multyplyByNumber(test, 3, multyNum);

	printMatrix(multyNum);

	//writeToFile(test);
	//readFromFile();

	return 0;
}