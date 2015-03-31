#include <stdio.h>
#include "list.h"
#include <string.h>
#include <inttypes.h>
#include "prototypes.h"

int main(void)
{
	struct table_list *lista;
	lista=calloc(1, sizeof(struct table_list));

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
	
	while (1)
	 {
			int result=print_menu(1,choices,2,"prueba","Welcome to nftables-gui,"
						"please select a option");

			if( result == 1){

							t1=nftables_gui_table_alloc();
							create_table(t1);

							if( t1!= NULL){

								list_add(&t1->head, &lista->list);
								lista->elements++;

							}
							
			}else if( result == 2){
				list_tables(lista);
			}

	 }

}



