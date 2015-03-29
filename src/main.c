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
void list_table_details(int ntable, struct table_list *list);
void list_chain_details(int ntable, int nchain, struct table_list *list);
void list_chains(int ntable, struct table_list *list);
void create_chain(int ntable, struct table_list *list);
void delete_chain(int ntable, struct table_list *list);
void delete_table(int ntable, struct table_list *list);
struct chain * get_chain(struct table *t, int nchain);
struct table * get_table(int ntable, struct table_list *list);

int main(void)
{
	struct table_list *lista;
	lista=calloc(1,sizeof(struct table_list));

	if( lista == NULL)
		return -1;

	INIT_LIST_HEAD(&lista->list);
	
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
			if(result==1)
		         {

				    t1=nftables_gui_table_alloc();
					create_table(t1);
					if(t1!=NULL){
					    list_add(&t1->head, &lista->list);
				    	lista->elements++;
			        }
			
		        }else if( result == 2)   
					{
				        list_tables(lista);
			        }
	 }

}

void list_tables(struct table_list *list){

	struct table *cur,*tmp;
	char *opts[99];
	int i=0;

	if( list->elements == 0)
		return;

	list_for_each_entry_safe(cur,tmp,&list->list,head)
	{			 
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


struct table * get_table(int ntable, struct table_list *list){
	
	struct table *cur,*tmp;
	
	int i=0;

	if(list->elements==0)
		return NULL;

	list_for_each_entry_safe(cur,tmp,&list->list,head){
		if( i== ntable-1)
			break;

		i++;
	  }
 
	if( cur == NULL)
		return NULL;
	return cur;    
}

void list_table_details(int ntable,struct table_list *list)
{
	char *opts[]={
		"List chains",
		"Create chain",
		"Delete this table",
		"Back"
	};
	
	struct table *c;
	int i=0;

	list_for_each_entry(c, &list->list, head) {
		
		if (i == ntable-1)
			break;
		i++;
	}
	if( c == NULL)
		return;
	 
	char message[50];
	char *message1="You are in ";
	char *message2=" table, please select a option";
	const char *table_name;

	table_name=nftables_gui_table_attr_get_str(c,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME);
	
	strcpy(message,message1);
	strcat(message,table_name);
	strcat(message,message2);
	
	int result=print_menu(1,opts,4,"",message);
	 
	if( result == 0)
		return;
	switch(result){
		
		case 1:
			list_chains(ntable, list);
			break;
		case 2:
			create_chain(ntable, list);
			break;
		case 3: 
			delete_table(ntable,list);
			break;
		case 4:
			/* Back, volvemos al menu de lista de tablas */
			list_tables(list);
			break;
	}

}

void create_chain(int ntable, struct table_list *list)
{
	
	struct table *cur,*tmp;
	char *opts[2]={
		"Chain name",
		"Hook"
	};

	char *opts_value[2];	
	int i=0;
	
	if( list->elements == 0)
		return;

	list_for_each_entry_safe(cur,tmp,&list->list,head){
		if( i== ntable-1)
			break;
		i++;
	}


   form_create(2,opts,opts_value);
   struct chain *chain;

   chain=nftables_gui_chain_alloc();
   nftables_gui_chain_attr_set_str(chain,NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME,opts_value[0]);
   nftables_gui_chain_attr_set_str(chain,NFTABLES_GUI_CHAIN_ATTR_HOOK,opts_value[1]);
   nftables_gui_table_attr_set_chain(cur,NFTABLES_GUI_TABLE_ATTR_CHAIN,chain);

   /* return to details of table */
   list_table_details(ntable, list);

}

void list_chains(int ntable, struct table_list *list)
{
		 
	struct table *cur,*tmp;
	char *opts[99];
	int i=0;
	
	if( list->elements == 0)
		return;

	list_for_each_entry_safe(cur,tmp,&list->list,head){
		if( i == ntable-1)
			break;
		i++;
	}
	
	if( cur->num_chains == 0){
		list_table_details(ntable, list);
		return;
	}
	int b;
		
	 for(b=0; b<cur->num_chains; b++){
	
		struct chain *chain;

		chain=nftables_gui_table_attr_get_chain(cur,NFTABLES_GUI_TABLE_ATTR_CHAIN,b);

		if( chain== NULL)
		 return;

		opts[b]=strdup(nftables_gui_chain_attr_get_str(chain,NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME));
		
	}

	const char *table_name=nftables_gui_table_attr_get_str(cur,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME);
	char message[80];
	char *message1="You are in ";
	strcpy(message,message1);
	strcat(message,table_name);
	char *message2=" table chains list,\n select a chain for details ";
	strcat(message,message2);
	
	int result=print_menu(1,opts,cur->num_chains,"",message);
	
	if( result == 0){
		return;
	}else{
	   list_chain_details(ntable,result,list);
	}

}


void delete_table(int ntable, struct table_list *list){
		
	struct table *c;

	c=get_table(ntable,list);
	list_del(&c->head);
	list->elements--;
	nftables_gui_table_free(c);
}

void list_chain_details(int ntable, int nchain, struct table_list *list)
{
  
	struct table *t;

	t=get_table(ntable,list);

	if( t == NULL)
		return;

	struct chain *ch;
	
	ch=get_chain(t,nchain);
	
	if( ch == NULL)
		return;

	const char *chain_name=nftables_gui_chain_attr_get_str(ch,
							NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME);
	const char *hook=nftables_gui_chain_attr_get_str(ch,
							NFTABLES_GUI_CHAIN_ATTR_HOOK);

	char *opts[5];

	opts[1]=strdup(chain_name);
	opts[2]=strdup(hook);
	opts[3]="Create rule";
	opts[4]="List rules";
	opts[5]="Back";	
	char *message="You are in ";
	
	const char* table_name=nftables_gui_table_attr_get_str(t,
							NFTABLES_GUI_TABLE_ATTR_TABLE_NAME);
	//message=strcat(message,table_name);
	char *message2=" chain ";
	//message=strcat(message,strcat(message2,chain_name));
	int result=print_menu(1,opts,6,"","");

	if( result == 0)
		return;
	switch( result) 
	{

	}
}

struct chain * get_chain(struct table *t, int nchain){
	struct chain *cur;
	int pos;

	list_for_each_entry(cur,&t->chains,head){
		 		 
		if( pos == nchain-1)
			break;
		pos++;
	}

	return cur;
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

			case 4:  /* bridge	family */
			   nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"BRIDGE");
			  //create the table with family arp and get the name of table
			  opts[0]="Table name";
			  form_create(1,opts,opts_value);
			  nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
							opts_value[0]);

			  break;
  }

	 
	



}
