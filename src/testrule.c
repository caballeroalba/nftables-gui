#include "rule.h"



int main(void)
{

	struct rule *r1;
	char info[4000];
	r1=nftables_gui_rule_alloc();
  nftables_gui_rule_attr_set_str(r1,NFTABLES_GUI_RULE_ATTR_RULE_NAME,"REGLA 1");
  nftables_gui_rule_attr_set_port(r1,NFTABLES_GUI_RULE_ATTR_SRCPORT,5);
  nftables_gui_rule_snprintf(info,sizeof(info),r1);
  printf("%s\n",info);
  nftables_gui_rule_free(r1);
  return 0;
}
