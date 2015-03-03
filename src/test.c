/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/03/15 09:10:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Maria Caballero Alba (caballeroalba), caballeroalba@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */



#include <stdio.h>
#include "definitions.h"
#include <string.h>
#include <stdlib.h>


int main(){

	struct table table1;
	strcpy(table1.tableName,"hola");
	printf("el valor del campo table  name es: %s\n",table1.tableName);	
	printf("vamos a insertar una cadena:\n");
	struct chain * cadena = malloc(sizeof (struct chain));
	//struct chain *cadena;
	strcpy(cadena->chainName,"cadenaNombre");
	printf("el nombre de la cadena (que es un puntero es: %s\n",cadena->chainName);
	table1.chains[0]=cadena;
	printf("el nombre de la cadena, en la struct tabla es: %s\n",table1.chains[0]->chainName);
	printf("asignamos la tabla a la cadena:\n");
	cadena->tabla=table1;
	printf("el nombre de la tabla desde la cadena es %s\n",cadena->tabla.tableName);
}





