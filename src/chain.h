#include "rule.h"


enum {
  NFTGUI_CHAIN_CHAIN_NAME,
  NFTGUI_CHAIN_HOOK,
  NFTGUI_CHAIN_RULE,
  NFTGUI_CHAIN_NUM_RULES,
  __NFTGUI_CHAIN_MAX


};

#define NFTGUI_CHAIN_MAX (__NFTGUI_CHAIN_MAX -1)

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

void nftgui_chain_unset_rule(struct chain *c,
                                              uint32_t pos);

//void nftables_gui_chain_set_data(struct chain *c, uint16_t attr, 
//                                  const void *data);
void nftgui_chain_set_str(struct chain *c, uint16_t attr,
                                          const char *data);
void nftgui_chain_set_rule(struct chain *con,
                                            uint16_t attr, struct rule *r);


const void *nftables_gui_attr_get_data(struct chain *c, uint16_t attr,
                                        uint32_t pos);

uint32_t nftgui_chain_get_u32(struct chain *c,
                                              uint16_t attr);
const char *nftgui_chain_get_str(struct chain *con,
                                                 uint16_t attr);
struct rule *nftgui_chain_get_rule(struct chain *c,
                                                     uint16_t attr, uint32_t pos);

int nftables_gui_chain_snprintf(char *buf, size_t size, struct chain *c);
