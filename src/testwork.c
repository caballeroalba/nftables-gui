#include <stdio.h>
#include "table.h"
#include "screen_work_flow.h"

/* prototipes*/
void create_table(struct table *t1);
void list_tables();

int main(void)
{
  struct table *t1;
  char *choices[10]={
    "Create table",
    "List tables"
    };

  int result=print_menu(1,choices,2,"prueba","Welcome to nftables-gui,"
      "please select a option");
  if(result==1)
  {
    t1=nftables_gui_table_alloc();
    create_table(t1);
  }else if(result==2)
  {
    list_tables();
  }
  
  char info[250];
  nftables_gui_table_snprintf(info,sizeof(info),t1);
  printf("%s\n",info);


}

void list_tables(){
}

void create_table(struct table *t1)
{
 // t1=nftables_gui_table_alloc();
  char *tables_name[4]={
    "IP",
    "ARP",
    "INET",
    "NAT"
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



  }



}
