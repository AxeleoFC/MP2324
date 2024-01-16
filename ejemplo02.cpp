#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank, nprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int data[100];

    if(rank==0){
        for (int i = 0; i < 100; ++i) {
            data[i]=i;
        }
        MPI_Send(data, 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }else if(rank==1){

    }
    MPI_Finalize();
}