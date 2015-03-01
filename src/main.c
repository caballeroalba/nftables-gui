/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 Jos?? Mar??a Caballero Alba <caballeroalba@gmail.com>
 * 
 * nftables-gui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * nftables-gui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <ncurses.h> //Incluiremos una librería a nuestro sistemas
#include <stdio.h>
#include "screen_Utilites.h"
#include <stdlib.h>
#include <sqlite3.h>

#define WIDTH 30
#define HEIGHT 10 

int startx = 0; //posiciones del menu
int starty = 0; // posiciones del menu

char *choices[] = {  //opciones
			"Create table",
			"Create chain",
			"Create Rule",
			"Export rules",
			"Import rules",
			"Exit", 
		  };
int n_choices = sizeof(choices) / sizeof(char *); //numero de opciones




int main(){


	WINDOW *menu_win; //el menu de tipo windows como puntero
	int highlight = 1; // el highlight
	

	initscr(); //iniciamos la pantalla
	clear(); //borramos
	noecho(); //no escribirir
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	start_color();
	assume_default_colors(COLOR_WHITE,COLOR_BLUE);
	menu_win = newwin(HEIGHT, WIDTH, starty, startx); // metodo para crear un menu, es de ncurses
	keypad(menu_win, TRUE); //obtenemos datos del teclado
	mvprintw(0, 0, "Welcome to nftables-gui please select a option");
	refresh();
	int salida=print_menu(menu_win, highlight, choices, n_choices); // dibujamos el menu pasandole el menu creado y la opción para hacer high light

	switch(salida){

		case 1://createtable
			createTable();
			break;
		case 2://createChain ()
			createChain();
			break;
		case 3: //createRule
			createRule();
			break;
		case 4: //export rules
			break;
		case 5://import rules
			break;
		case 6://exit
			clear();
			endwin();
			exit(EXIT_SUCCESS);

	}

	
	clear();
	mvprintw(0, 0, "se ha seleccionado la opcion %d", salida);
	refresh();
	getch(); // pausa 
	main(); // una vez finalizan los metodos volvemos al menu principal
	endwin();
	return 0;
}


