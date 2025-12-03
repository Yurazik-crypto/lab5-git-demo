#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// --- УБРАЛИ: #include <windows.h> ---
// --- ДОБАВИЛИ: #include <dlfcn.h> для dlopen, dlsym, dlclose ---
#include <dlfcn.h>

// Define function pointer types (остаётся без изменений)
typedef void (*fill_func_t)(int*, int);
typedef void (*print_func_t)(int*, int);
typedef void (*process_func_t)(int*, int);

typedef void (*fill_matrix_func_t)(int[][6], int, int);
typedef void (*print_matrix_func_t)(int[][6], int, int);
typedef void (*process_matrix_func_t)(int[][6], int, int);

int main() {
    srand(time(NULL));

    int choice;
    // --- ИЗМЕНИЛИ: void* lib; вместо HMODULE hLib; ---
    void* lib;

    printf("Select mode:\n");
    printf("1. Work with array (20 elements)\n");
    printf("2. Work with matrix (5x6)\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // --- ИЗМЕНИЛИ: dlopen вместо LoadLibrary ---
        // Имя библиотеки изменено на .so для Linux
        lib = dlopen("./array_lib.so", RTLD_LAZY);
        if (!lib) {
            // --- ИЗМЕНИЛИ: dlerror() вместо GetLastError() ---
            fprintf(stderr, "Error loading array_lib.so: %s\n", dlerror());
            return 1;
        }

        // --- ИЗМЕНИЛИ: dlsym вместо GetProcAddress ---
        fill_func_t fill_array_random_ptr = (fill_func_t)dlsym(lib, "fill_array_random");
        // Проверим ошибку после dlsym
        char* dlsym_error = dlerror();
        if (dlsym_error != NULL) {
            fprintf(stderr, "Error getting fill_array_random: %s\n", dlsym_error);
            dlclose(lib); // --- ИЗМЕНИЛИ: dlclose вместо FreeLibrary ---
            return 1;
        }

        print_func_t print_array_ptr = (print_func_t)dlsym(lib, "print_array");
        dlsym_error = dlerror();
        if (dlsym_error != NULL) {
            fprintf(stderr, "Error getting print_array: %s\n", dlsym_error);
            dlclose(lib);
            return 1;
        }

        process_func_t process_array_ptr = (process_func_t)dlsym(lib, "process_array");
        dlsym_error = dlerror();
        if (dlsym_error != NULL) {
            fprintf(stderr, "Error getting process_array: %s\n", dlsym_error);
            dlclose(lib);
            return 1;
        }

        // if (!fill_array_random_ptr || !print_array_ptr || !process_array_ptr) { // Это условие больше не работает так же
        //     fprintf(stderr, "Error getting function address.\n");
        //     dlclose(lib); // --- ИЗМЕНИЛИ: dlclose вместо FreeLibrary ---
        //     return 1;
        // }

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

        dlclose(lib); // --- ИЗМЕНИЛИ: dlclose вместо FreeLibrary ---

    }
    else if (choice == 2) {
        // --- ИЗМЕНИЛИ: dlopen вместо LoadLibrary ---
        // Имя библиотеки изменено на .so для Linux
        lib = dlopen("./matrix_lib.so", RTLD_LAZY);
        if (!lib) {
            // --- ИЗМЕНИЛИ: dlerror() вместо GetLastError() ---
            fprintf(stderr, "Error loading matrix_lib.so: %s\n", dlerror());
            return 1;
        }

        // --- ИЗМЕНИЛИ: dlsym вместо GetProcAddress ---
        fill_matrix_func_t fill_matrix_random_ptr = (fill_matrix_func_t)dlsym(lib, "fill_matrix_random");
        char* dlsym_error = dlerror();
        if (dlsym_error != NULL) {
            fprintf(stderr, "Error getting fill_matrix_random: %s\n", dlsym_error);
            dlclose(lib); // --- ИЗМЕНИЛИ: dlclose вместо FreeLibrary ---
            return 1;
        }

        print_matrix_func_t print_matrix_ptr = (print_matrix_func_t)dlsym(lib, "print_matrix");
        dlsym_error = dlerror();
        if (dlsym_error != NULL) {
            fprintf(stderr, "Error getting print_matrix: %s\n", dlsym_error);
            dlclose(lib);
            return 1;
        }

        process_matrix_func_t process_matrix_ptr = (process_matrix_func_t)dlsym(lib, "process_matrix");
        dlsym_error = dlerror();
        if (dlsym_error != NULL) {
            fprintf(stderr, "Error getting process_matrix: %s\n", dlsym_error);
            dlclose(lib); // --- ИЗМЕНИЛИ: dlclose вместо FreeLibrary ---
            return 1;
        }

        // if (!fill_matrix_random_ptr || !print_matrix_ptr || !process_matrix_ptr) { // Это условие больше не работает так же
        //     fprintf(stderr, "Error getting function address.\n");
        //     dlclose(lib); // --- ИЗМЕНИЛИ: dlclose вместо FreeLibrary ---
        //     return 1;
        // }

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

        dlclose(lib); // --- ИЗМЕНИЛИ: dlclose вместо FreeLibrary ---

    }
    else {
        printf("Invalid choice!\n");
        return 1;
    }

    return 0;
}
