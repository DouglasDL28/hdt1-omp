#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void openmp_hello(void);

int main(int argc, char* argv[]) {
	int thread_count = strtol(argv[1], NULL, 10);

    #pragma omp parallel num_threads(thread_count)
	openmp_hello();

	return 0;
}
/* openmp_hello */
void openmp_hello(void) {
    int t_id = omp_get_thread_num();
    int total_threads = omp_get_num_threads();
    
    printf("TOTAL THREADS: %d\n", total_threads);

    if (t_id % 2 == 0) {
        printf("Par\n");
        printf("Feliz cumpleaños número %d\n", t_id);
    } else {
        printf("Impar\n");
        printf("Saludos del hilo %d\n", t_id);
    }
    
	// printf("Hola mundo\n");

}
