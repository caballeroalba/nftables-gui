#include <stdio.h>
#include "table.h"
#include "screen_work_flow.h"
#include "list.h"
#include <string.h>

/* prototipes*/
void create_table(struct table *t);
//void list_tables(struct table_list *list);

struct table_list {
    struct list_head list;
    int elements;
};

void list_tables(struct table_list *list);
void list_table_details(int ntable,struct table_list *list);
struct table * get_table(int ntable);

int main(void)
{
    struct table_list *lista;
    lista=calloc(1,sizeof(struct table_list));
    if(lista==NULL)
        return -1;
    INIT_LIST_HEAD(&lista->list);
    lista->elements=0;
	char *choices[2]={
		"Create table",
		"List tables"
	};

 	 struct table *t1;
  	//t1=nftables_gui_table_alloc();
  	while (1)
 	 {
    		int result=print_menu(1,choices,2,"prueba","Welcome to nftables-gui,"
      					"please select a option");
    		if(result==1)
   		 {

    	 		t1=nftables_gui_table_alloc();
                
			printf("direccion %p\n", t1);
   			//  memset(t1,0,(sizeof(struct table)));
     			create_table(t1);
			if(t1!=NULL){
	        		list_add(&t1->head,&lista->list);
                    lista->elements++;
            }
			printf("prueba2\n");
   		 }else if(result==2)
	    	 {
			 printf("prueba3\n");
     			 list_tables(lista);
	    	 }
 	 }

}

void list_tables(struct table_list *list){

    struct table *cur,*tmp;
    char *opts[99];
    int i=0;

    if(list->elements==0)
        return;
    printf("los elementos de la lista son: %d\n",list->elements);
	list_for_each_entry_safe(cur,tmp,&list->list,head){
        
        printf("%s\n",nftables_gui_table_attr_get_str(cur,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME));      
        opts[i]=strdup(nftables_gui_table_attr_get_str(cur,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME));    
        i++;
	  }
    int result=print_menu(1,opts,list->elements,"","Select a table for details");
    if(result==0){
        return;
    }else{
        list_table_details(result,list);
    }

}


struct table * get_table(int ntable){
    return NULL;    
}

void list_table_details(int ntable,struct table_list *list)
{
    char *opts[]={
        "List chains",
        "Create chain",
        "Delete this table"
    };
    printf("el numero de tabla seleccionada es: %d\n",ntable);
    struct table *c;
    int i=1;
    list_for_each_entry(c, &list->list, head) {
        printf("he entrado en el forearch\n");
        if (i == ntable)
            break;
        i++;
    }
    if(c==NULL)
        return;
    printf("el nombre la tabla seleccionada es: %s\n",nftables_gui_table_attr_get_str(c,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME)); 
    char message[50];
    char *message1="You are in ";
    char *message2=" table, please select a option";
    const char *table_name;
    table_name=nftables_gui_table_attr_get_str(c,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME);
    strcpy(message,message1);
    strcat(message,table_name);
    strcat(message,message2);
    int result=print_menu(1,opts,3,"",message);

}

void create_table(struct table *t1)
{

	  char *tables_name[4]={
   	        "IP",
	        "ARP",
	        "IP6",
    		"BRIDGE"
  	  };
  	 int result;

  	 result=print_menu(1,tables_name,4,"prueba","select a familty");
     char *opts[5];
     char *opts_value[5];
  	 switch(result){

	 	    
    	    
    		case 1:

			nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"IP");
			//create the table with family ip and get the name of table
			opts[0]="Table name";
			form_create(1,opts,opts_value);
			nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
						opts_value[0]);
			break;

    		case 2:  /* arp family */
		       nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"ARP");
		      //create the table with family arp and get the name of table
		      opts[0]="Table name";
		      form_create(1,opts,opts_value);
		      nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
							opts_value[0]);

		      break;
		case 3:  /* ip6 family */
		       nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"IP6");
		      //create the table with family arp and get the name of table
		      opts[0]="Table name";
		      form_create(1,opts,opts_value);
		      nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
							opts_value[0]);

		      break;
    		case 4:  /* bridge  family */
		       nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"BRIDGE");
		      //create the table with family arp and get the name of table
		      opts[0]="Table name";
		      form_create(1,opts,opts_value);
		      nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
							opts_value[0]);

		      break;
  }

     
    



}
