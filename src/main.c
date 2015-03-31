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
void list_rules(struct chain *ch);
void list_rule_details(struct chain *ch, int nrule);
struct rule * get_rule(struct chain *ch, int nrule);
void create_chain(int ntable, struct table_list *list);
void delete_chain(int ntable, struct table_list *list);
void delete_table(int ntable, struct table_list *list);
void create_rule(struct chain *);
struct chain * get_chain(struct table *t, int nchain);
struct table * get_table(int ntable, struct table_list *list);

int main(void)
{
	struct table_list *lista;
	lista=calloc(1, sizeof(struct table_list));

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

	if( list->elements == 0)
		return NULL;

	list_for_each_entry_safe(cur, tmp, &list->list, head){

		if( i== ntable-1)
			break;

		i++;
	  }
 
	if( cur == NULL)
		return NULL;
	printf("el nombre de tabla en get table es %s\n",cur->table_name);
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
	 
	
	const char *table_name;
	table_name=nftables_gui_table_attr_get_str(c, NFTABLES_GUI_TABLE_ATTR_TABLE_NAME);
	
	char buf[1024];

	snprintf(buf , sizeof(buf), "You are in %s table, please"
			"select a option" ,table_name );

	int result=print_menu(1, opts, 4, "", buf);
	 
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
			delete_table(ntable, list);
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

	list_for_each_entry_safe(cur, tmp, &list->list, head){
		if( i == ntable-1)
			break;
		i++;
	}


   form_create(2, opts, opts_value);
   
	 struct chain *chain;
	 
   chain=nftables_gui_chain_alloc();
   nftables_gui_chain_attr_set_str(chain, NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME, opts_value[0]);
   nftables_gui_chain_attr_set_str(chain, NFTABLES_GUI_CHAIN_ATTR_HOOK, opts_value[1]);
   nftables_gui_table_attr_set_chain(cur, NFTABLES_GUI_TABLE_ATTR_CHAIN, chain);

	 /* making the chain */
	 int system_result=0;
	 char buf[1024];
	 snprintf(buf, sizeof(buf), "nft add chain %s %s { type filter hook %s priority 0 \\; }", cur->table_name, opts_value[0], opts_value[1]);
	 system_result= system(buf);
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

	list_for_each_entry_safe(cur, tmp, &list->list, head){
		if( i == ntable-1)
			break;
		i++;
	}
	
	if( cur->num_chains == 0){
		list_table_details(ntable, list);
		return;
	}
	int b;
	struct chain *chain;	
	for(b=0; b < cur->num_chains; b++){
	
		

		chain=nftables_gui_table_attr_get_chain(cur, NFTABLES_GUI_TABLE_ATTR_CHAIN, b);

		if( chain == NULL)
		 return;

		opts[b]=strdup(nftables_gui_chain_attr_get_str( chain, NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME));
		
	}

	const char *table_name=nftables_gui_table_attr_get_str(cur, NFTABLES_GUI_TABLE_ATTR_TABLE_NAME);
	char buf[1024];

	snprintf(buf, sizeof(buf), " You are in %s table chain list,\n"
			"plase select a chain for details", table_name);

	int result=print_menu(1, opts, cur->num_chains, "", buf);
	
	if( result == 0){
		return;
	}else{
	   list_chain_details(ntable, result, list);
	}

}


void delete_table(int ntable, struct table_list *list){
		
	struct table *c;

	c=get_table(ntable, list);
	list_del(&c->head);
	list->elements--;
	nftables_gui_table_free(c);
}

void list_chain_details(int ntable, int nchain, struct table_list *list)
{
 	 
	struct table *t;

	t=get_table(ntable, list);

	if( t == NULL)
		return;

	struct chain *ch;
		
	
	ch=get_chain(t, nchain);
	
	if( ch == NULL)
		return;

	const char *chain_name=nftables_gui_chain_attr_get_str(ch,
							NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME);
	const char *hook=nftables_gui_chain_attr_get_str(ch,
							NFTABLES_GUI_CHAIN_ATTR_HOOK);

	char *opts[6];

	opts[1]=strdup(chain_name);
	opts[2]=strdup(hook);
	opts[3]="Create rule";
	opts[4]="List rules";
	opts[5]="Delete this Chain";
	opts[6]="Back";
	

	const char* table_name=nftables_gui_table_attr_get_str(t,
							NFTABLES_GUI_TABLE_ATTR_TABLE_NAME);
	char buf[1024];

	snprintf(buf, sizeof(buf), "You are in %s table, in "
			"%s chain, \n please select a option", table_name,
															ch->chain_name);
	int result=print_menu(1, opts, 7, "", buf);
	
	result--;
	
	if( result == 0)
		return;
	switch( result ){
		
		case 3:
			create_rule(ch);		
			break;

		case 4:
			list_rules(ch);
			
			break;

		case 5:
			
			nftables_gui_table_attr_unset_chain(t, nchain);
			break;

		case 6:

			break;

	}
}

void list_rules(struct chain *ch)
{
	struct rule *cur,*tmp;
	char *opts[99];
	
	if(ch->num_rules == 0)
		return;

	int i=0;
	
	list_for_each_entry_safe(cur, tmp, &ch->rules, head){

		opts[i]=strdup(nftables_gui_rule_attr_get_str(cur,
					NFTABLES_GUI_RULE_ATTR_RULE_NAME));
		i++;
	}

	int result=print_menu(1, opts, ch->num_rules,"","");

	if( result== 0)
		return;
	
	if(result > 0){
		list_rule_details(ch, result);
	}
}

void list_rule_details(struct chain *ch, int nrule)
{
	printf("la rule llegada es : %d\n", nrule);
	struct rule *r;
	if( ch == NULL )
		return;

	if( nrule == 0 )
		return;

	r=get_rule(ch, nrule);
		
	const char *rule_name= nftables_gui_rule_attr_get_str(r,
										 		NFTABLES_GUI_RULE_ATTR_RULE_NAME);
	const char *action = nftables_gui_rule_attr_get_str(r,
												NFTABLES_GUI_RULE_ATTR_ACTION);
	const char *proto = nftables_gui_rule_attr_get_str(r,
												NFTABLES_GUI_RULE_ATTR_PROTO);
	int srcport = nftables_gui_rule_attr_get_u32(r,
												NFTABLES_GUI_RULE_ATTR_SRCPORT);
	int dstport = nftables_gui_rule_attr_get_u32(r,
												NFTABLES_GUI_RULE_ATTR_DSTPORT);
	const char *ipsrc = nftables_gui_rule_attr_get_str(r,
												NFTABLES_GUI_RULE_ATTR_IPSRC);
	const char *ipdst = nftables_gui_rule_attr_get_str(r,
												NFTABLES_GUI_RULE_ATTR_IPDST);
	const char *srcnet = nftables_gui_rule_attr_get_str(r,
												NFTABLES_GUI_RULE_ATTR_SRCNETWORK);
	const char *dstnet = nftables_gui_rule_attr_get_str(r,
												NFTABLES_GUI_RULE_ATTR_DSTNETWORK);

	char *opts[11];
	
	opts[0]=strdup(rule_name);
	opts[1]=strdup(action);
	opts[2]=strdup(proto);
	char buf[1024];
	printf("el puerto es %d\n", srcport);
	snprintf(buf, sizeof(buf), "%d", r->srcport);

	opts[3]=buf;
	char buf2[1024];

	snprintf(buf2, sizeof(buf2), "%d", dstport);

	opts[4]=buf;
	opts[5]=strdup(ipsrc);
	opts[6]=strdup(ipdst);
	opts[7]=strdup(srcnet);
	opts[8]=strdup(dstnet);
	opts[9]="Delete this table";
	opts[10]="Back";


	int result=print_menu(1,opts, 11,"","test");
	printf("el result  es: %d\n", result);
	if(result == 0)
		return;

	if(result == 10)
		nftables_gui_chain_attr_unset_rule(ch, nrule-1);
	
	if(result == 11)
		return;
		

}

struct rule * get_rule(struct chain *ch, int nrule)
{
	struct  rule *cur, *tmp;
	int pos = 0;
	if( ch == NULL )
		return;
	
	list_for_each_entry_safe(cur, tmp, &ch->rules, head){
		
			if( pos == nrule-1)
				break;
			pos++;
	}
	
	if(cur == NULL) 
		return;

	return cur;
}

void create_rule(struct chain *ch)
{
	struct rule *r;
	char *opts[9]={
		"Rule name:",
		"Action:",
		"Protocol:",
		"Src port:",
		"Dst port:",
		"Ip src:",
		"Ip dst:",
		"Src network:",
		"Dst network:"
	};
	char *opts_value[9];


	if(ch == NULL)
		return;

	form_create(9, opts, opts_value);
	
	r=nftables_gui_rule_alloc();
	if( r == NULL)
		return;
	nftables_gui_rule_attr_set_str(r,NFTABLES_GUI_RULE_ATTR_RULE_NAME, opts_value[0]);
	nftables_gui_rule_attr_set_str(r,NFTABLES_GUI_RULE_ATTR_ACTION, opts_value[1]);
	nftables_gui_rule_attr_set_str(r,NFTABLES_GUI_RULE_ATTR_PROTO, opts_value[2]);	
	nftables_gui_rule_attr_set_port(r,NFTABLES_GUI_RULE_ATTR_SRCPORT, atoi(opts_value[3]));
	nftables_gui_rule_attr_set_port(r,NFTABLES_GUI_RULE_ATTR_DSTPORT, atoi(opts_value[4]));	
	nftables_gui_rule_attr_set_str(r,NFTABLES_GUI_RULE_ATTR_IPSRC, opts_value[5]);
	nftables_gui_rule_attr_set_str(r,NFTABLES_GUI_RULE_ATTR_IPDST, opts_value[6]);
	nftables_gui_rule_attr_set_str(r,NFTABLES_GUI_RULE_ATTR_SRCNETWORK, opts_value[7]);
	nftables_gui_rule_attr_set_str(r,NFTABLES_GUI_RULE_ATTR_DSTNETWORK, opts_value[8]);

	nftables_gui_chain_attr_set_rule(ch, NFTABLES_GUI_CHAIN_ATTR_RULE, r);

}

struct chain * get_chain(struct table *t, int nchain){
	struct chain *cur,*tmp;
	int pos=0;
	printf("el numero de chain en get_chain es %d\n", nchain);
	list_for_each_entry_safe(cur, tmp,  &t->chains, head){
		 		 
		if( pos == nchain-1)
			break;
		pos++;
	}
	printf("el nombre de la chain es %s\n", cur->chain_name);
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

	 result=print_menu(1, tables_name, 4, "", "select a familty");
	 
	 char *opts[5];
	 char *opts_value[5];

	 switch(result){

			
			
			case 1:

			nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_FAMILY, "ip");
			//create the table with family ip and get the name of table
			opts[0]="Table name";
			form_create(1, opts, opts_value);
			nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
						opts_value[0]);
			
			break;

			case 2:  /* arp family */
			   nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_FAMILY, "arp");
			  //create the table with family arp and get the name of table
			  opts[0]="Table name";
			  form_create(1, opts, opts_value);
			  nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
							opts_value[0]);

			  break;

		case 3:  /* ip6 family */
			   nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_FAMILY, "ip6");
			  //create the table with family arp and get the name of table
			  opts[0]="Table name";
			  form_create(1, opts, opts_value);
			  nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
							opts_value[0]);

			  break;

			case 4:  /* bridge	family */
			   nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_FAMILY, "bridge");
			  //create the table with family arp and get the name of table
			  opts[0]="Table name";
			  form_create(1, opts, opts_value);
			  nftables_gui_table_attr_set_str(t1, NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
							opts_value[0]);

			  break;
  }
	 /*Making the table */
	 int system_result=0;
	 char buf[1024];
	 snprintf(buf, sizeof(buf), "nft add table %s %s", t1->family, t1->table_name);
	 system_result= system(buf);

}
