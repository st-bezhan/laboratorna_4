#include <float.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int validate_input(const char* formatSpecifier, void* value, char message[]) {
    char input[100];
    printf("%s", message);
    do {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, formatSpecifier, value) == 1) {
            return 1;
        } else {
            printf("\nInvalid input, try again\n");
            printf("%s", message);
            fseek(stdin, 0, SEEK_END); //clears buffer
        }
    } while (1);
}
unsigned int define_action() {
    unsigned int action_variant = 0;
    do {
        printf("\nSelect action:"
           "\n[1] Find minimal and maximal values higher than main diagonal of matrix A"
           "\n[2] Transpose matrix B"
           "\n[3] Multiply matrix A by matrix B"
           "\n[4] Sort elements of A"
           "\n[5] Show sum of A rows and B columns"
           "\n[6] Exit\n");
        validate_input("%u", &action_variant, "");
    } while (action_variant != 1 && action_variant != 2 &&
        action_variant != 3 && action_variant != 4 &&
        action_variant != 5 && action_variant != 6);

    return action_variant;
}
double** initialize_array(const int rows, const int columns) {
    double** array = calloc(rows, sizeof(double*));
    for (unsigned i = 0; i < rows; i++) {
        array[i] = malloc(sizeof(double) * columns);
    }
    return array;
}
void validate_array(double** array) {
    if (array != NULL) {
        return;
    } else {
        printf("\nMemory allocation error!\n");
        exit(1);
    }
}
void fill_array(double** array, const int rows, const int columns) {
    validate_array(array);
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int column = 0; column < columns; column++) {
            double element;
            printf("\nCurrent position: [%u][%u]", row, column);
            validate_input("%lf", &element, "\nInput element at current position:\n");
            array[row][column] = element;
        }
    }
}
void print_array(double** array, const int rows, const int columns) {
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int column = 0; column < columns; column++) {
            printf("[%lf] ", array[row][column]);
        }
        printf("\n");
    }
}
void free_array(double** array, const int rows) {
    for (unsigned int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}
int init_rows() {
    int rows = 0;
    do {
        validate_input("%u", &rows, "\nEnter amount of rows [>0]:\n");
    } while (rows <= 0);

    return rows;
}
int init_columns() {
    int columns = 0;
    do {
        validate_input("%u", &columns, "\nEnter amount of columns [>0]:\n");
    } while (columns <= 0);

    return columns;
}

double** transpose(double** array, const int rows, const int columns) {
    double** transposed_matrix = initialize_array(columns, rows);
    validate_array(transposed_matrix);
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int column = 0; column < columns; column++) {
            transposed_matrix[column][row] = array[row][column];
        }
    }
    return transposed_matrix;
}
void max_min(double** array, const int rows, const int columns) {
    validate_array(array);
    if (rows == columns) {
        double min_value = DBL_MAX;
        double max_value = -DBL_MAX;
        for (int row = 0; row < rows; row++) {
            for (int column = row + 1; column < columns; column++) {
                if (array[row][column] > max_value) {
                    max_value = array[row][column];
                }
                if (array[row][column] < min_value) {
                    min_value = array[row][column];
                }
            }
        }

        printf("\nMax value above the main diagonal: %lf\n", max_value);
        printf("Min value above the main diagonal: %lf\n", min_value);
    } else {
        printf("\nThis matrix doesn't have a main diagonal.\n");
    }
}
double** multiply(double** array_a, const int rows_a, const int columns_a, double** array_b, const int rows_b, const int columns_b) {
    validate_array(array_a);
    validate_array(array_b);
    if (columns_a == rows_b) {
        double** multiplication_result = initialize_array(rows_a, columns_b);
        for (unsigned int row = 0; row < rows_a; row++) {
            for (unsigned int column = 0; column < columns_b; column++) {
                for (unsigned int k = 0; k < columns_a; k++) {
                    multiplication_result[row][column] += array_a[row][k] * array_b[k][column];
                }
            }
        }

        return multiplication_result;
    } else {
        printf("\nThese matricies cannot be multiplied:"
               " Matrix A[%u*%u] Matrix B[%u*%u]", rows_a, columns_a, rows_b, columns_b);
        exit(1);
    }
}

int main(void) {

    int rows_a = init_rows();
    int columns_a = init_columns();
    int rows_b = init_rows();
    int columns_b = init_columns();
    double** array_a = initialize_array(rows_a, columns_a);
    double** array_b = initialize_array(rows_b, columns_b);

    while (1) {
        unsigned int action = define_action();
        switch (action) {
            case 1:
                print_array(array_a, rows_a, columns_a);
                max_min(array_a, rows_a, columns_a);
                break;
            case 2:
                print_array(array_b, rows_b, columns_b);
                double** transposed = transpose(array_b, rows_b, columns_b);
                print_array(transposed, rows_b, columns_b);
                free_array(transposed, rows_b);
                break;
            case 3:
                print_array(array_a, rows_a, columns_a);
                print_array(array_b, rows_b, columns_b);
                double** multiplicated = multiply(array_a, rows_a, columns_a, array_b, rows_b, columns_b);
                print_array(multiplicated, rows_a, columns_b);
                free_array(multiplicated, rows_a);
                break;
            case 6:
                free_array(array_a, rows_a);
                free_array(array_b, rows_b);
                exit(0);
        }
    }

    return 0;
}
