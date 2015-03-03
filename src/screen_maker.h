/*
 * =====================================================================================
 *
 *       Filename:  screen_maker.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/15 11:42:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Maria Caballero Alba (caballeroalba), caballeroalba@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <ncurses.h>
#include <stdio.h>


int select_Table_Option();
int create_Table_Screen();
int select_Chain_Option(char *Tname);
int create_Chain_Screen(char *Tname);
int select_Rule_Option(char *Tname, char *Cname);
int create_Rule_Screen(char *Tname, char *Cname);

