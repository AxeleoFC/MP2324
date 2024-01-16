#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank, nprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int data[100];

    if(rank==0){
        std::printf("Total de RANKS: %d\n",nprocs);
        for (int i = 0; i < 100; ++i) {
            data[i]=i;
        }
        for (int i = 0; i < nprocs; ++i) {
            std::printf("Enviando datos de RANK: %d\n",i);
            MPI_Send(data, //datos
                     100, //cantidad
                     MPI_INT, //tipo de dato
                     i, //rank destino
                     0, //TAG
                     MPI_COMM_WORLD //grupo
            );
        }
    }else{
        MPI_Recv(data,//datos
                 100, //
                 MPI_INT, //tipo de dato
                 0, //rank origen
                 0, //TAG
                 MPI_COMM_WORLD, //grupo
                 MPI_STATUS_IGNORE //status
                 );
        std::string  str="";
        for (int i = 0; i < 10; ++i) {
            //std::printf("%d: \n",data[i]);
            str=str+std::to_string(data[i])+",";
        }
        std::printf("Rank_%d datos recibidos===>%s \n",rank,str.c_str());    }
    MPI_Finalize();
}