#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>


float ecuacion(int *a, int *b,int la);

int main(int argc,char *argv[]){
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

    					int numero,largo=0;
    					if (fichero == NULL){
						return 0;
					}
					 else{
						while(!feof(fichero)){
						    fscanf(fichero,"%d",&numero);
						    largo = largo + 1;
						}
					    }
					    fclose(fichero);

					    int a[largo], j=0;
					    FILE *fichero1;
					    fichero1 = fopen(nombre,"r");
					    if (fichero1 == NULL){
						return 0;
					    }
					    else{
						while(!feof(fichero1)){
						    fscanf(fichero1,"%d",&a[j]);
						    j++;
						}
					    }
					    fclose(fichero1);
					    int c[largo-1];
					    int i;
					    for(i =0;i<j-1;i++){
						    c[i] = a[i];
						    printf("valor: %i, de a = %d\n",i,c[i]);
					    }
					    int b[largo-1];
					    int k;
					    for(k =0;k<j-1;k++){
						    //if(k ==0)b[k] = 0;
						    
						    b[k] = a[k+1];
						    printf("valor: %d, de b = %d\n",k,b[k]);
					            
					    }
					    float resultado;
					    resultado = ecuacion(a,b,largo-1);
					    printf("%f\n",resultado);
				}
				break;

			case '?': printf("valor no valido\n");
				break;
		}

	}
	free(nombre);
	return 0;

}


float ecuacion(int *a, int *b,int la){
    float suma;
    int i;
    for(i = 0; i < la-1; i++){
        suma = suma + (float)(a[i]*b[i]);
	printf("suma: %f , valor de a: %d,valor de b: %d\n",suma,a[i],b[i]);
    }
    return suma;
}
