#include "chain.h"


enum {
  NFTGUI_TABLE_TABLE_NAME,
  NFTGUI_TABLE_FAMILY,
  NFTGUI_TABLE_CHAIN,
  NFTGUI_TABLE_NUM_CHAINS,
  __NFTGUI_TABLE_MAX


};

#define NFTGUI_TABLE_MAX (__NFTGUI_TABLE_MAX -1)

#define xfree(ptr)    free((void *)ptr);

struct table {
  struct list_head head;
  struct list_head chains;
  const char *table_name;
  const char *family;
  uint32_t num_chains;

  uint32_t flags;
};


struct table *nftables_gui_table_alloc(void);
void nftables_gui_table_free(struct table *);

void NFTGUI_TABLE_unset_chain(struct table *t,
                                              uint32_t pos);

//void nftgui_table_set_data (struct table *t, uint16_t attr,
//                                        const void *data);
void nftgui_table_set_str(struct table *t, uint16_t attr,
                                          const char *data);
void nftgui_table_set_chain(struct table *t,
                                            uint16_t attr, struct chain *c);
const void *nftgui_table_get_data(struct table *c, uint16_t attr,
                                            uint32_t pos);
uint32_t nftgui_table_get_u32(struct table *t,
                                              uint16_t attr);
const char *nftgui_table_get_str(struct table *ton,
                                                 uint16_t attr);
struct chain *nftgui_table_get_chain(struct table *t,
                                                     uint16_t attr, uint32_t pos);

int nftables_gui_table_snprintf(char *buf, size_t size, struct table *t);

