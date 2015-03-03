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
	struct table *tablas=malloc (99 * sizeof (struct table));

	/* TODO */

	verify_tables(tablas);
	printf("vemos si se ha copiado algo a nuestro array de struts\n");
	printf("el nombre de 0 en tablas es: %s\n",tablas[0].tableName);

}



int verify_tables(struct table *tablas){

	char command[50];
	strcpy(command, "nft list tables");
	//system(command);

	FILE *fp;
	int status;
	char output[555550];

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
		printf("antes del strcpy\n");
		strcpy(tabla1.tableName,output);
		printf("antes de la asignacion\n");
		tablas[i]=tabla1;		

		i++;
	}
	pclose(fp);
	return 0;

}
