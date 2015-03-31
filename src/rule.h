#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

enum {
    NFTABLES_GUI_RULE_ATTR_RULE_NAME,
    NFTABLES_GUI_RULE_ATTR_ACTION,
    NFTABLES_GUI_RULE_ATTR_PROTO,
    NFTABLES_GUI_RULE_ATTR_SRCPORT,
    NFTABLES_GUI_RULE_ATTR_DSTPORT,
    NFTABLES_GUI_RULE_ATTR_IPSRC,
    NFTABLES_GUI_RULE_ATTR_IPDST,
    NFTABLES_GUI_RULE_ATTR_SRCNETWORK,
    NFTABLES_GUI_RULE_ATTR_DSTNETWORK,
    NFTABLES_GUI_RULE_ATTR_INTERFACE,
    NFTABLES_GUI_RULE_ATTR_ID,
    __NFTABLES_GUI_RULE_ATTR_MAX
};

#define NFTABLES_GUI_RULE_ATTR_MAX (__NFTABLES_GUI_RULE_ATTR_MAX - 1)

#define xfree(ptr)      free((void *)ptr);

struct rule {
	struct list_head head;
  uint32_t	id;
	const char  *rule_name;
	const char	*action;
  const char  *proto;
  uint32_t     srcport;
  uint32_t     dstport;
  const char *ipsrc;
  const char *ipdst;
  const char *srcnetwork;
  const char *dstnetwork;
  const char *interface;

	uint32_t	flags;
};

struct rule *nftables_gui_rule_alloc(void);
void nftables_gui_rule_free(struct rule *);

bool nftables_gui_rule_attr_is_set(const struct rule *c, uint16_t attr);

void nftables_gui_rule_attr_unset(struct rule *c, uint16_t attr);

void nftables_gui_rule_attr_set_data(struct rule *c, uint16_t attr, const void *data,
                 uint32_t data_len);
void nftables_gui_rule_attr_set_u32(struct rule *c, uint16_t attr, uint32_t data);
void nftables_gui_rule_attr_set_str(struct rule *c, uint16_t attr, const char *data);
void nftables_gui_rule_attr_set_port(struct rule *c, uint16_t attr, uint32_t data);

const void *nftables_gui_rule_attr_get_data(struct rule *c, uint16_t attr);
uint32_t nftables_gui_rule_attr_get_u32(struct rule *c, uint16_t attr);
const char *nftables_gui_rule_attr_get_str(struct rule *c, uint16_t attr);

int nftables_gui_rule_snprintf(char *buf, size_t size, struct rule *c);
