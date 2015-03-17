#include "rule.h"


enum {
  NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME,
  NFTABLES_GUI_CHAIN_ATTR_HOOK,
  NFTABLES_GUI_CHAIN_ATTR_RULE,
  NFTABLES_GUI_CHAIN_ATTR_NUM_RULES,
  __NFTABLES_GUI_CHAIN_ATTR_MAX


};

#define NFTABLES_GUI_CHAIN_ATTR_MAX (__NFTABLES_GUI_CHAIN_ATTR_MAX -1)

#define xfree(ptr)    free((void *)ptr);


struct chain {
  struct list_head head;
  struct list_head rules;
  const char *chain_name;
  const char *hook;
  uint32_t num_rules;

  uint32_t flags;
};

struct chain *nftables_gui_chain_alloc(void);
void nftables_gui_chain_free(struct chain *);

void nftables_gui_chain_attr_unset_rule(struct chain *c,
                                              uint32_t pos);

//void nftables_gui_chain_set_data(struct chain *c, uint16_t attr, 
//                                  const void *data);
void nftables_gui_chain_attr_set_str(struct chain *c, uint16_t attr,
                                          const char *data);
void nftables_gui_chain_attr_set_rule(struct chain *con,
                                            uint16_t attr, struct rule *r);


const void *nftables_gui_attr_get_data(struct chain *c, uint16_t attr,
                                        uint32_t pos);

uint32_t nftables_gui_chain_attr_get_u32(struct chain *c,
                                              uint16_t attr);
const char *nftables_gui_chain_attr_get_str(struct chain *con,
                                                 uint16_t attr);
struct rule *nftables_gui_chain_attr_get_rule(struct chain *c,
                                                     uint16_t attr, uint32_t pos);

int nftables_gui_chain_snprintf(char *buf, size_t size, struct chain *c);