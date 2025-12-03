#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_functions.h"

// Заполнение массива случайными числами от -50 до 50
void fill_array_random(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 101 - 50; // Генерация числа от -50 до 50
    }
}

// Вывод массива на экран
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Замена всех четных по значению элементов на их квадраты
void process_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) { // Проверка на четность
            arr[i] = arr[i] * arr[i]; // Замена на квадрат
        }
    }
}