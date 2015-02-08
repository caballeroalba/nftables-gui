

#include <stdio.h>
#include <form.h>
#include <ncurses.h>
#include "database_util.h"

#define WIDTH 30
#define HEIGHT 10 
void createChain();
int print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices); //metodo para el el menu, 
void createRule();
void createTable();
void createTableIP();


void createTable();



void createRule(){

	int startx = (80 - WIDTH) / 2;
	int starty = (24 - HEIGHT) / 2;
	clear();
	endwin();
	initscr();
	mvprintw(0,0,"Please select the type of rule");
	refresh();
	char *choices[]={"accept","drop","reject","redirect"};
	int n_choices = sizeof(choices) / sizeof(char *); //numero de opciones
	WINDOW *menu_win;
	menu_win = newwin(HEIGHT, WIDTH, starty, startx); // metodo para crear un menu, es de ncurses
	keypad(menu_win, TRUE); //obtenemos datos del teclado
	refresh();
	int salida=print_menu(menu_win, 1,choices,n_choices);
	//seleccionamos la salida y vemos que hacemos para crear la tabla
	switch(salida){
		case 1: //accept, podemos aprovectar la misma window en la que estamos
			
			break;
		case 2: //drop
			break;
		case 3: //reject
			break;
		case 4: //redirect
			break;



	}
	
}

void createTable(){
	int startx = (80 - WIDTH) / 2;
	int starty = (24 - HEIGHT) / 2;
	clear();
	endwin();
	initscr();
	mvprintw(0,0,"Please select the family");
	refresh();
	char *choices[]={"ip","ip6","arp","nat"};
	int n_choices = sizeof(choices) / sizeof(char *); //numero de opciones
	WINDOW *menu_win;
	menu_win = newwin(HEIGHT, WIDTH, starty, startx); // metodo para crear un menu, es de ncurses
	keypad(menu_win, TRUE); //obtenemos datos del teclado
	refresh();
	int salida=print_menu(menu_win, 1,choices,n_choices);
	//seleccionamos la salida y vemos que hacemos para crear la tabla
	switch(salida){
		case 1: //ip
			createTableIP();
			break;
		case 2: //ip6
			break;
		case 3: //arp
			break;
		case 4: //nat
			break;
	}


	
	
}


void createTableIP(){


	char tableName[80];
	clear();
	refresh();
	mvprintw(10,0,"Please insert the name of table\n");
	echo();
	getstr(tableName);  
	mvprintw(12, 0, "You Entered: %s", tableName);
	char command[80];
	snprintf(command, sizeof(command), "nft create table '%s'  > test.txt", tableName);
	system(command);

}




void createChain(){
	
	endwin();
	clear();
	initscr();
	
	printw ("Please select the hook of chain\n");
			
	char *choices[]={"INPUT","OUTPUT","PREROUTE","POSTROUTING","CUSTOM"};
	int num= sizeof(choices) / sizeof(char *);
	WINDOW *menuwin;
	menuwin = newwin(num+10, 30, 5, 5);
	char *tablas[100];
	WINDOW *menu2;
	keypad(menuwin, TRUE);
	refresh();
	int salida=print_menu (menuwin, 1, choices, num);
    
    switch(salida){
        case 1: //input
            //debemos de llamar a las tablas que hay existentes
        	 
        	 
        	 
        	 menu2=newwin(num+10,30,5,5);
        	 keypad(menu2,TRUE);
        	 refresh();
        	 tablas[]=getTables();
        	 int num2= sizeof(tablas) / sizeof(char *);
        	  salida=print_menu (menuwin, 1,tablas , num2);

            break;
        case 2: //output
            //
            break;
        case 3: // preroute
            //
            break;

        case 4:
            break;        
           // 
       case 5:
            break;
            //
    
    }    
	


}



int print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices)
{
    //tarea: modificar metodo para que solo necesite el array de las opciones, que el solo imprima y detecte el menu
	int x, y, i;	

	int choice = 0;
	int c=0;
        
        
	
	while(1) //infinito para vovler a el desde los ficheros de funciones
	{	

	

	        x = 2;
	        y = 2;
	        box(menu_win, 0, 0);
	        for(i = 0; i < n_choices; ++i)
	        {	if(highlight == i + 1) /* High light the present choice */
		        {	wattron(menu_win, A_REVERSE); 
			        mvwprintw(menu_win, y, x, "%s", choices[i]);
			        wattroff(menu_win, A_REVERSE);
		        }
		        else
			        mvwprintw(menu_win, y, x, "%s", choices[i]);
		        ++y;
	        }
	        wrefresh(menu_win);



		
		
		        c = wgetch(menu_win); // obtenemos las pulsaciones del teclado
		        switch(c)
		        {	case KEY_UP: //flecha arriba
				        if(highlight == 1) // comprobamos que si highlight es 1 (primera posicion) lo dejamos igual (es decirlo, lo seleccionamos como high)
					        highlight = n_choices; // lo dejamos a 1 (n_choises era 0)
				        else
					        --highlight; // si no es uno, subimos de posicion
				        break;
			        case KEY_DOWN:
				        if(highlight == n_choices)
					        highlight = 1;
					
				        else 
					        ++highlight;
				
				
				        break;
			        case 10:
				        choice = highlight; // caso intro, pasa a elegir la opcion
				        break;
			        default:
				        mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				        refresh();
				        break;
		        }
		

		        if(choice != 0)	/*se sale del loop infinito, por lo cual procedemos a hacer segun la choise elegida */
			        break;
		        else
			        continue;
			        //print_menu(menu_win, highlight, choices, n_choices);
	}	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	
	clrtoeol();
	refresh();// aqui en funcion de la choice hacemos las cosas necesarias
	//createChain();
	
	return choice;
}


