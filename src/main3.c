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
	struct table *tablas[99]; //array de punteros de 99 tablas


	/* TODO */

	verify_tables(tablas);

	if(tablas==NULL){

		/* no hay tablas creadas */
	}else{

		/* buscamos las cadenas de las tablas */
		int i;
		//printf("el ahora es %s\n ",sizeof(struct table)/sizeof(tablas));
		for (i=0; i<=sizeof(struct table)/sizeof(tablas);i++){

			tablas[i]->chains[i]=malloc (sizeof (struct chain));
	        tablas[i]->chains[i]->tabla=tablas[i];
			if(strstr(tablas[i]->tableName, "table") != NULL){
				add_Chains_To_Table(tablas[i]);
                add_Rules_To_Chain(tablas[i]->chains[i]);
			}
		}

	}

    add_Rules_To_Chain(tablas[0]->chains[0]);
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

		struct table tabla1;
		tablas[i]=malloc(sizeof(struct table));
    	strcpy(tablas[i]->tableName,output);
		i++;
	}
	pclose(fp);
	return 0;


}

/* add chains to a determinate table pointer */
int add_Chains_To_Table(struct table *tabla){

	FILE *fp;
	int status;
	char output[50];
	char command[50]="nft list  ";
	strcat(command,tabla->tableName);


	/* abrimos */
	fp=popen(command, "r");
	if(fp==NULL){
		printf("failed to run nft utility\n");
		exit;
	}

	int i=0;
	while(fgets(output, sizeof(output), fp) !=NULL){


		if(strstr(output,"chain")!=NULL){
	        int b;
            for (b=0;b<sizeof(output);b++){
                if(output[b]=='{'){
                    output[b]='\0';
                }
            }
            tabla->chains[i]=malloc (sizeof(struct chain));
			strcpy(tabla->chains[i]->chainName,output);
			i++;
		}

	}
	pclose(fp);
	return 0;
}


int add_Rules_To_Chain(struct chain *cadena){
    printf("hola2%s\n",cadena->tabla->tableName);
    FILE *fp;
    char output[50];
    char command[50]="nft list table  ";
    strcat(command,cadena->tabla->tableName);
    printf("   comando a ejecutar desde add_Rules_To_Chain  es: %s\n",command);

    return 0;
}
