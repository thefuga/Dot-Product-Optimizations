#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

/*
Standard dot product calculation using for loop.
*/
double dot_product_loop(double *vector_a, double *vector_b, long long int vector_length){

    double product = 0;

    for(long long int i = 0; i < vector_length; ++i)
        product += vector_a[i] * vector_b[i];

    return product;
}


/*
Calculate the dot product using recursion.
*/
double dot_product_recursion(double *vector_a, double *vector_b, long long int vector_length){

    if(vector_length == 0)
       return vector_a[0] * vector_b[0];
    else
        return (vector_a[vector_length] * vector_b[vector_length]) + dot_product_recursion(vector_a, vector_b, vector_length-1);

}


/*
This version executes 2 instructions per iteration.
*/
double dot_product_pairs(double *vector_a, double *vector_b, long long int vector_length){

    double product = 0;
    long long int i = 0;

    //In case the vector lenght is odd, calculate the first element product and treat the rest of the vector as if it had an even length
    if((vector_length % 2)!= 0){
        --vector_length;
        product += vector_a[0] * vector_b[0];
        ++i;
    }

    for(i = i; i < vector_length; i+=2)
        product += (vector_a[i] * vector_b[i] ) + (vector_a[i+1] * vector_b[i+1]);

    return product;
}


/*
This version calculates the dot product using SIMD instructions.
*/
double dot_product_simd(double *vector_a, double *vector_b, long long int vector_length){
    double product = 0;

    #pragma vector aligned
	#pragma simd reduction(+ : product)

    for(long long int i = 0; i < vector_length; ++i)
        product += vector_a[i] * vector_b[i];

    return product;
}

/*
This version calculates the dot product using OpenMP to paralelize the process.
*/
double dot_product_parallel(double *vector_a, double *vector_b, long long int vector_length){
    double product = 0;

    #pragma omp parallel for reduction(+ : product)

    for(long long int i = 0; i < vector_length; ++i)
        product += vector_a[i] * vector_b[i];

    return product;
}


/**/
double dot_product_parallel_simd(double *vector_a, double *vector_b, long long int vector_length){
    double product = 0;

    #pragma vector aligned
	#pragma omp parallel for simd reduction(+ : product)

    for(long long int i = 0; i < vector_length; ++i)
        product += vector_a[i] * vector_b[i];

    return product;
}


int main(){

	long long int vector_length = 100000000;
    double result;
    int start, end;

	double *vector_a = _mm_malloc(vector_length * sizeof(double), 64);
	assert(vector_a != NULL);

	double *vector_b = _mm_malloc(vector_length * sizeof(double), 64);
	assert(vector_b != NULL);

	for(long long int i = 0; i < vector_length; i++){
		vector_a[i] = 1;
		vector_b[i] = 1;
	}

    //Loop

    start = omp_get_wtime();
	result = dot_product_loop(vector_a, vector_b, vector_length);
	end = omp_get_wtime();
    printf("Loop: \nResult: %f\nTime: %f\n", result, end - start);

    //Pairs
    start = omp_get_wtime();
	result = dot_product_pairs(vector_a, vector_b, vector_length);
	end = omp_get_wtime();
    printf("Pairs: \nResult: %f\nTime: %f\n", result, end - start);

    //Recursion
    /*start = omp_get_wtime();
	result = dot_product_recursion(vector_a, vector_b, vector_length-1);
	end = omp_get_wtime();
    printf("Recursion: \nResult: %f\nTime: %f\n", result, end - start);*/

    //SIMD
    start = omp_get_wtime();
	result = dot_product_simd(vector_a, vector_b, vector_length);
	end = omp_get_wtime();
    printf("SIMD: \nResult: %f\nTime: %f\n", result, end - start);

    //parallel
    start = omp_get_wtime();
	result = dot_product_parallel(vector_a, vector_b, vector_length);
	end = omp_get_wtime();
    printf("Parallel: \nResult: %f\nTime: %f\n", result, end - start);

    //SIMD parallel
    start = omp_get_wtime();
	result = dot_product_parallel_simd(vector_a, vector_b, vector_length);
	end = omp_get_wtime();
    printf("Parallel SIMD: \nResult: %f\nTime: %f\n", result, end - start);

    _mm_free(vector_a);
	_mm_free(vector_b);

	return 0;
}
