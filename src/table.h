#include "chain.h"


enum {
  NFTABLES_GUI_TABLE_ATTR_TABLE_NAME,
  NFTABLES_GUI_TABLE_ATTR_FAMILY,
  NFTABLES_GUI_TABLE_ATTR_CHAIN,
  NFTABLES_GUI_TABLE_ATTR_NUM_CHAINS,
  __NFTABLES_GUI_TABLE_ATTR_MAX


};

#define NFTABLES_GUI_TABLE_ATTR_MAX (__NFTABLES_GUI_TABLE_ATTR_MAX -1)

#define xfree(ptr)    free((void *)ptr);

struct table {
  
  struct list_head chains;
  const char *table_name;
  const char *family;
  uint32_t num_chains;

  uint32_t flags;
};


struct table *nftables_gui_table_alloc(void);
void nftables_gui_table_free(struct table *);

void nftables_gui_table_attr_unset_chain(struct table *t,
                                              uint32_t pos);

//void nftables_gui_table_attr_set_data (struct table *t, uint16_t attr,
//                                        const void *data);
void nftables_gui_table_attr_set_str(struct table *t, uint16_t attr,
                                          const char *data);
void nftables_gui_table_attr_set_chain(struct table *t,
                                            uint16_t attr, struct chain *c);
const void *nftables_gui_table_attr_get_data(struct table *c, uint16_t attr,
                                            uint32_t pos);
uint32_t nftables_gui_table_attr_get_u32(struct table *t,
                                              uint16_t attr);
const char *nftables_gui_table_attr_get_str(struct table *ton,
                                                 uint16_t attr);
struct chain *nftables_gui_table_attr_get_chain(struct table *t,
                                                     uint16_t attr, uint32_t pos);

int nftables_gui_table_snprintf(char *buf, size_t size, struct table *t);
