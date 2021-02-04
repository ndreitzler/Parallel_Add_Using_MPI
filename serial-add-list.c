/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4730
    Professor: Walt Ligon
    Semester: Fall2020
    Filename: serial-add-list.c

    Purpose: To sum a list of integers from a .dat file

    Input:  -i <input file>
    
    Output: Sum of list
 */

#include "P1.h"

int main(int argc, char **argv)
{
    FILE* fptr;
    char filename_default[] = "default-list-file.dat";
    char *in_file = NULL;
    short temp_data;
    int opt, num;
    long long int sum = 0;
    clock_t clock_cycles;

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

    //If no input file given use default
    if(in_file == NULL)
        in_file = strdup(filename_default);


    if ((fptr = fopen(in_file, "r")) == NULL)
    {
        printf("serial-add-list - Error opening file\n");
        exit(-1);
    }

    //Get total number of intergers in list
    fread(&num, 1, sizeof(int), fptr);

    clock_cycles = -clock();

    //Read 1 int at a time and print to screen until end of file
    while(fread(&temp_data, 1, sizeof(short), fptr) != 0)
    {
        sum += temp_data;
    }

    clock_cycles += clock();

    fclose(fptr);
    fptr = NULL;

    printf("Size of %s: %d\n",in_file, num);
    printf("Sum of %s: %lld\n",in_file, sum);
    printf("Completion Time: %10.6f s\n", ((double)clock_cycles)/CLOCKS_PER_SEC);

    free(in_file);
    in_file = NULL;

    return(0);
}