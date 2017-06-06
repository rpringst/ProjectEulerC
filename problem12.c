#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
 * Function: trianglenumber
 * --------------------
 * Computes the n-th triangle number.
 *
 *  n (int): the index of the triangle number in its sequence
 *
 *  returns (int): the triangle number 
 */
int trianglenumber(int n){
    return n * (n + 1) / 2;
}

/*
 * Function: generateprimes
 * --------------------
 * Generates a sequence of prime numbers.
 *
 *  n (int): the index of the final prime to compute
 *
 *  returns (int*): a pointer to an array of prime numbers 
 */
int* generateprimes(int n){
    if (n<3)
        return NULL;
    else{
        int* ptr = (int*) calloc(n, sizeof(int));
        
        *(ptr) = 2;
        *(ptr+1) = 3;
        
        int numberofprimes = 2;
        int i = 3;
        
        while (numberofprimes < n){
            for (int j=2; j*j<=i; j++){
                if (i % j == 0) 
                    break;
                else if (j+1 > sqrt(i)){
                    *(ptr+numberofprimes) = i;
                    numberofprimes++;
                }
            }
            i+=2;
        }
    return ptr;
    }
}

/*
 * Function: factorize
 * --------------------
 *
 *
 *  x (int):
 *  primes (int*):
 *
 *  returns (int*): 
 */
int* factorize(int x, int* primes){
    int n = 1000;
    int* ptr = (int*) calloc(n, sizeof(int));
    
    int factors = 0;
    for (int i = 0; i < n; i++){
        if (factors%1000 == 0){
            n+=1000;
            ptr = (int*) realloc(ptr, n*sizeof(int));
            for (int dummy = factors; dummy < (factors+1000); dummy++){
                *(ptr+dummy) = 0;
            }
        }
        if (*(primes+i) > x){
            return ptr;
        }
        while ((x % *(primes+i)) == 0){
            x/=*(primes+i);
            *(ptr+factors) = *(primes+i);
            factors++;
        }
    }
    return ptr;
}

/*
 * Function: numofdivisors
 * --------------------
 * 
 *
 *  primefactors (int*): 
 *
 *  returns (int): 
 */
int numofdivisors(int* primefactors){
    int divisors = 2;
    
    int i = 0;
    int currentfactor;
    int currentmultiplicity;
    
    while(*(primefactors+i) != 0){
        if (i == 0){
            currentfactor = *primefactors;
            currentmultiplicity = 1;
            i++;
        }
        else{
            if(currentfactor == *(primefactors+i)){
                currentmultiplicity++;
                i++;
            }
            else{
                divisors = divisors * (currentmultiplicity+1);
                currentfactor = *(primefactors+i);
                currentmultiplicity = 1;
                i++;
            }
        }
    }
    
    return divisors;
}

int main(int argc, char **argv){
    static int numberofprimes = 100000;
    
    clock_t begin = clock();
    int* primenumbers = generateprimes(numberofprimes);
    clock_t end = clock();
    
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("Prime Generation Time: %f seconds\n", time_spent);
    
    //int test = 30;
    
    //int* factors = factorize(test, primenumbers);
    
    //int i = 0;
    //while(*(factors+i) != 0){
        //printf("%d\n", *(factors+i));
        //i++;
    //}
    
    //int divisors = numofdivisors(factors);
    //printf("%d\n", divisors);
    
    int n = 3;
    int current = trianglenumber(n);
    int* factors = factorize(current, primenumbers);
    int divisors = numofdivisors(factors);
    
    while(divisors < 500){
        n++;
        current = trianglenumber(n);
        factors = factorize(current, primenumbers);
        divisors = numofdivisors(factors);
    }
    
    printf("triangle number %d has %d divisors", current, divisors);
    
    free(primenumbers);
    free(factors);
    
	return 0;
}
