#include <stdio.h>
#include "table.h"
#include "screen_work_flow.h"
#include "list.h"
/* prototipes*/
void create_table(struct table *t);
void list_tables(struct list_head list);


int main(void)
{
	struct list_head table_list;
	INIT_LIST_HEAD(&table_list);
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
			if(t1!=NULL)
	        		list_add(&t1->head,&table_list);
			printf("prueba2\n");
   		 }else if(result==2)
	    	 {
			 printf("prueba3\n");
     			 list_tables(table_list);
	    	 }
 	 }

}

void list_tables(struct list_head list){
//  char *choices[99];
	  struct table *t,*tmp;

	  list_for_each_entry_safe(t,tmp,&list, head){
	    if(t==NULL || tmp==NULL)
	      break;
	  	printf("mostar la lista\n");
   	    printf("%s\n",nftables_gui_table_attr_get_str(t,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME));



 	  }

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
  	 switch(result){

	 	char *opts[5];
	 	char *opts_value[5];
    		char info[250];
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
