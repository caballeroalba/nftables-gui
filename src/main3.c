/*
 * =====================================================================================
 *
 *       Filename:  main3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/03/15 10:37:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Maria Caballero Alba (caballeroalba), caballeroalba@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */


#include "definitions.h"
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "screen_maker.h"
#include <stdio.h>



int main(){

	/* def de las estructuras principales */
	struct table *tablas[99]; //array de 99 tablas
	tablas[0]=malloc(sizeof(struct table));
	
	/* TODO */

	verify_tables(tablas);
    printf("lo que se ha recivido ess: %s\n",tablas[0]->tableName);

	if(tablas==NULL){
		printf("no hay cadenas\n");
		/* no hay tablas creadas */
	}else{

		/* buscamos las cadenas de las tablas */
		int i;

		for (i=0; i<sizeof(struct table)/sizeof(tablas);i++){
            
			tablas[i]->chains[i]=malloc (sizeof (struct chain));
			
			if(strstr(tablas[i]->tableName, "table") != NULL){
		        printf("tabla numero %d nombre: %s\n",i,tablas[i]->tableName);
                  
				add_Chains_To_Table(tablas[i]);
			    printf("su primera cadena es %s\n",tablas[i]->chains[0]->chainName);
			}
		}

	}	
	//free(tablas);
}



int verify_tables(struct table *tablas[99]){

	char command[50];
	strcpy(command, "nft list tables");
	//system(command);

	FILE *fp;
	int status;
	char output[50];

	/* abrimos el comando para su lectura */
	fp=popen("nft list tables", "r");
	if(fp==NULL){
		printf("failed to run nft utitly\n");
		exit;
	}
	/* leemos y guardamos la salida */
	int i=0;
	while(fgets(output, sizeof(output), fp) !=NULL){
		printf("%s",output);
		struct table tabla1;
       // tabla1=malloc (sizeof(struct table));
		printf("antes del strcpy\n");
		strcpy(tablas[0]->tableName,output);
		printf("antes de la asignacion\n");
		//tablas[i]=tabla1;		
        printf("desppues de haberlo asignado su nombre es: %s\n",tablas[i]->tableName);
		i++;
	}
	pclose(fp);
	return 0;


}

int add_Chains_To_Table(struct table *tabla){
    
	FILE *fp;
	int status;
	char output[50];
	char command[50]="nft list  ";
	strcat(command,tabla->tableName);
    printf("el comando a ejecutar es %s\n",command); 
	
	/* abrimos */
	fp=popen(command, "r");
	if(fp==NULL){
		printf("failed to run nft utility\n");
		exit;
	}
    
	int i=0;
	while(fgets(output, sizeof(output), fp) !=NULL){	
		
		//struct chain *chain1= malloc (sizeof(struct chain));
		//struct chain * chain1=(struct chain *) malloc (sizeof (struct chain));
		if(strstr(output,"chain")!=NULL){
			//strcpy(chain1->chainName,output);
			//tabla.chains[i]=chain1;
			//tabla.chains[i]=malloc (sizeof (struct chain));
            printf("antes de copiar iter %d\n",i);
            tabla->chains[i]=malloc (sizeof(struct chain));
			strcpy(tabla->chains[i]->chainName,output);
			printf("cadena encontrada: %s\n",output);
			printf("valor en el struct: %s\n",tabla->chains[i]->chainName);
			i++;
		}
		
	}
	pclose(fp);
	return 0;
}
