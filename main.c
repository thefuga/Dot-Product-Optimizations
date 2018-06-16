#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>
#include "dot_product_loop.c"
#include "dot_product_pairs.c"
#include "dot_product_recursion.c"
#include "dot_product_simd.c"
#include "dot_product_parallel.c"
#include "dot_product_parallel_simd.c"


int main(){

    //Variáveis p/ cálculo
	long long int vector_length = 10;
    long long int result;
    double start, end;

    //Arquivos para resultados
    FILE *loop_file = fopen("loop.csv","wb");
    FILE *pairs_file = fopen("pairs.csv","wb");
    FILE *simd_file = fopen("simd.csv","wb");
    FILE *parallel_file = fopen("parallel.csv","wb");
    FILE *parallel_simd_file = fopen("parallel_simd.csv","wb");

    //Vetores utilizados
	int *vector_a = _mm_malloc(vector_length * sizeof(double), 64);
	assert(vector_a != NULL);
	int *vector_b = _mm_malloc(vector_length * sizeof(double), 64);
	assert(vector_b != NULL);

    //Preenchimento dos vetores
	for(long long int i = 0; i < vector_length; ++i){
		vector_a[i] = 1;
		vector_b[i] = 2;
	}

    //--------------------------------------------------------------------------

    //Loop
    fputs("sep=,\nIteração,Tempo\n", loop_file);
    for(long long int i = 0; i < 101; ++i){
        start = omp_get_wtime();
    	result = dot_product_loop(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(loop_file, "%ld, %f\n", i, end-start);
        //printf("Loop: \nResult: %ld\nTime: %f\n", result, end - start);
    }


    //Pairs
    fputs("sep=,\nIteração,Tempo\n", pairs_file);
    for(long long int i = 0; i < 101; ++i){
        start = omp_get_wtime();
    	result = dot_product_pairs(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(pairs_file, "%ld, %f\n", i, end-start);
        //printf("Pairs: \nResult: %ld\nTime: %f\n", result, end - start);
    }


    //Recursion
    /*start = omp_get_wtime();
	result = dot_product_recursion(vector_a, vector_b, vector_length-1);
	end = omp_get_wtime();
    printf("Recursion: \nResult: %f\nTime: %f\n", result, end - start);*/

    //SIMD
    fputs("sep=,\nIteração,Tempo\n", simd_file);
    for(long long int i = 0; i < 101; ++i){
        start = omp_get_wtime();
    	result = dot_product_simd(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(simd_file, "%ld, %f\n", i, end-start);
        //printf("SIMD: \nResult: %ld\nTime: %f\n", result, end - start);
    }

    //parallel
    fputs("sep=,\nIteração,Tempo\n", parallel_file);
    for(long long int i = 0; i < 101; ++i){
        start = omp_get_wtime();
    	result = dot_product_parallel(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(parallel_file, "%ld, %f\n", i, end-start);
        //printf("Parallel: \nResult: %ld\nTime: %f\n", result, end - start);
    }

    //SIMD parallel
    fputs("sep=,\nIteração,Tempo\n", parallel_simd_file);
    for(long long int i = 0; i < 101; ++i){
        start = omp_get_wtime();
    	result = dot_product_parallel_simd(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(parallel_simd_file, "%ld, %f\n", i, end-start);
        //printf("Parallel SIMD: \nResult: %ld\nTime: %f\n", result, end - start);
    }

    _mm_free(vector_a);
	_mm_free(vector_b);

    fclose(loop_file);
    fclose(pairs_file);
    fclose(simd_file);
    fclose(parallel_file);
    fclose(parallel_simd_file);

	return 0;
}
