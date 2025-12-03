#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_functions.h"

// Заполнение матрицы случайными числами от -50 до 50
void fill_matrix_random(int matrix[][6], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 101 - 50;
        }
    }
}

// Вывод матрицы на экран
void print_matrix(int matrix[][6], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Замена всех четных по значению элементов на их квадраты
void process_matrix(int matrix[][6], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] % 2 == 0) {
                matrix[i][j] = matrix[i][j] * matrix[i][j];
            }
        }
    }
}