/*
 * =====================================================================================
 *
 *       Filename:  definitions.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/03/15 09:05:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Maria Caballero Alba (caballeroalba), caballeroalba@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */


struct table 
{
	char tableName[50];
	char family[50];
	struct chain *chains[99];

};

struct chain
{
	char chainName[50];
	char hook[10];
	struct rule *rules[99];
	struct table tabla;

};

struct rule
{
	char ruleName[50];
	char action[10];
	struct chain cadena;
	struct table tabla;

};

