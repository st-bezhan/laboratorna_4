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
double** multiply(double** array_a, const int rows, const int columns) {
    const int b_rows = init_rows();
    const int b_columns = init_columns();
    double** array_b = initialize_array(b_rows, b_columns);
    fill_array(array_b, b_rows, b_columns);
    validate_array(array_b);
    if (columns == b_rows) {
        double** multiplication_result = initialize_array(rows, b_columns);
        for (unsigned int row = 0; row < rows; row++) {
            for (unsigned int column = 0; column < b_columns; column++) {
                for (unsigned int k = 0; k < columns; k++) {
                    multiplication_result[row][column] += array_a[row][k] * array_b[k][column];
                }
            }
        }

        print_array(multiplication_result, rows, b_columns);
        return multiplication_result;
    } else {
        printf("\nThese matricies cannot be multiplied:"
               " Matrix A[%u*%u] Matrix B[%u*%u]", rows, columns, b_rows, b_columns);
        exit(1);
    }
}

int main(void) {
    int rows = init_rows();
    int columns = init_columns();

    double** array = initialize_array(rows, columns);
    fill_array(array, rows, columns);

    printf("\nOriginal matrix:\n");
    print_array(array, rows, columns);

    double** trans = transpose(array, rows, columns);
    printf("\nTransposed matrix:\n");
    print_array(trans, columns, rows);

    max_min(array, rows, columns);
    multiply(array, rows, columns);

    free_array(array, rows);
    free_array(trans, columns);

    return 0;
}
