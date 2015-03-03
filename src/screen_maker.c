/*
 * =====================================================================================
 *
 *       Filename:  screen_maker.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/15 11:53:49
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
#include "screen_maker.h"


int main (){
	
	//variables
	
	

	//TODO
	
	select_Table_Option();
	


}




int select_Table_Option(){
	initscr();
	move(5,15);
	printw("%s","Welcome to nftables-gui, please select a option");
	refresh();
	sleep(2);
	endwin();
}
