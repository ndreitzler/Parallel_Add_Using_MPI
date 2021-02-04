/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4730
    Professor: Walt Ligon
    Semester: Fall2020
    Filename: parallel-add-list.c

    Purpose: To sum a list of integers from a .dat file using mpi

    Input:  -i <input file>
    
    Output: Size of list
            Sum of list
            Time for each processor to complete
            Max time to complete
 */

#include "P1.h"
#include <mpi.h>
#include "MyMPI.h"

int main(int argc, char **argv)
{
    int size; /*Number of MPI tasks*/
    int rank; /*MPI Task number*/
    int opt; /*Input option*/
    long long int num; /*Number of Ints in input file*/
    long long int partial_sum = 0; /*Partial sum of data*/
    long long int final_sum = 0;
    int i;
    int *in_data; /*Input data from file*/
    double elapsed_time;
    double max_time;
    char filename_default[] = "default-list-file.dat"; /*Default filename*/
    char *in_file = NULL; /*User inputed filename*/
    
    //MPI setup
    MPI_Init(&argc, &argv);
    MPI_Barrier(MPI_COMM_WORLD);
    elapsed_time = -MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

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

    read_block_vector(in_file, (void *)(&in_data), MPI_INT, &num, MPI_COMM_WORLD);

    //print_block_vector((void *) in_data, MPI_INT, num, MPI_COMM_WORLD);

    for(i = 0; i < BLOCK_SIZE(rank, size, num); i++)
    {
        partial_sum += in_data[i];
    }

    MPI_Reduce( (void *)(&partial_sum), (void *)(&final_sum), 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    elapsed_time += MPI_Wtime();

    MPI_Reduce( (void *)(&elapsed_time), (void *)(&max_time), 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    printf("Rank %d total elapsed time: \t%10.6f ms\n", rank, elapsed_time/1000);
    fflush(stdout);

    if(rank == 0)
    {
        printf("Size of list: \t%lld\n", num);
        printf("Final_sum: \t%lld\n", final_sum);
        printf("Max completion time for size %d: \t%10.6f ms\n", size, max_time/1000);
        fflush(stdout);
    }

    free(in_file); in_file = NULL;
    free(in_data); in_data = NULL;

    MPI_Finalize();
    return(0);
}
