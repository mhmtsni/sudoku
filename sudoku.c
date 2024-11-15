#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 9
#define SUBGRID_SIZE 3

void print_grid(int grid[SIZE][SIZE]);
bool is_valid(int grid[SIZE][SIZE], int row, int col, int num);
bool generate_sudoku(int grid[SIZE][SIZE]);
int solve_or_count_solutions(int grid[SIZE][SIZE], int row, int col, bool count_only);
bool has_unique_solution(int grid[SIZE][SIZE]);
void remove_numbers(int grid[SIZE][SIZE], int count);
void clear_grid(int grid[SIZE][SIZE]);
void print_usage();

int main(int argc, char *argv[]) {
    srand(time(NULL)+ clock());

    int grid[SIZE][SIZE] = {0};

    if (argc == 4 && strcmp(argv[1], "generate") == 0) {
        int number_of_sudokus = atoi(argv[2]);
        int numbers_to_remove = atoi(argv[3]);
        int count = 0;
        if (number_of_sudokus <= 0 || numbers_to_remove <= 0 || numbers_to_remove >= 81) {
            fprintf(stderr, "Invalid input: Both numbers must be positive integers.\n");
            return 1;
        }

        FILE *file = fopen("sudoku.txt", "w");
        if (!file) {
            fprintf(stderr, "Error opening file for writing.\n");
            return 1;
        }

        int valid_sudoku_count = 0;
        while (valid_sudoku_count < number_of_sudokus) {
            count++;
            clear_grid(grid);
            generate_sudoku(grid);
            int temp_grid[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++)
            {
                for(int j = 0; j < SIZE; j++)
                {
                    temp_grid[i][j] = grid[i][j];
                }
            }
            remove_numbers(grid, numbers_to_remove);
            printf("%i\n", count);
            if (has_unique_solution(grid)) {
                valid_sudoku_count++;
                fprintf(file, "%i. Sudoku\n\n", valid_sudoku_count);
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        fprintf(file, "%i ", grid[i][j]);
                    }
                    fprintf(file, "\n");
                }
                fprintf(file, "\n\n\n");
                fprintf(file, "%i. Solution\n\n", valid_sudoku_count);
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        fprintf(file, "%i ", temp_grid[i][j]);
                    }
                    fprintf(file, "\n");
                }
                fprintf(file, "\n\n\n");
                fflush(file);

            }
        }
        fclose(file);
        printf("Generated %d unique Sudoku puzzles saved to 'sudoku.txt'.\n", valid_sudoku_count);

    } else if (argc == 2) {
        int numbers_to_remove = atoi(argv[1]);
        if (numbers_to_remove <= 0 || numbers_to_remove >= 81) {
            fprintf(stderr, "Invalid number of cells to remove: %i\n", numbers_to_remove);
            return 1;
        }

        int count = 0;
        do {
            clear_grid(grid);
            generate_sudoku(grid);
            remove_numbers(grid, numbers_to_remove);
            count++;
        } while (!has_unique_solution(grid));

        printf("Generated Sudoku:\n");
        print_grid(grid);
        if (solve_or_count_solutions(grid, 0, 0, false)) {
            printf("Solved:\n");
            print_grid(grid);
        } else {
            printf("Not solvable\n");
        }
        printf("Attempts: %i\n", count);

    } else if (argc == 3 && strcmp(argv[1], "solve") == 0) {
        char input[1000];
        strcpy(input, argv[2]);

        int count = 0;
        char *token = strtok(input, " \n");
        while (token != NULL) {
            if (count < SIZE * SIZE) {
                grid[count / SIZE][count % SIZE] = atoi(token);
                count++;
            }
            token = strtok(NULL, " \n");
        }

        if (count != SIZE * SIZE) {
            fprintf(stderr, "Invalid input format: Expected %d values\n", SIZE * SIZE);
            return 1;
        }

        printf("Puzzle:\n");
        print_grid(grid);
        if (solve_or_count_solutions(grid, 0, 0, false)) {
            printf("Solved:\n");
            print_grid(grid);
        } else {
            printf("Not solvable\n");
        }
    } else {
        print_usage();
    }

    return 0;
}


void clear_grid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

void print_grid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0) {
            printf(" ┌───────┬───────┬───────┐\n");
        }
        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0) {
                printf(" │");
            }
            printf(" %i", grid[i][j]);
        }
        printf(" │\n");
    }
    printf(" └───────┴───────┴───────┘\n");
}

bool is_valid(int grid[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }
    int startRow = row - row % SUBGRID_SIZE;
    int startCol = col - col % SUBGRID_SIZE;
    for (int i = 0; i < SUBGRID_SIZE; i++) {
        for (int j = 0; j < SUBGRID_SIZE; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}
void shuffle_numbers(int *arr) {
    for (int i = SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

bool generate_sudoku(int grid[SIZE][SIZE]) {
    int nums[SIZE];
    for (int i = 0; i < SIZE; i++) {
        nums[i] = i + 1;
    }
    
    for (int row = 0; row < SIZE; row++) {
        shuffle_numbers(nums);
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                for (int i = 0; i < SIZE; i++) {
                    if (is_valid(grid, row, col, nums[i])) {
                        grid[row][col] = nums[i];
                        if (generate_sudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = 0; // Backtrack
                    }
                }
                return false; // No valid number found
            }
        }
    }
    return true; // Sudoku is completely filled
}


int solve_or_count_solutions(int grid[SIZE][SIZE], int row, int col, bool count_only) {
    if (row == SIZE - 1 && col == SIZE) return 1; // Solution found

    if (col == SIZE) {
        row++;
        col = 0;
    }

    if (grid[row][col] != 0) {
        // Move to the next cell if it's already filled
        return solve_or_count_solutions(grid, row, col + 1, count_only);
    }

    int total_solutions = 0;

    for (int num = 1; num <= SIZE; num++) {
        if (is_valid(grid, row, col, num)) {
            grid[row][col] = num;

            int result = solve_or_count_solutions(grid, row, col + 1, count_only);
            if (count_only) {
                total_solutions += result;
                if (total_solutions > 1) {
                    return total_solutions; 
                }
            } else if (result == 1) {
                return 1;
            }

            grid[row][col] = 0; // Backtrack
        }
    }

    return count_only ? total_solutions : 0;
}

bool has_unique_solution(int grid[SIZE][SIZE]) {
    return solve_or_count_solutions(grid, 0, 0, true) == 1;
}

void remove_numbers(int grid[SIZE][SIZE], int count) {
    int removed = 0;
    while (removed < count) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            removed++;
        }
    }
}

void print_usage() {
    printf("USAGE:\n");
    printf("[generate] [amount] [numbers_to_remove] - Generate unique puzzles and save to 'sudoku.txt'\n");
    printf("[solve] \"enter 81 numbers for a solution\" - Solve a given Sudoku puzzle\n");
    printf("[numbers_to_remove] - Find a unique Sudoku with given numbers to remove and solve it\n");
}

