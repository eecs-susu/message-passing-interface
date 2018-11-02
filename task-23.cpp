#include <mpi.h>
#include <stdio.h>
#include <string.h>

int calc_chars(char *buff, char c) {
  int cnt = 0;
  for (char *a = buff; *a != '\0'; ++a) {
    cnt += *a == c;
  }
  return cnt;
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int max_buff_size = 1024;
    if (rank == 0) {
      char buff[max_buff_size];
      scanf("%d", &rank);
      scanf("%s", buff);
      MPI_Bcast(buff, max_buff_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    } else {

      char buff[max_buff_size];
      memset(buff, '\0', max_buff_size);
      MPI_Bcast(buff, max_buff_size, MPI_CHAR, 0, MPI_COMM_WORLD);
      char need_char = 'a' + (rank - 1);
      if (need_char <= 'z') {
        printf("From rank %d -> count %c: %d\n", rank, need_char,
               calc_chars(buff, need_char));
      }
    }
  }
  MPI_Finalize();
  return 0;
}
