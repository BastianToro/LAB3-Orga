#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <math.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

__m128 fcargar(float *a, int indice);

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
			case 'f':   {nombre = malloc(strlen(optarg));
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
				    int b[N];
					FILE *fichero1;
					    fichero1 = fopen(nombre,"r");
					    if (fichero1 == NULL){
						return 0;
					    }
					    else{
						while(!feof(fichero1)){
						    
						    fscanf(fichero1,"%d",&b[j]);
						    j++;
						}
					    }
					    int c[N];
						int k;
						for(k =0;k<j-1;k++){
							c[k] = b[k];
							printf("valor: %d, de b = %d\n",k,c[k]);
						
						}
					    int t[N];
					    int h;
					    for(h =0;h<j-1;h++){
						    //if(k ==0)b[k] = 0;
						    
						    t[h] = b[h+1];
						    printf("valor: %d, de b = %d\n",h,t[h]);
					            
					    }
						
					    float a[N] __attribute__((aligned(16)));
					    float d[N] __attribute__((aligned(16)));
			
					    for(size_t i = 0; i < N; i++){
							a[i] = c[i]%120 +1;
							
						}
					     for(size_t i = 0; i < N-1; i++){
							d[i] = t[i]%120 +1;
							
						}
					    __m128 valor_xor;
					    __m128 v_carga1;
					    __m128 v_carga2;
					    __m128 sumatoria;

						sumatoria[0] = 0.0;
					    sumatoria[1] = 0.0;
					    sumatoria[2] = 0.0;
					    sumatoria[3] = 0.0;
					    
					    for (size_t i =0;i <N;i=i+4){
						if((N-i)<4){
							int g;
							for(g=0;g<(N-i);g++){
								sumatoria[g] = sumatoria[g] + pow(a[i+g],b[i+g]);
						    	} 
						}
						else{
							v_carga1 = _mm_load_ps(&a[i]);
							v_carga2 = _mm_load_ps(&d[i]);
							valor_xor = _mm_xor_ps(v_carga1,v_carga2);
							sumatoria = _mm_add_ps(sumatoria,valor_xor);
						}
					}
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
