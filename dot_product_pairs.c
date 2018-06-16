/*
This version executes 2 instructions per iteration.
*/
long long int dot_product_pairs(int *vector_a, int *vector_b, long long int vector_length){

    long long int product = 0;
    long long int i = 0;

    //In case the vector lenght is odd, calculate the first element product and treat the rest of the vector as if it had an even length
    if((vector_length % 2)!= 0){
        --vector_length;
        product += vector_a[0] * vector_b[0];
        ++i;
    }

    for(i = i; i < vector_length; i+=2){
        product += vector_a[i] * vector_b[i];
        product += vector_a[i+1] * vector_b[i+1];
    }
    return product;
}
