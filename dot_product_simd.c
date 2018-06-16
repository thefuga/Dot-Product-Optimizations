/*
This version calculates the dot product using SIMD instructions.
*/
long long int dot_product_simd(int *vector_a, int *vector_b, long long int vector_length){

    long long int product = 0;

    #pragma vector aligned
	#pragma simd reduction(+ : product)
    for(long long int i = 0; i < vector_length; ++i)
        product += vector_a[i] * vector_b[i];

    return product;
}
