#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPESIZE 1000000
#define MAX_FILE_SIZE 100000  // Choose an appropriate maximum file size
char *pfile;
char *tape;
char *ptape;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("No input file provided.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
		FILE *file=fopen(argv[i], "r");
		if (file == NULL) {
            printf("Error opening the file: %s\n", argv[i]);
            continue; // Skip to the next file if there was an error
        }

        char file_buffer[MAX_FILE_SIZE];

        size_t bytes_read = fread(file_buffer, sizeof(char), MAX_FILE_SIZE, file);
        fclose(file);

        if (bytes_read == 0) {
            printf("Error reading the file: %s\n", argv[i]);
            continue; // Skip to the next file if there was an error
        }

        // Null-terminate the buffer to make it a valid C string
        file_buffer[bytes_read] = '\0';

        pfile = file_buffer;
        tape = (char*)calloc(TAPESIZE, sizeof(char));
        ptape = tape;

        while (*pfile != '\0') {
            switch (*pfile) {
                case '>':
                    ptape++;
                    break;
                case '<':
                    ptape--;
                    break;
                case '+':
                    (*ptape)++;
                    break;
                case '-':
                    (*ptape)--;
                    break;
                case ',':
                    while ((*ptape = getchar()) == '\n');
                    break;
                case '.':
                    printf("%c", *ptape);
                    break;
                case '[':
                    if (*ptape == 0) {
                        int brackets = 1;
                        while (brackets > 0) {
                            pfile++;
                            if (*pfile == '[')
                                brackets++;
                            else if (*pfile == ']')
                                brackets--;
                        }
                    }
                    break;
                case ']':
                    if (*ptape != 0) {
                        int brackets = 1;
                        while (brackets > 0) {
                            pfile--;
                            if (*pfile == ']')
                                brackets++;
                            else if (*pfile == '[')
                                brackets--;
                        }
                    }
                    break;
            }
            pfile++;
        }

        free(tape);
    }

    return 0;
}

