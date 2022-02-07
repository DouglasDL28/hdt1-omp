/*----------------------------------------------
 * riemann.c - calculo de area bajo la curva
 *----------------------------------------------
 * Sumas de Riemann para calcular la integral f(x)
 *
 * Date:  2021-09-22
 * 
 * gcc-11 -o ejercicio4 ejercicio4.c -fopenmp
 * ./ejercicio 1 40 4
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define A 1
#define B 40
#define N 10e6
#define THREAD_COUNT 4

double f(double x);     // La funcion a integrar
double trapezoides(double a, double b, int n);

int main(int argc, char* argv[]) {
    double integral;
    double a=A, b=B;
    int thread_count=THREAD_COUNT;
    int n=N;
    double h;

    if(argc > 3) {
        a = strtol(argv[1], NULL, 10);
        b = strtol(argv[2], NULL, 10);
        thread_count = strtol(argv[3], NULL, 10);
    }

    //---- Aproximacion de la integral
    //h = (b-a)/n;
    integral = 0.0;

    #pragma omp parallel num_threads(thread_count) reduction(+ : integral)
    integral += trapezoides(a, b, n);

    printf("thread_count: %d\n", thread_count);
    printf("Con n = %d trapezoides, nuestra aproximacion \n",n);
    printf("de la integral de %f a %f es = %.10f\n", a,b,integral);

    return 0;
}

/*
Estimar la integral mediante sumas de Riemann
Input: a, b, n, h
Output: integral
*/
double trapezoides(double a, double b, int n) {
    double h, x, local_sum;
    double local_a, local_b;
    int i, local_n;
    int thread_ID = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    //---- Ancho de cada trapezoide
    h = (b-a)/n;
    // valores locales del hilo
    local_n = n/thread_count;
    local_a = a + thread_ID * local_n*h;
    local_b = local_a + local_n*h;

    //---- Valor inicial de la integral (valores extremos)
    local_sum = (f(local_a) + f(local_b)) / 2.0;

    for(i = 1; i <= local_n-1; i++) {
        x = local_a + i*h;
        local_sum += f(x);
    }

    local_sum = local_sum * h;

    return local_sum;
}

/*
Funcion a ser integrada. Integral = 21_333.
Input: x
*/
double f(double x) {
    double return_val;

    return_val = x*x;

    return return_val;
}