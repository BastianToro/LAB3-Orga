#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <math.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

__m128 fpow(__m128 base,__m128 exponente);

int main(int argc, char *argv[])
{
	FILE *fichero;
	int sgte_opcion;
	char *nombre;
	char *tipo = "f:";
	while(1){
		sgte_opcion = getopt_long(argc,argv,tipo,NULL,NULL);
		if(sgte_opcion == -1)break;
		switch(sgte_opcion){
			case 'f': 	{nombre = malloc(strlen(optarg));
					strcpy(nombre,optarg);	
					fichero = fopen(nombre,"r");
					int numero,N=0;
    					if (fichero == NULL){
						return 0;
					}
					else{
						while(!feof(fichero)){
						    fscanf(fichero,"%d",&numero);
						    N = N + 1;
						}
					 }
					 fclose(fichero);
					 N = N-1;
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
					}
					break;

			case '?': printf("valor no valido\n");
				break;
		}

	}
	free(nombre);

	return 0;
}






__m128 fpow(__m128 base,__m128 exponente){
    __m128 final;
    int i,j;
    float arregloResultados[4];//aqui se guardaran los 4 resultados la funcion elevada
    float arrayBase[4];// aqui se cargaran los 4 datos del vector "base"
    float arrayExponente[4];//aqui se caragaran los 4 datos del vector "exponente"
    float exponenteActual,baseActual,aux=0.0;
    _mm_store_ps (arrayExponente,exponente);//se pasa el vector al arrayExponente.
    _mm_store_ps (arrayBase,base);//se  pasa el vector base al arrayBase.
    for(j=0;j<4;j++){
        exponenteActual = arrayExponente[j];//se obtiene el exponente en la posicion j
        baseActual = arrayBase[j];//se obtiene la base en la  posicion j
        aux = 1.0;
        if(exponenteActual==0 || baseActual==0){//raiz de 0 es 0, pero 0 elevado a 0
            arregloResultados[j]=0;             //no existe-> se decide dejarlo como 0.
        }
        else{
            for(i=0;i<exponenteActual;i++){//calculamos la potencia
                aux = aux * baseActual;
            }
            arregloResultados[j]=aux;//se guarda en array el resultado de la potencia
        }                           //de la posicion j
    }
    final = _mm_load_ps(&arregloResultados[0]);//se guarda en un __m128 el arreglo obtenido
    return final;                           //con la matematica ya hecha
}
