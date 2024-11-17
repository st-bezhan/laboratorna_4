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
            printf("\nInvalid input, try again");
            printf("%s", message);
            fseek(stdin, 0, SEEK_END); //clears buffer
        }
    } while (1);
}
double** initialize_array(const int rows, const int columns) {
    double **array = calloc(rows, sizeof(double *));
    for (unsigned i = 0; i < rows; i++) {
        array[i] = malloc(sizeof(double) * columns);
    }

    return array;
}
void validate_array(double** array) {
    if (array != NULL && array[0] != NULL) {
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
        printf("\n");
    }

}
void max_min(double** array, const int rows, const int columns) {
    validate_array(array);
    if (rows == columns) {
        double min_value = array[0][1];
        double max_value = array[0][1];
        for (int row = 0; row < rows; row++) {
            for (int column = row + 1; column < columns; column++) {
                if (array[row][column] > max_value) {
                    max_value = array[row][column];
                } else if (array[row][column] < min_value) {
                    min_value = array[row][column];
                }
            }
        }

        printf("\nMax value of elements higher than main diagonal: %lf,"
          " Min value of elements higher than main diagonal: %lf\n", max_value, min_value);
    } else {
        printf("\nThis matrix doesn't have main diagonal");
    }
}

int main(void) {
    int rows = 0;
    int columns = 0;

    do {
        validate_input("%u", &rows, "\nEnter amount of rows [>0]:\n");
    } while (rows <= 0);

    do {
        validate_input("%u", &columns, "\nEnter amount of columns [>0]:\n");
    } while (columns <= 0);

    printf("Rows: %u, columns: %u", rows, columns);
    double** array = initialize_array(rows, columns);
    fill_array(array, rows, columns);

    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int column = 0; column < columns; column++) {
            printf("[%lf]", array[row][column]);
        }
        printf("\n");
    }

    free(array);
    return 0;
}
