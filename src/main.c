#include <stdio.h>
#include "list.h"
#include <string.h>
#include <inttypes.h>
#include "prototypes.h"
#include "nft-table-add.h"
#include "nft-chain-add.h"
#include "nft-table-del.h"
#include "nft-chain-del.h"
#include "nft-table-get.h"
#include "nft-rule-get.h"
#include <jansson.h>


char json[4096];


int main(void)
{

	/* check is root user */
	if (getuid())
	{
		printf("%s", "You must be root!\n");	
		return -1;
	}
	/* root user */
	
	/* check for tables already created */

	char *tables[4];

	tables[0] = "nft";
	tables[1] = "ip";
	tables[2] = "json";
	
	get_tables_from_lib(3, tables);	
	json_t *json_data;
 	json_data	= json_string(json);		
	
	if(json_data == NULL)
		perror("fallo al leer por json");
	
	/* recorremos el fichero y creamos las tablas si es necesario */
	json_t *value;
	void *iter, *root, *tabla;
	const char *key;
	json_error_t err;
	root = json_load_file("prueba.json", 0 , &err); 
	tabla = json_object_get(root, "table"); 
	iter = json_object_iter(tabla);
	while (iter) {
		key = json_object_iter_key(iter);
		value = json_object_iter_value(iter);
		printf("key del objeto %s\n y valor %s\n", key, value);
		iter = json_object_iter_next(tabla, iter);
	}
	

	/* check for tables already created */
	struct table_list *lista;
	lista=calloc(1, sizeof(struct table_list));
	int buffer_size= 1024;
	char messages[buffer_size];

	if( lista == NULL)
		return -1;

	INIT_LIST_HEAD(&lista->list);
		
	/* Sanity tables already created */
	//delete_all_tables();

		
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



