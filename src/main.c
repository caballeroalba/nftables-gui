#include <stdio.h>
#include "list.h"
#include <string.h>
#include <inttypes.h>
#include "prototypes.h"
#include "nft-table-add.h"
#include "nft-chain-add.h"
#include "nft-table-del.h"
#include "nft-chain-del.h"

int main(void)
{

	/* check is root user */
	if (getuid())
	{
		printf("%s", "You must be root!\n");	
		return -1;
	}
	/* root user */

	struct table_list *lista;
	lista=calloc(1, sizeof(struct table_list));
	int buffer_size= 1024;
	char messages[buffer_size];

	if( lista == NULL)
		return -1;

	INIT_LIST_HEAD(&lista->list);
		
	/* Sanity tables already created */
	delete_all_tables();

		
	lista->elements=0;
	char *choices[2]={
		"Create table",
		"List tables"
	};

	struct table *t1;
	
	snprintf(buf_screen, MAX_BUFFER_SIZE, "Welcome to nftables gui \n, please select");	
	printf("%s\n", buf_screen);
	while (1)
	 {
			int result=print_menu(1, choices, 2, messages, "Welcome to nftables-gui,"
						"please select a option");

			if( result == 1){

							t1=nftgui_table_alloc();
							create_table(t1);

							if( t1!= NULL){

								list_add(&t1->head, &lista->list);
								lista->elements++;
								concat_strings_buffer("test2");

							}
							
			}else if( result == 2){
				
				list_tables(lista);
			}else if( result == 7){ /* aqui las opciones del menu */
				/*
				printf("la opción seleccionada es: %d\n", result);
				list_tables(lista);
				char *table[3];
				table[0]="nft";
				table[1]="ip";
				table[2]="test";
				create_table_nft(3, table);
				/* y apagamos curses */
			}

	 }

}



