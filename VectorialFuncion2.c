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
    				    float a[N] __attribute__((aligned(16)));
    
    				    // inicializar el arreglo
    				    for(size_t i = 0; i < N; i++){
    					a[i] = i;
    				    }
    
    				    __m128 v1;
    				    __m128 v2;
    				    __m128 sumatoria;
    				    __m128 resultadoMul;
    
    				    //se inicializan con 0 para poder ir sumando los resultados obtenidos.
    				    sumatoria[0] = 0.0;
    				    sumatoria[1] = 0.0;
    				    sumatoria[2] = 0.0;
    				    sumatoria[3] = 0.0;
    				    for(size_t i=0; i<N; i=i+4){
    					if(((N+1)/(i+1))<=1){
    					    for(int j=0;j<(N-i-1);j++){
    						float aux = 0;
    						v1[j]=a[i+j];
    						v2[j]=a[i+j+1];
    						sumatoria[j]=sumatoria[j]+(v1[j]*v2[j]);
    					    }
    
    					}
    					/*se van a ir agarrando de a 4 datos hasta el final del archivo de texto.
    					En v1 se cargan 4 alementos, desde i hasta i+4. En v2 se carga desde i+1 hasta i+5.*/
    					else{
    					    v1 = fcargar(a,i);
    					    v2 = fcargar(a,i+1);
    
    					    //se multiplican los 2 vectores
    					    resultadoMul = _mm_mul_ps(v1,v2);
    
    					    //se va sumando el resultado en sumatoria, que contiene 4 indices o 4 datos.
    					    sumatoria = _mm_add_ps(sumatoria,resultadoMul);
    					}
    					//se va guardando 
    				       //de a 4 por cada 'i' de la sumatoria en cada ciclo del for.
    				    }       //Al final del ciclo FOR se suman los 4 indices del arreglo y se obtiene
    					    //el resultado final.
    
    				    //guardo en a[], lo que esta en __m128 sumatoria 
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



__m128 fcargar(float *a, int indice){//entra el arreglo de float y el indice desde 
    __m128 final;               // el que se quieren cargar los datos
    int i;
    float arregloResultados[4];
    for(i=0;i<4;i++){//se cargan 4 datos desde el indice pasado por parametro.
        arregloResultados[i]=a[indice+i];
    }
    final = _mm_load_ps(&arregloResultados[0]);//se guarda en final del tipo __m128
    return final;                           //y se retorna el mismo.
}
