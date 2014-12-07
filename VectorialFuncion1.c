#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <math.h>
#include <stdio.h>


#define N 8

__m128 fpow(__m128 base,__m128 exponente);

int main(int argc, char *argv[])
{
    float a[N] __attribute__((aligned(16)));

    // inicializar el arreglo
    for(size_t i = 0; i < N; i++){
        a[i] = i;
    }

    __m128 base;
    __m128 baseConRaiz;
    __m128 sumatoria;
    __m128 resultadofpow;

    sumatoria[0] = 0.0;
    sumatoria[1] = 0.0;
    sumatoria[2] = 0.0;
    sumatoria[3] = 0.0;

    for(size_t i=0; i<N; i=i+4){

        /*se van a ir agarrando de a 4 datos, hasta que ya no se pueda porque
        quedan menos de 4 datos en el archivo de texto. En ese caso entraremos en
        el siguiente IF en donde se realizaran las operaciones dato por dato.*/
        if((N-i)<4){
            int k;
            for(k=0;k<(N-i);k++){
                sumatoria[k] = sumatoria[k] + pow(sqrt(a[i+k]),a[i+k]);
            }
        }
        else{
            base = _mm_load_ps(&a[i]);
            baseConRaiz = _mm_sqrt_ps(base);

            resultadofpow = fpow(baseConRaiz,base);

            sumatoria = _mm_add_ps(sumatoria,resultadofpow);
            

            //se va guardando 
        }   //de a 4 por cada 'i' de la sumatoria en cada ciclo del for.
    }       //Al final del ciclo FOR se suman los 4 indices del arreglo y se obtiene
            //el resultado final.

    //guardo en a[], lo que esta en __m128 acc 
    _mm_store_ps(a,sumatoria);

    float resultado = 0;
    int i;
    for(i=0;i<4;i++){//aqui se suman los 4 indices del arreglo
        resultado = resultado + sumatoria[i];
    }
    printf("resultado = %f\n",resultado);
    return 0;
}

__m128 fpow(__m128 base,__m128 exponente){
    __m128 final;
    int i,j;
    float arregloResultados[4];
    float arrayBase[4];
    float arrayExponente[4];
    float exponenteActual,baseActual,aux=0.0;
    _mm_store_ps (arrayExponente,exponente);
    _mm_store_ps (arrayBase,base);
    for(j=0;j<4;j++){
        exponenteActual = arrayExponente[j];
        baseActual = arrayBase[j];
        aux = 1.0;
        if(exponenteActual==0 || baseActual==0){//raiz de 0 es 0, pero 0 elevado a 0
            arregloResultados[j]=0;             //no existe-> se decide dejarlo como 0.
        }
        else{
            for(i=0;i<exponenteActual;i++){//calculamos la potencia
                aux = aux * baseActual;
            }
            arregloResultados[j]=aux;
        }
    }
    final = _mm_load_ps(&arregloResultados[0]);
    return final;
}
