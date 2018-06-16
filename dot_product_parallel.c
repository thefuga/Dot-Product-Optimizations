#include <omp.h>

/*
This version calculates the dot product using OpenMP to paralelize the process.
*/
long long int dot_product_parallel(int *vector_a, int *vector_b, long long int vector_length){
    long long int product = 0;

    #pragma omp parallel for reduction(+ : product)

    for(long long int i = 0; i < vector_length; ++i)
        product += vector_a[i] * vector_b[i];

    return product;
}
