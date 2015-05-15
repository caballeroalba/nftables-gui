#include "table.h"

int main(void)
{

	struct rule *r1;
	char info[4000];
	r1=nftables_gui_rule_alloc();
  nftables_gui_rule_attr_set_str(r1,NFTABLES_GUI_RULE_ATTR_RULE_NAME,"REGLA 1");
  nftables_gui_rule_attr_set_u32(r1,NFTABLES_GUI_RULE_ATTR_SRCPORT,5);
  nftables_gui_rule_snprintf(info,sizeof(info),r1);
  printf ("la id es %d\n",nftables_gui_rule_attr_get_u32(r1,NFTABLES_GUI_RULE_ATTR_SRCPORT));
	printf("%s\n",info);
  
  struct chain *c;
  c=nftables_gui_chain_alloc();
  nftables_gui_chain_attr_set_rule(c,NFTABLES_GUI_CHAIN_ATTR_RULE,r1);
  nftables_gui_chain_snprintf(info,sizeof(info),c);
  printf("%s\n",info);	
	struct table *t;
  t=nftables_gui_table_alloc();
  nftables_gui_table_attr_set_chain(t,NFTABLES_GUI_TABLE_ATTR_CHAIN,c);
  nftables_gui_table_snprintf(info,sizeof(info),t);
  printf("%s\n",info);
  nftables_gui_chain_free(c);
  return 0;
}
