/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4730
    Professor: Walt Ligon
    Semester: Fall2020
    Filename: print-list.c

    Purpose: To print a .dat file to stdout

    Input:  -i <input file>
    
    Output: Contents input file printed to screen
 */

#include "P1.h"

int main(int argc, char **argv)
{
    FILE* fptr;
    char filename_default[] = "default-list-file.dat";
    char *in_file = NULL;
    int temp_data, opt;

    //Parse Inputs
    while((opt = getopt(argc, argv, "i:")) != -1) 
    {
        switch(opt) 
        { 
            case 'i': 
                in_file = strdup(optarg);
                break;
        }
    }

    //If no output file given use default
    if(in_file == NULL)
        in_file = strdup(filename_default);


    if ((fptr = fopen(in_file, "r")) == NULL)
    {
        printf("print-list - Error opening file\n");
        exit(-1);
    }

    //Read 1 int at a time and print to screen until end of file
    while(fread(&temp_data, 1, sizeof(int), fptr) != 0)
    {
        printf("%d\n",temp_data);
    }

    fclose(fptr);
    fptr = NULL;

    free(in_file);
    in_file = NULL;

    return(0);
}