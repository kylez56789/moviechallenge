#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

// Function Definitions
char *realpath(const char *path, char *resolved_path);
int *process_input(FILE* in, int r);
void print_seats(FILE* out, int theater[10][20], int r);
void reserve(int theater[10][20], int r, int *seats);

int main(int argc, char* argv[]) {
    FILE *in, *out;
    int reservations = 0;
    int* seats;
    char outpath[PATH_MAX];
    if (argc != 2) {
        printf("Unable to read input\n");
        return EXIT_FAILURE;
    } else {
        in = fopen(argv[1], "r");
        out = fopen("out.txt", "w");
        printf("%s\n", realpath("out.txt", outpath));
    }
    while(!feof(in)) {  // count reservations
        char ch;
        ch = fgetc(in);
        if(ch == '\n') {
            reservations++;
        }
    }
    reservations++;
    fseek(in, 0, SEEK_SET);
    seats = process_input(in, reservations);
    int theater[10][20];
    reserve(theater, reservations, seats);
    print_seats(out, theater, reservations);
    return EXIT_SUCCESS;
}

int *process_input(FILE *in, int r) {
    int i = 0, j = 0, k = 0;
    char str[100];
    char c[10];
    int *seats = malloc(sizeof(int)*r);
    for (i = 0; i < r; i++) {
        memset(str,'\0',strlen(str));
        memset(c,'\0',strlen(c));
        fgets(str, 100, in);
        j = 0;
        k = 0;
        while (str[j] != ' ') {j++;}
        j++;
        while(str[j] != '\n' && str[j] != '\0') {
            c[k] = str[j];
            j++;
            k++;
        }
        seats[i] = atoi(c);
    }
    return seats;
}

void print_seats(FILE* out, int theater[10][20], int r) {
    char row = 'A';
    int i, j, k, first;
    for (i = 1; i <= r; i++) {
        fprintf(out, "R");
        if (i < 10) {
            fprintf(out, "00%d ", i);
        } else if (i < 100) {
            fprintf(out, "0%d ", i);  
        } else {
            fprintf(out, "%d ", i);
        }
        first = 1;
        for (j = 0; j < 10; j++) {
            for (k = 0; k < 20; k++) {
                if (theater[j][k] == i) {
                    if (first) {
                        fprintf(out, "%c%d", row+j, k+1);
                        first = 0;
                    } else {
                        fprintf(out, ",%c%d", row+j, k+1);
                    }
                }
            }
        }
        if (i != r) {
            fprintf(out, "\n");
        }
    }
}

void reserve(int theater[10][20], int r, int *seats) {
    int i, j, k, x, u, d;
    int needed_seats, seats_left = 200;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 20; j++) {theater[i][j] = 0;}
    }
    for (i = 0; i < r; i++) {
        needed_seats = seats[i];
        if (seats_left < needed_seats) {continue;}
        u = 4; 
        d = 5;
        while(needed_seats > 0) {
            if (u >= 0) {
                x = 0;
                for (k = 0; k < 20; k++) {
                    if (needed_seats <= 0) {break;} // check is all needed seats are met
                    if (theater[u][k] == 0) { // check availability of seats
                        theater[u][k] = i+1;
                        needed_seats--;
                        seats_left--;
                        if (theater[u+1][k] == 0) { // address public safety constraint for rows
                        theater[u+1][k] = -1;
                        seats_left--;
                        }
                        if (u > 0) {
                        theater[u-1][k] = -1;
                        seats_left--;
                        }
                    } else if (theater[u][k] == -1 && theater[u+1][k] == i+1) { // check if seats right below are of the same group
                        theater[u][k] = i+1;
                        needed_seats--;
                        if (theater[u+1][k] == 0) {
                        theater[u+1][k] = -1;
                        seats_left--;
                        }
                        if (u > 0) {
                        theater[u-1][k] = -1;
                        seats_left--;
                        }
                    }
                }
                while(k < 20 && x < 3) {    // address public safety constraint for groups sitting in the same row
                    theater[u][k] = -1;
                    x++;
                    k++;
                    seats_left--;
                }
                u--;
            }
            if (d < 10) {
                x = 0;
                for (k = 0; k < 20; k++) {
                    if (needed_seats <= 0) {break;}
                    if (theater[d][k] == 0) {
                        theater[d][k] = i+1;
                        needed_seats--;
                        seats_left--;
                        if (theater[d-1][k] == 0) {
                        theater[d-1][k] = -1;
                        seats_left--;
                        }
                        if (d < 9) {
                        theater[d+1][k] = -1;
                        seats_left--;
                        }
                    } else if (theater[d][k] == -1 && theater[d-1][k] == i+1) {
                        theater[d][k] = i+1;
                        needed_seats--;
                        if (theater[d-1][k] == 0) {
                        theater[d-1][k] = -1;
                        seats_left--;
                        }
                        if (d < 9) {
                        theater[d+1][k] = -1;
                        seats_left--;
                        }
                    }
                }
                while(k < 20 && x < 3) {
                    theater[d][k] = -1;
                    x++;
                    k++;
                    seats_left--;
                }
                d++;
            }
        }
    }
}
