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
	long long unsigned int vector_length = 100000000;
    double start, end;

    //Vetores utilizados
	int *vector_a = malloc(vector_length * sizeof(int));
	assert(vector_a != NULL);
	int *vector_b = malloc(vector_length * sizeof(int));
	assert(vector_b != NULL);

    //Preenchimento dos vetores
	for(long long int i = 0; i < vector_length; ++i){
		vector_a[i] = 1;
		vector_b[i] = 2;
	}

    //--------------------------------------------------------------------------

    //Loop
	FILE *loop_file = fopen("loop.csv","wb");
    fputs("sep=,\nIteração,Tempo\n", loop_file);
    for(long long unsigned int i = 0; i < 100; ++i){
        start = omp_get_wtime();
    	dot_product_loop(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(loop_file, "%I64u, %f\n", i, end-start);
    }
	fclose(loop_file);

    //Pairs
	FILE *pairs_file = fopen("pairs.csv","wb");
    fputs("sep=,\nIteração,Tempo\n", pairs_file);
    for(long long int i = 0; i < 100; ++i){
        start = omp_get_wtime();
    	dot_product_pairs(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(pairs_file, "%I64u, %f\n", i, end-start);
    }
	fclose(pairs_file);

    //Recursion
	FILE *recursion_file = fopen("recursion.csv","wb");
	fputs("sep=,\nIteração,Tempo\n", recursion_file);
    for(long long int i = 0; i < 100; ++i){
        start = omp_get_wtime();
    	dot_product_pairs(vector_a, vector_b, vector_length);
    	end = omp_get_wtime();
        fprintf(recursion_file, "%I64u, %f\n", i, end-start);
    }
	fclose(recursion_file);

	free(vector_a);
	free(vector_b);

	//Vetores utilizados com alinhamento.
	int *vector_a_alligned = _mm_malloc(vector_length * sizeof(int), 64);
	assert(vector_a != NULL);
	int *vector_b_alligned = _mm_malloc(vector_length * sizeof(int), 64);
	assert(vector_b != NULL);

	//Preenchimento dos vetores
	for(long long int i = 0; i < vector_length; ++i){
		vector_a_alligned[i] = 1;
		vector_b_alligned[i] = 2;
	}

    //SIMD
	FILE *simd_file = fopen("simd.csv","wb");
    fputs("sep=,\nIteração,Tempo\n", simd_file);
    for(long long int i = 0; i < 100; ++i){
        start = omp_get_wtime();
    	dot_product_simd(vector_a_alligned, vector_b_alligned, vector_length);
    	end = omp_get_wtime();
        fprintf(simd_file, "%I64u, %f\n", i, end-start);
    }
    fclose(simd_file);

    //parallel
    FILE *parallel_file = fopen("parallel.csv","wb");
    fputs("sep=,\nIteração,Tempo\n", parallel_file);
    for(long long int i = 0; i < 100; ++i){
        start = omp_get_wtime();
    	dot_product_parallel(vector_a_alligned, vector_b_alligned, vector_length);
    	end = omp_get_wtime();
        fprintf(parallel_file, "%I64u, %f\n", i, end-start);
    }
	fclose(parallel_file);

    //SIMD parallel
	FILE *parallel_simd_file = fopen("parallel_simd.csv","wb");
    fputs("sep=,\nIteração,Tempo\n", parallel_simd_file);
    for(long long int i = 0; i < 100; ++i){
        start = omp_get_wtime();
    	dot_product_parallel_simd(vector_a_alligned, vector_b_alligned, vector_length);
    	end = omp_get_wtime();
        fprintf(parallel_simd_file, "%I64u, %f\n", i, end-start);
    }
	fclose(parallel_simd_file);

    _mm_free(vector_a);
	_mm_free(vector_b);

	return 0;
}
