#include <stdio.h>
#include "table.h"
#include "screen_work_flow.h"

/* prototipes*/
void create_table(struct table *t);
void list_tables();

int main(void)
{
  struct list_head table_list; 
  INIT_LIST_HEAD(&table_list);
  char *choices[3]={
    "Create table",
    "List tables"
  };


  while (1)
  {
    int result=print_menu(1,choices,2,"prueba","Welcome to nftables-gui,"
      "please select a option");
    if(result==1)
    {
     struct table *t1;
     t1=nftables_gui_table_alloc();
     t1=nftables_gui_table_alloc();
     create_table(t1);
     //list_add(&t1->head,&table_list);
    }else if(result==2)
    {
      list_tables();
    } 
  }

}

void list_tables(struct list_head *list){
//  char *choices[99];
  struct table *t,*tmp;
  int i=0;
  list_for_each_entry_safe(t,tmp,list,head){
   // printf("%s\n",nftables_gui_table_attr_get_str(t,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME));
    //choices[i]=t->table_name;
  printf("hola\n");
  }
  return;
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
      nftables_gui_table_snprintf(info,sizeof(info),t1);
      printf("%s\n",info);
      break;

    case 2:  /* arp family */
       nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"ARP");
      //create the table with family arp and get the name of table
      opts[0]="Table name";
      form_create(1,opts,opts_value);
      nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
                                        opts_value[0]);
      nftables_gui_table_snprintf(info,sizeof(info),t1);
      printf("%s\n",info);
      break;
    case 3:  /* inet family */
       nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"INET");
      //create the table with family arp and get the name of table
      opts[0]="Table name";
      form_create(1,opts,opts_value);
      nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
                                        opts_value[0]);
      nftables_gui_table_snprintf(info,sizeof(info),t1);
      printf("%s\n",info);
      break;
    case 4:  /*nat family */
       nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_FAMILY,"NAT");
      //create the table with family arp and get the name of table
      opts[0]="Table name";
      form_create(1,opts,opts_value);
      nftables_gui_table_attr_set_str(t1,NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
                                        opts_value[0]);
      nftables_gui_table_snprintf(info,sizeof(info),t1);
      printf("%s\n",info);
      break;





  }

  

}
