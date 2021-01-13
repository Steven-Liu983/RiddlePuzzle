/* C Program for the Number Riddle Puzzle Game
1. This game consists of a frame of numbered square tiles in a random order, with one tile missing.
The missing tile makes the tiles’ movement on the frame possible.
2. The player should move the tiles in order by making sliding moves that use the empty space until
the numbers are in the correct order, and the empty space is located on the bottom right corner.
Programmer: Steven Liu
Date: July 18, 2020 */

#include <stdio.h>  // C Standard Library for input/output functions
#include <stdlib.h> // Functions involving memory allocation, process control, conversions, etc.
#include <time.h>  // Contains time and date function declarations to provide standardized access to time/date manipulation and formatting
#include <math.h>  // A set of functions to perform mathematical operations

#define randrange(N) rand()/(RAND_MAX/(N)+1)

void inputArray(int ** table, int row, int col);    // A function to populate a 2D array with random values in a specific range
void printTable(int ** table, int row, int col);    // A function to printout the element of a 2D array
int checkValue(int ** table, int row, int col, int answer); // A function to search a value inside a 2D array and return the result
int checkMove(int ** table, int row, int col, int answer);  // A function to check the validity of a movement depending on the move
void swap(int ** table, int row, int col, int answer);      // A function to swap two elements of a 2D array
int sorted(int ** table, int row, int col);         // A function to check if all the numbers are sorted in ascending order

int main() {
    srand(time(0)); // Make use of the computer's internal clock to control the choice of the seed
    puts("Welcome to play Number Riddle Puzzle Game!!!");	 // Show a welcome message to the player

    do {
        int m, n, ** mat;     // Variables for number of rows and columns, as well as a pointer for 2D array
        int answer, flag1, flag2, counter = 0;  // Variables for getting the answers, check the validity of moves, and count the moves
    
        do {
            printf("Enter the number of rows (3-8): ");     // Get the number of rows and columns from the user
            scanf("%d",&m);
    
            printf("Enter the number of columns (3-8): ");
            scanf("%d",&n);
        } while (m<3||m>8||n<3||n>8);

        if ((mat = malloc(m * n * sizeof(int))) == NULL) {
            puts("not enough memory");
            exit(-1);
        }

        for (int i = 0; i < m; ++i) {   // Allows the program to dynamically allocate memory as the program is executing
            if ((mat[i] = malloc(m * n * sizeof(int))) == NULL) {
                puts("not enough memory");
                exit(-1);
            }
        }
    
        inputArray (mat, m, n); // Generate random numbers in a specific range and put them on the board
        printTable(mat, m, n);  // Show the board on the screen

        do {
            do {
                printf("(#Move %d), Enter the number you want to move (0 to exit): ", counter);
                scanf("%d",&answer);    // Get the player's move
	
                flag1 = checkValue(mat, m, n, answer);  // Check if the selected number is a number on the board
                flag2 = checkMove(mat, m, n, answer);   // Check if the move is valid
                if (flag1 == 0 || flag2 == 0) {
                    puts("Please enter a valid number.");
                }
            } while (flag1 == 0 || flag2 == 0);

            swap(mat, m, n, answer); // Move the selected number to the empty slot on the board
            printTable(mat, m, n);   // Show the updated board on the screen

            int sort = sorted(mat,m,n); // Check if all the numbers are sorted in ascending order
            if (sort == 1) {
                counter++;  // Count the number of moves
            }
            else {      // Game is over and the player wins
                printf("Excellent!!! You solved it with %d moves.\n",counter);
                break;
            }
        } while (answer != 0);  // Game will continue as long as the answer is not 0
    
		printf("To play again, enter 1: "); // Ask the user to play again or not
		int choice;
		scanf("%d",&choice);
		if (choice != 1) {
			break;
		}
	} while (1);

	printf("Thank you, goodbye!\n");

    return 0;
}

void inputArray (int ** table, int row, int col) {  // This function receives a two-dimensional array of integers
    int a[row*col], arr[row*col], i, k = 0; // Then it generates random unique digits and stores them into the array

    for (i=0; i < row*col; i++) {
      a[i] = i;
    }
    for (i = 0; i < row*col-1; i++) {   // Takes all the possible values and shuffles them
    int c = randrange(row*col-i);       // Analogous to shuffling a deck of cards and dealing off the top
    int t = a[i];
      a[i] = a[i+c];
      a[i+c] = t;
    }
    for (i=0; i < row*col; i++) {       // Store an array of unique numbers as another array
      arr[i] = a[i] + 1;
    }
    for(int a=0;a<row;a++) {
        for(int b=0;b<col;b++) {
            table[a][b] = arr[k++];     // Store the array of random numbers as a two-dimensional array
        }
    }
}

void printTable(int ** table, int row, int col) {
    for(int i=0;i<row;i++) {
        printf("\t |");     // Print the left side of the board
        for(int j=0;j<col;j++) {
            if (table[i][j] == row*col) {
                printf("    |");    // The maximum number would be treated as an empty slot
            }
            else {
                printf(" %2d |", table[i][j]);  // Print all other numbers on the board
            }
        }
        printf("\n");
    }
}

int checkValue(int ** table, int row, int col, int answer) {
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            if (table[i][j] == answer) {    // Check if the selected number is on the board
                return 1;
            }
            else if (answer == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int checkMove(int ** table, int row, int col, int answer) {
    int a,b,c,d;
    
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            if (table[i][j] == answer) {    // Check the position of the selected number
                a=i;
                b=j;
            }
            if (table[i][j] == row*col) {   // Check the position of the empty slot
                c=i;
                d=j;
            }
        }
    }
    if (abs(c - a) == 1 && abs(d - b) == 0) {   // Movement of the selected number can only be horizontal or vertical
        return 1;
    }
    else if (abs(c - a) == 0 && abs(d - b) == 1) {
        return 1;
    }
    else if (answer == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void swap(int ** table, int row, int col, int answer) {
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            if (table[i][j] == row*col) {   // Change the previous empty slot to 0
                table[i][j] = 0;
            }
            if (table[i][j] == answer) {    // Change the selected number to a new empty slot
                table[i][j] = row*col;
            }
            if (table[i][j] == 0) {         // Change the previous empty slot (i.e., 0) to the selected number
                table[i][j] = answer;
            }
        }
    }
}

int sorted(int ** table, int row, int col) {
    int array[row*col], k=0;
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            array[k++] = table[i][j];   // Store all the numbers on the board as a new array
        }
    }
    for(int i=0;i<row*col-1;i++) {      // Check if any number is greater than the one following it
        if (array[i] > array[i+1]) {
            return 1;
        }
    }
    return 0;
}
