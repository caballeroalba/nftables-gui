#include "prototypes.h"
#include "screen_work_flow.h"



char buf_screen[MAX_BUFFER_SIZE];

void delete_all_tables()
{
	int result=0;
	result = system("sh deleteTables.sh");
	if( result < 0)
		perror("error al borrar las tablas previas");
}
void list_tables(struct table_list *list){

	struct table *cur,*tmp;
	char *opts[99];
	int i=0;

	if( list->elements == 0)
		return;

	list_for_each_entry_safe(cur,tmp,&list->list,head)
	{			 
	    opts[i]=strdup(nftgui_table_get_str(cur,NFTGUI_TABLE_TABLE_NAME));	
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
	table_name=nftgui_table_get_str(c, NFTGUI_TABLE_TABLE_NAME);
	
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

	char *hook;
	char *value;
	int test=0;
	while(test == 0){
		form_create(2, opts, opts_value);
		hook=(strdup(opts_value[1]));
		value=trim(hook);
		if(strcmp(value, "input" ) == 0)
			test=1;
		if(strcmp(value, "output" ) == 0)
			test=1;
	}




	 struct chain *chain;
	 
   chain=nftables_gui_chain_alloc();
   nftgui_chain_set_str(chain, NFTGUI_CHAIN_CHAIN_NAME, opts_value[0]);
   nftgui_chain_set_str(chain, NFTGUI_CHAIN_HOOK, opts_value[1]);
   nftgui_table_set_chain(cur, NFTGUI_TABLE_CHAIN, chain);

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
	
		

		chain=nftgui_table_get_chain(cur, NFTGUI_TABLE_CHAIN, b);

		if( chain == NULL)
		 return;

		opts[b]=strdup(nftgui_chain_get_str( chain, NFTGUI_CHAIN_CHAIN_NAME));
		
	}

	const char *table_name=nftgui_table_get_str(cur, NFTGUI_TABLE_TABLE_NAME);
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

	char buf[1024];
	int result=0;

	snprintf(buf, sizeof(buf), "nft delete table %s", c->table_name );
	result=system(buf);
	if( result < 0 )
		perror("can't delete this table");
	list_del(&c->head);
	list->elements--;
	nftgui_table_free(c);

	

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

	const char *chain_name=nftgui_chain_get_str(ch,
							NFTGUI_CHAIN_CHAIN_NAME);
	const char *hook=nftgui_chain_get_str(ch,
							NFTGUI_CHAIN_HOOK);

	char *opts[6];
	
	opts[0]="";
	opts[1]=strdup(chain_name);
	opts[2]=strdup(hook);
	opts[3]="Create rule";
	opts[4]="List rules";
	opts[5]="Delete this Chain";
	opts[6]="Back";
	

	const char* table_name=nftgui_table_get_str(t,
							NFTGUI_TABLE_TABLE_NAME);
	char buf[1024];

	snprintf(buf, sizeof(buf), "You are in %s table, in "
			"%s chain, \n please select a option", table_name,
															ch->chain_name);
	int result=print_menu(1, opts, 5, "", buf);
	
	result--;
	int test=0;

	if( result == 0)
		return;
	switch( result ){
		
		case 3:
			create_rule(t, ch);		
			break;

		case 4:
			list_rules(ch);
			
			break;

		case 5:
			
			
			snprintf(buf, sizeof(buf), "nft delete chain %s %s",t->table_name, ch->chain_name);	

			test=system(buf);
			if ( test < 0 )
				perror("Can't delete this chain");
			nftgui_table_unset_chain(t, nchain);
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

		opts[i]=strdup(nftgui_rule_get_str(cur,
					NFTGUI_RULE_NAME));
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
	
	struct rule *r;
	if( ch == NULL )
		return;

	if( nrule == 0 )
		return;

	r=get_rule(ch, nrule);
		
	const char *rule_name= nftgui_rule_get_str(r,
										 		NFTGUI_RULE_NAME);
	const char *action = nftgui_rule_get_str(r,
												NFTGUI_RULE_ACTION);
	const char *proto = nftgui_rule_get_str(r,
												NFTGUI_RULE_PROTO);
	uint32_t srcport = nftgui_rule_get_u32(r,
												NFTGUI_RULE_SRCPORT);
	uint32_t dstport = nftgui_rule_get_u32(r,
												NFTGUI_RULE_DSTPORT);
	/* to develop in the future 
	const char *ipsrc = nftgui_rule_get_str(r,
												NFTGUI_RULE_IPSRC);
	const char *ipdst = nftgui_rule_get_str(r,
												NFTGUI_RULE_IPDST);
	const char *srcnet = nftgui_rule_get_str(r,
												NFTGUI_RULE_SRCNETWORK);
	const char *dstnet = nftgui_rule_get_str(r,
												NFTGUI_RULE_DSTNETWORK);
 */
	char *opts[7];
	
	opts[0]=strdup(rule_name);
	opts[1]=strdup(action);
	opts[2]=strdup(proto);
	char buf[1024];
	
	snprintf(buf, sizeof(buf), "%d", srcport);

	opts[3]=buf;
	char buf2[1024];

	snprintf(buf2, sizeof(buf2), "%d", dstport);

	opts[4]=buf2;
	/* to develop in the future 
	opts[5]=strdup(ipsrc);
	opts[6]=strdup(ipdst);
	opts[7]=strdup(srcnet);
	opts[8]=strdup(dstnet);
	*/
	opts[5]="Delete this rule";
	opts[6]="Back";


	int result=print_menu(1,opts, 7,"","test");
	
	if(result == 0)
		return;

	if(result == 10)
		
		
		nftgui_chain_unset_rule(ch, nrule-1);
	
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

void create_rule(struct table *t, struct chain *ch)
{
	struct rule *r;
	char *opts[5]={
		"Rule name:",
		"Action:",
		"Protocol:",
		"Src port:",
		"Dst port:"
	};
	char *opts_value[5];

	if( ch == NULL)
		return;
	
	int test = 1;
	int test2 = 1;
	
	while( test == 1 ||  test2 == 1)
	{
		form_create(5, opts, opts_value);
		char *action=trim(strdup(opts_value[1]));

		if( strcmp(action, "accept") == 0 )
			test=0;
		if( strcmp(action, "reject") == 0 )
			test=0;
		if( strcmp(action, "drop") == 0 )
			test=0;

		char *proto=trim(strdup(opts_value[2]));
		
		if( strcmp(proto, "tcp") == 0)
			test2=0;
		if( strcmp(proto, "udp") == 0)
			test2=0;
		if (strlen(proto) == 0)
			test2=0;
		if (strlen(proto) == 0)
			test2=0;
	}
	
	r=nftables_gui_rule_alloc();
	if( r == NULL)
		return;
	nftgui_rule_set_str(r,NFTGUI_RULE_NAME, opts_value[0]);
	nftgui_rule_set_str(r,NFTGUI_RULE_ACTION, opts_value[1]);
	nftgui_rule_set_str(r,NFTGUI_RULE_PROTO, opts_value[2]);	
	nftgui_rule_set_port(r,NFTGUI_RULE_SRCPORT, atoi(opts_value[3]));
	nftgui_rule_set_port(r,NFTGUI_RULE_DSTPORT, atoi(opts_value[4]));	
	
	/* to develop in the future 
	nftgui_rule_set_str(r,NFTGUI_RULE_IPSRC, opts_value[5]);
	nftgui_rule_set_str(r,NFTGUI_RULE_IPDST, opts_value[6]);
	nftgui_rule_set_str(r,NFTGUI_RULE_SRCNETWORK, opts_value[7]);
	nftgui_rule_set_str(r,NFTGUI_RULE_DSTNETWORK, opts_value[8]);
	*/

	nftgui_chain_set_rule(ch, NFTGUI_CHAIN_RULE, r);
	/* making the rule */
	
	char *proto=trim(strdup(r->proto));
	char buf[1024];
	
	if ( strlen(proto) == 0 ){
		
		snprintf(buf, sizeof(buf), "nft add rule %s %s %s ", t->table_name, ch->chain_name, r->action );
		
		int result= system(buf);

		if( result < 0 )
		perror("Can't add the rule");

		
	}else if(atoi(opts_value[3]) != 0 ){
		
		snprintf(buf, sizeof(buf), " nft add rule %s %s %s sport %d  %s", t->table_name, ch->chain_name, r->proto, r->srcport, r->action );
		int result= system(buf);

		if( result < 0 )
			perror("Can't add the rule");

	}else if (atoi(opts_value[4]) !=0 ){
		
		snprintf(buf, sizeof(buf), " nft add rule %s %s %s dport %d %s", 
				t->table_name, ch->chain_name, r->proto, r->dstport,
				r->action);
		int result= system(buf);

		if( result < 0 )
			perror("Can't add the rule");

	
	}else if (atoi(opts_value[3]) !=0 && atoi(opts_value[4]) != 0 ){

		snprintf(buf, sizeof(buf), "nft add rule %s %s %s sport %d %s dport %d %s",
				t->table_name, ch->chain_name, r->proto, r->srcport, r->proto,
				r->dstport, r->action);
		int result= system(buf);

		if( result < 0 )
			perror("Can't add the rule");

	}else{
		return;
	
	}

	
}

struct chain * get_chain(struct table *t, int nchain){
	struct chain *cur,*tmp;
	int pos=0;
	
	list_for_each_entry_safe(cur, tmp,  &t->chains, head){
		 		 
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

	 result=print_menu(1, tables_name, 4, "", "select a family");
	 
	 char *opts[5];
	 char *opts_value[5];

	 switch(result){

			
			
			case 1:

			nftgui_table_set_str(t1, NFTGUI_TABLE_FAMILY, "ip");
			//create the table with family ip and get the name of table
			opts[0]="Table name";
			int test=0;
			while ( test == 0 )
			{
				form_create(1, opts, opts_value);
				char *name=trim(strdup(opts_value[0]));
				if( strcmp(name, "") !=0)
					test=1;
			}
			nftgui_table_set_str(t1, NFTGUI_TABLE_TABLE_NAME,
						opts_value[0]);
			
			break;

			case 2:  /* arp family */
			   nftgui_table_set_str(t1, NFTGUI_TABLE_FAMILY, "arp");
			  //create the table with family arp and get the name of table
			  opts[0]="Table name";
				int test1=0;
				while ( test1 == 0 )
				{
					form_create(1, opts, opts_value);
					char *name=trim(strdup(opts_value[0]));
					if( strcmp(name, "") !=0)
						test1=1;
				}
			  
			  nftgui_table_set_str(t1, NFTGUI_TABLE_TABLE_NAME,
							opts_value[0]);

			  break;

		case 3:  /* ip6 family */
			   nftgui_table_set_str(t1, NFTGUI_TABLE_FAMILY, "ip6");
			  //create the table with family arp and get the name of table
			  opts[0]="Table name";
			  int test2=0;
				while ( test2 == 0 )
				{
					form_create(1, opts, opts_value);
					char *name=trim(strdup(opts_value[0]));
					if( strcmp(name, "") !=0)
						test2=1;
				}
			  nftgui_table_set_str(t1, NFTGUI_TABLE_TABLE_NAME,
							opts_value[0]);

			  break;

			case 4:  /* bridge	family */
			   nftgui_table_set_str(t1, NFTGUI_TABLE_FAMILY, "bridge");
			  //create the table with family arp and get the name of table
			  opts[0]="Table name";
			  int test3=0;
				while ( test3 == 0 )
				{
					form_create(1, opts, opts_value);
					char *name=trim(strdup(opts_value[0]));
					if( strcmp(name, "") !=0)
						test3=1;
				}
			  nftgui_table_set_str(t1, NFTGUI_TABLE_TABLE_NAME,
							opts_value[0]);

			  break;
  }
	 /*Making the table */
	 int system_result=0;
	 char *table[3];

	 table[0]="nft"; 
	 table[1]= trim(strdup(t1->family));
	 
	 
	 system_result=create_table_nft( 3, table);
	
}

char *trim(char *s)
{
	char *start = s;

		  /* Nos comemos los espacios al inicio */
	 while(*start && isspace(*start))
		 ++start;
	 char *i = start;
	 char *end = start;
	 /* Nos comemos los espacios al final */
	 while(*i)
	 {
		 if( !isspace(*(i++)) )
			 end = i;
	 }

	 /* Escribimos el terminados */
	 *end = 0;
	 return start;
}

void menubar_controller(int ntable, struct table_list *list);
