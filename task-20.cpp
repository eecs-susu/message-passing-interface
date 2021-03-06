#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
      int buf = 42;
      MPI_Request request;
      MPI_Isend(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
    } else if (rank == 1) {
      int buf;
      MPI_Request request;
      MPI_Status status;
      MPI_Irecv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
      MPI_Wait(&request, &status);
      printf("Recieved: '%d'\n", buf);
    }
  }
  MPI_Finalize();
  return 0;
}
