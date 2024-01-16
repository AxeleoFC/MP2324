#include <iostream>
#include <mpi.h>

int sumar(int* numeros, int n){
    int suma=0;
    for (int i = 0; i < n; ++i) {
        suma=suma+numeros[i];
    }
    return  suma;
}

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
        for (int rank_id = 1; rank_id < nprocs; ++rank_id) {
            std::printf("Enviando datos de RANK: %d\n",rank_id);
            int inicio=rank_id*25;
            MPI_Send(&data[inicio], 25, MPI_INT,rank_id,0,MPI_COMM_WORLD);
        }

        int suma_ranks[4];
        suma_ranks[0]=sumar(data,25);
        for (int rank_id = 1; rank_id < nprocs; ++rank_id){
            MPI_Recv(&suma_ranks[rank_id],1,MPI_INT,rank_id,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }

        for (int i = 0; i < 4; ++i) {
            std::printf("La suma parcial el Rank %d es de: %d\n", i, suma_ranks[i]);
        }
        int suma_t= sumar(suma_ranks,4);
        std::printf("La suma total es de: %d\n", suma_t);
    }else{
        MPI_Recv(data,25,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        std::string  str="";
        for (int i = 0; i < 10; ++i) {
            //std::printf("%d: \n",data[i])
            str=str+std::to_string(data[i])+",";
        }
        int suma_parcial=sumar(data,25);
        MPI_Send(&suma_parcial,1,MPI_INT,0,0,MPI_COMM_WORLD);
        str=str+"....";
        std::printf("Rank_%d datos recibidos===>%s y la suma es\n",rank,str.c_str());
    }
    MPI_Finalize();
}