#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // For Windows API: LoadLibrary, GetProcAddress, FreeLibrary

// Define function pointer types
typedef void (*fill_func_t)(int*, int);
typedef void (*print_func_t)(int*, int);
typedef void (*process_func_t)(int*, int);

typedef void (*fill_matrix_func_t)(int[][6], int, int);
typedef void (*print_matrix_func_t)(int[][6], int, int);
typedef void (*process_matrix_func_t)(int[][6], int, int);

int main() {
    srand(time(NULL));

    int choice;
    HMODULE hLib; // Handle for the loaded library (Windows API)

    printf("Select mode:\n");
    printf("1. Work with array (20 elements)\n");
    printf("2. Work with matrix (5x6)\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Load the array library - Use ANSI string (no L prefix)
        hLib = LoadLibrary("array_lib.dll");
        if (hLib == NULL) {
            fprintf(stderr, "Error loading array_lib.dll.\n");
            return 1;
        }

        // Get function pointers
        fill_func_t fill_array_random_ptr = (fill_func_t)GetProcAddress(hLib, "fill_array_random");
        print_func_t print_array_ptr = (print_func_t)GetProcAddress(hLib, "print_array");
        process_func_t process_array_ptr = (process_func_t)GetProcAddress(hLib, "process_array");

        if (!fill_array_random_ptr || !print_array_ptr || !process_array_ptr) {
            fprintf(stderr, "Error getting function address.\n");
            FreeLibrary(hLib);
            return 1;
        }

        int arr[20];
        printf("\n--- Working with array ---\n");

        // Fill and print original array
        fill_array_random_ptr(arr, 20);
        printf("Original array:\n");
        print_array_ptr(arr, 20);

        // Process array (square even numbers)
        process_array_ptr(arr, 20);
        printf("Array after processing:\n");
        print_array_ptr(arr, 20);

        FreeLibrary(hLib); // Close the library

    }
    else if (choice == 2) {
        // Load the matrix library - Use ANSI string (no L prefix)
        hLib = LoadLibrary("matrix_lib.dll");
        if (hLib == NULL) {
            fprintf(stderr, "Error loading matrix_lib.dll.\n");
            return 1;
        }

        // Get function pointers
        fill_matrix_func_t fill_matrix_random_ptr = (fill_matrix_func_t)GetProcAddress(hLib, "fill_matrix_random");
        print_matrix_func_t print_matrix_ptr = (print_matrix_func_t)GetProcAddress(hLib, "print_matrix");
        process_matrix_func_t process_matrix_ptr = (process_matrix_func_t)GetProcAddress(hLib, "process_matrix");

        if (!fill_matrix_random_ptr || !print_matrix_ptr || !process_matrix_ptr) {
            fprintf(stderr, "Error getting function address.\n");
            FreeLibrary(hLib);
            return 1;
        }

        int matrix[5][6];
        printf("\n--- Working with matrix ---\n");

        // Fill and print original matrix
        fill_matrix_random_ptr(matrix, 5, 6);
        printf("Original matrix:\n");
        print_matrix_ptr(matrix, 5, 6);

        // Process matrix (square even numbers)
        process_matrix_ptr(matrix, 5, 6);
        printf("Matrix after processing:\n");
        print_matrix_ptr(matrix, 5, 6);

        FreeLibrary(hLib); // Close the library

    }
    else {
        printf("Invalid choice!\n");
        return 1;
    }

    return 0;
}