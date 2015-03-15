#include "chain.h"



int main(void)
{

	struct rule *r1;
	char info[4000];
	r1=nftables_gui_rule_alloc();
  nftables_gui_rule_attr_set_str(r1,NFTABLES_GUI_RULE_ATTR_RULE_NAME,"REGLA 1");
  nftables_gui_rule_attr_set_port(r1,NFTABLES_GUI_RULE_ATTR_SRCPORT,5);
  nftables_gui_rule_snprintf(info,sizeof(info),r1);
  printf("%s\n",info);
  struct chain *c;
  c=nftables_gui_chain_alloc();
  nftables_gui_chain_attr_set_rule(c,NFTABLES_GUI_CHAIN_ATTR_RULE,r1);
//  nftables_gui_rule_free(r1);
  nftables_gui_chain_snprintf(info,sizeof(info),c);
  printf("%s\n",info);
  return 0;
}
