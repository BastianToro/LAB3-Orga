#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

float ecuacion(int *a,int largo);

int main(int argc,char *argv[]){
	FILE *fichero;
	FILE *fichero2;
	int sgte_opcion,numero,largo=0,j=0;
	char *nombre;
	char *tipo = "f:";
	while(1){
		sgte_opcion = getopt_long(argc,argv,tipo,NULL,NULL);
		if(sgte_opcion == -1)break;
		switch(sgte_opcion){
			case 'f': 	{nombre = malloc(strlen(optarg));
					strcpy(nombre,optarg);	
					fichero = fopen(nombre,"r");
					if(fichero ==NULL)break;
					else{
						while(!feof(fichero)){
							fscanf(fichero,"%d",&numero);
							largo = largo+1;
							//printf("valor: %i, de a = %d\n",largo,numero);
						}
					}
					fclose(fichero);
					int a[largo];
					fichero2 = fopen(nombre,"r");
					if(fichero2 ==NULL)break;
					else{
						while(!feof(fichero2)){
							fscanf(fichero2,"%d",&a[j]);
							j++;
							//printf("valor: %i, de a = %d\n",j,a[j]);
						}
					}
					fclose(fichero2);
					int b[largo-1];
					int i;
					for(i =0;i<j-1;i++){
						b[i] = a[i];
					}
					float resultado;
        				resultado = ecuacion(b,largo-1);
        				printf("%f\n",resultado);
					//printf("%s\n",nombre);
				}
				break;

			case '?': printf("valor no valido\n");
				break;
		}

	}
	free(nombre);
	return 0;

}


float ecuacion(int *a,int largo){
    	float suma,base;
    	int i;
	for(i = 0; i < largo; i++){
        	base = a[i];
        	suma = suma + pow(sqrt(base),base);
        	printf("base: %f, suma %f asdasdas\n",base,suma);
    	}
    	return suma;
}
