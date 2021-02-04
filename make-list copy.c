/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4730
    Professor: Walt Ligon
    Semester: Fall2020
    Filename: make-list.c

    Purpose: To create a .dat file of a given number of intergers,
        from -MAXINT to MAXINT

    Input:  -n <number of integers>
            -o <output file>
    
    Output: .dat file with -n integers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAXINT 10

int main(int argc, char **argv)
{
    FILE* fptr;
    char filename_default[] = "default-list-file.dat";
    char *out_file = NULL;
    int num = 100;
    short temp_data;
    int opt, i;

    srand(time(0));

    //Parse Inputs
    while((opt = getopt(argc, argv, "n:o:")) != -1) 
    {
        switch(opt) 
        { 
            case 'n':
                num = atoi(optarg);
                break; 
            case 'o':
                out_file = strdup(optarg);
                break;
        }
    }

    //If no output file given use default
    if(out_file == NULL)
        out_file = strdup(filename_default);


    if ((fptr = fopen(out_file, "w")) == NULL)
    {
        printf("make-list - Error opening file\n");
        exit(-1);
    }

    //Makes the first integer the total number of integers written to the list
    fwrite(&num, 1, sizeof(int), fptr);

    //Write 1 int at a time, n times 
    for(i = 0; i < num; i++)
    {
        temp_data = rand() % MAXINT;
        fwrite(&temp_data, 1, sizeof(short), fptr);
    }

    fclose(fptr);
    fptr = NULL;

    free(out_file);
    out_file = NULL;

    return(0);
}
