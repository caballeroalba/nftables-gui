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
	
	
	struct table_list *lista;
	lista=calloc(1, sizeof(struct table_list));
	int buffer_size= 1024;
	char messages[buffer_size];

	if( lista == NULL)
		return -1;

	INIT_LIST_HEAD(&lista->list);
		
	/* Sanity tables already created */
	//delete_all_tables();

	/* check for tables already created */

	load_tables_from_json(lista);	
	printf("el numero de elementos en la lista es %d\n  ", lista->elements);	

	
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
								concat_strings_buffer(" ");

							}
							
			}else if( result == 2){
				
				list_tables(lista);

			}else if( result > 7){ /*  opciones del menu */
				
			

			}

	 }

}


int load_tables_from_json (struct table_list *list)
{
	

	char *tables[4];

	tables[0] = "nft";
	tables[1] = "ip";
	tables[2] = "json";
	
//	get_tables_from_lib(3, tables);	
//	json_t *json_data;
// 	json_data	= json_string(json);		
	
	/* get json from nft export */
	FILE *pipe;
	int len;

	pipe = popen ("nft export json", "r");

	if( pipe == NULL)
			perror("pipe");

	fgets(json, sizeof(json), pipe);
	pclose(pipe);
		
	if(json == NULL)
		perror("fallo al leer por json");
	
	/* recorremos el fichero y creamos las tablas si es necesario */
	json_t *value, *root, *tabla;
	void *iter;
	const char *key;
	json_error_t err;
	int tam = strlen(json);
	//json[tam+1]= '\0';
	
	root = json_loadb(json, sizeof(json), JSON_DISABLE_EOF_CHECK, &err); 
			
		
	if(root == NULL){
		perror("Error: ");
		fprintf(stderr, "Jansson error: %s %d %d\n", err.text, 
				err.column, err.line);
	}
	
	tabla = json_object_get(root, "nftables"); 
	if( tabla == NULL)
		perror("error al obtener el objeto");
	json_t *t2=json_object_get(tabla, "table");
	printf(" tamaño del array = %d\n ", json_array_size(tabla));		
	int i=0;
	for (i=0; i < json_array_size(tabla); i++){
		json_t *table2 = json_array_get(tabla, i);
		json_t *info= json_object_get(table2, "table");
		iter = json_object_iter(info);
		if(iter == NULL){
			perror("error al iterar el objeto");
			continue;
		}
		struct table *t1;
		t1=nftgui_table_alloc();
		
		while (iter) {
		printf("clave %s valor %s iteracion %d\n",json_object_iter_key(iter), json_string_value(json_object_iter_value(iter)), i);
			key = json_object_iter_key(iter);
			value = json_object_iter_value(iter);
			if(strcmp(key, "name") == 0 || strcmp(key, "family") == 0){	
			
				if( t1 == NULL){
					perror("error creating table");
					exit(EXIT_FAILURE);
				}
				if(strcmp(key, "name" ) == 0 )
					nftgui_table_set_str(t1, NFTGUI_TABLE_TABLE_NAME, json_string_value(value));
				
				if(strcmp(key, "family") == 0 ) 	
					nftgui_table_set_str(t1, NFTGUI_TABLE_FAMILY, json_string_value(value));				
			}
			
				iter = json_object_iter_next(info, iter);
			}
			list_add(&t1->head, &list->list);
			list->elements++;
			/* Ahora iteramos sobre las cadenas */


			
		 /* iterado de cadenas */
	}
}




