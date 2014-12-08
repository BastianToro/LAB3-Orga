#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <math.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

float largoMin(float a, float b);
__m128 funcion(__m128 v1, __m128 v2);

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
					int j=0;
					 //float a[N] __attribute__((aligned(16)));
					    size_t t[N];
					    FILE *fichero1;
					    fichero1 = fopen(nombre,"r");
					    if (fichero1 == NULL){
						return 0;
					    }
					    else{
						while(!feof(fichero1)){
						    
						    fscanf(fichero1,"%d",&t[j]);
						    j++;
						}
					    }
					    int c[N];
						int k;
						for(k =0;k<j-1;k++){
							c[k] = t[k];
						
						}
					    float a[N] __attribute__((aligned(16)));
						float b[N] __attribute__((aligned(16)));

					    for(size_t i = 0; i < N; i++){
							a[i] = c[i];
							b[i] = c[i];
						}
						


				    /*se toma como n en la sumatoria, el largo menor entre los 2
				    vectores, ya que si uno es mas largo que el otro habrian
				    datos que operarian con datos que no existen*/
				    float largo = (largoMin(sizeof(a),sizeof(b)))/4;

				    __m128 v1;
				    __m128 v2;
				    __m128 sumatoria1;
				    __m128 sumatoria2;

				    for(size_t j=0;j<4;j++){//se inicializan en 0 las variables que contendran
					sumatoria1[j]=0.0;  //la suma temporal de las funciones
					sumatoria2[j]=0.0;
				    }
				    for(size_t j=0;j<largo;j=j+4){
					if((largo/4)>=1){
					    v1 = _mm_load_ps(&a[j]);//se cargan en v1 y v2 los arreglos a[] y b[]
					    v2 = _mm_load_ps(&b[j]);
					    /*se llama a funcion que hace lo matematico. 
					     en sumatoria2 se van calculando los cuadrados de cada termino*/
					    sumatoria1 = _mm_add_ps(sumatoria1,funcion(v1,v2));
					    sumatoria2 = _mm_add_ps(sumatoria2,_mm_mul_ps(v1,v1));
					}
					/*si el arreglo no es multiplo de 4, se calcularan de forma
					escalar los terminos restantes que son 3 o menos*/
					else{
					    for(size_t k=j;k<largo;k++){
						sumatoria1[k] = sumatoria1[k] + a[k] / 2 + sqrt(b[k]);
						sumatoria2[k] = sumatoria2[k] + a[k] * a[k];
					    }
					}
				    }
				    /*se calculan la suma de los 4 valores del vector, que en total conforman
				    el total de la funcion*/
				    float acc = 0.0;
				    float acc2 = 0.0;
				    for(size_t l=0;l<4;l++){
					acc = acc + sumatoria1[l];
					acc2= acc2+ sumatoria2[l];
				    }

				    /*anteriormente se descompuso el problema, se factorizo la resta acc, que
				    se restaba n veces en acc2, en donde n es el largo de acc2*/
				    float resultadoFinal = acc2 - largo*acc;

				    printf("Restulado Final = %f\n",resultadoFinal);


					}
				break;
			case '?': printf("valor no valido\n");
				break;
		}

	}
	free(nombre);

	return 0;
}

__m128 funcion(__m128 v1, __m128 v2){

    __m128 acc;
    __m128 dividirpor2;
    
    acc[0]=0.0;//se inicializan las variables que se usaran como "temporal de suma"
    acc[1]=0.0;
    acc[2]=0.0;
    acc[3]=0.0;
    dividirpor2[0]=0.5;//se llena el vector con 0.5 para poder operar
    dividirpor2[1]=0.5;
    dividirpor2[2]=0.5;
    dividirpor2[3]=0.5;

    //funcion correspondiente a acc.
    acc = _mm_add_ps(acc,_mm_add_ps(_mm_mul_ps(v1,dividirpor2),_mm_sqrt_ps(v2)));
    
    return acc;
}

float largoMin(float a, float b){//ve cual es el largo minimo entre el largo de a[]
    if(a<=b)                    //y el largo de b[]
        return a;
    else
        return b;
}
