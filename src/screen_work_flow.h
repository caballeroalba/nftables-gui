#include <ncurses.h>
#include <form.h>
#include <menu.h>
#include <string.h>


#define WIDTH 30
#define HEIGHT 10





int print_menu(int highlight, char *choices[],int n_choices, char *message, char *title)
{
	//tarea: modificar metodo para que solo necesite el array de las opciones, que el solo imprima y detecte el menu
  int x,y,i;
  int startx,starty=0;
  WINDOW *menu_win;
  startx=(40-WIDTH) / 2;
  starty=(24-HEIGHT) /2;
  
  initscr();
  clear();
  start_color();
  assume_default_colors(COLOR_WHITE,COLOR_BLUE);
  menu_win=newwin(HEIGHT+n_choices, WIDTH+n_choices, startx, starty);
 
  mvprintw(0,0,title);
  refresh();
  keypad(menu_win,TRUE);
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
							highlight = n_choices; // lo dejamos a 1 (n_choices era 0)
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
		
	}	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	
	clrtoeol();
	refresh();// aqui en funcion de la choice hacemos las cosas necesarias
	delwin(menu_win);  
  endwin();
	
	return choice;
}
/*	This method create a generic form in function of params as passed by method
 *	First param: Number of params (int)
 *	Second param: Name of fields (char *) */
void form_create(int n, char *opts[], char *opts_values[])
{
  FIELD *field[n];
	FORM  *my_form;
	int ch;
	
	/* Initialize curses */
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize the fields */
  int i;
  for (i=0; i<n; i++){
	  if(i==0)
	  field[i] = new_field(1, 10, 4, 25, 0, 0);
	field[i]=new_field(1,10,4+i,25,0,0);
  }
  
	field[n] = NULL;

	/* Set field options */
  for(i=0; i<n; i++){
	  set_field_back(field[i], A_UNDERLINE);	/* Print a line for the option	*/
	  field_opts_off(field[i], O_AUTOSKIP);		/* Don't go to next field when this */
	field_opts_on(field[i], O_EDIT);
  }
	
	/* Field is filled up		*/
	/*Create the form and post it */
	my_form = new_form(field);
	post_form(my_form);
	refresh();
	for (i=0; i<n; i++){
	  mvprintw(4+i, 10, opts[i]);
	}
  mvprintw(0,0,"Please fill values and press F2 to exit");
  refresh();

	/* Loop through to get user requests */
	while((ch = getch()) != KEY_F(2))
	{	switch(ch)
		{	case KEY_DOWN:
				/* Go to next field */
		form_driver(my_form, REQ_VALIDATION);
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
		form_driver(my_form,REQ_VALIDATION);
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
	  case KEY_BACKSPACE:
		form_driver(my_form,REQ_DEL_PREV);
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */	
		form_driver(my_form,REQ_VALIDATION);
				form_driver(my_form, ch);
				break;
		}
	}
  /* f2 key, need to validade last char */
  form_driver(my_form,REQ_VALIDATION);

  endwin();
  /* copy all values of form to opts_values passed by function */
  for(i=0; i<n; i++){
	opts_values[i]=strdup(field_buffer(field[i],0));
  }
	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	for(i=0; i<n; i++){
  
	free_field(field[i]);
	
  }
 
  
	
}
