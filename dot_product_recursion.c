/*
Calculate the dot product using recursion.
*/
long long int dot_product_recursion(int *vector_a, int *vector_b, long long int vector_length){

    if(vector_length == 0)
       return vector_a[0] * vector_b[0];

    else
        return (vector_a[vector_length] * vector_b[vector_length]) + dot_product_recursion(vector_a, vector_b, vector_length-1);

}
