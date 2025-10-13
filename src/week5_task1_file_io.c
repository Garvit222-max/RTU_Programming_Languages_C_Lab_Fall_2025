/*
 * week5_task1_file_io.c
 * Task 1: Read and write data from text files
 * Week 5 – Files & Modular Programming
 *
 * Name: [Garvit]
 * Student ID: [241ADB140]
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = NULL;             // Always initialize pointers
    char filename[100] = "data.txt";
    char line[256];
    int lineCount = 0;

    printf("Writing lines to %s...\n", filename);

    /* 1. Open file for writing */
    fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open %s for writing.\n", filename);
        return EXIT_FAILURE;     // More portable than returning 1
    }

    /* 2. Write a few lines of text */
    if (fprintf(fp, "Hello, file I/O in C!\n") < 0 ||
        fprintf(fp, "This is another line.\n") < 0 ||
        fprintf(fp, "File handling is powerful!\n") < 0) {
        fprintf(stderr, "Error: writing to file failed.\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    /* 3. Close the file */
    if (fclose(fp) != 0) {
        fprintf(stderr, "Error: could not close %s after writing.\n", filename);
        return EXIT_FAILURE;
    }

    /* 4. Open the file again for reading */
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open %s for reading.\n", filename);
        return EXIT_FAILURE;
    }

    printf("Reading contents:\n");

    /* 5. Read each line using fgets() */
    while (fgets(line, (int)sizeof(line), fp) != NULL) {
        printf("%s", line);
        lineCount++;
    }

    if (ferror(fp)) {  // Check for read errors
        fprintf(stderr, "Error: reading from %s failed.\n", filename);
        fclose(fp);
        return EXIT_FAILURE;
    }

    /* 6. Close the file after reading */
    if (fclose(fp) != 0) {
        fprintf(stderr, "Error: could not close %s after reading.\n", filename);
        return EXIT_FAILURE;
    }

    printf("\nTotal lines read: %d\n", lineCount);

    return EXIT_SUCCESS;
}

