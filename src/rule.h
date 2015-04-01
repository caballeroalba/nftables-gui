#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

enum {
    NFTGUI_RULE_NAME,
    NFTGUI_RULE_ACTION,
    NFTGUI_RULE_PROTO,
    NFTGUI_RULE_SRCPORT,
    NFTGUI_RULE_DSTPORT,
    NFTGUI_RULE_IPSRC,
    NFTGUI_RULE_IPDST,
    NFTGUI_RULE_SRCNETWORK,
    NFTGUI_RULE_DSTNETWORK,
    NFTGUI_RULE_INTERFACE,
    NFTGUI_RULE_ID,
    __NFTGUI_RULE_MAX
};

#define NFTGUI_RULE_MAX (__NFTGUI_RULE_MAX - 1)

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

bool nftgui_rule_is_set(const struct rule *c, uint16_t attr);

void nftgui_rule_unset(struct rule *c, uint16_t attr);

void nftgui_rule_set_data(struct rule *c, uint16_t attr, const void *data,
                 uint32_t data_len);
void nftgui_rule_set_u32(struct rule *c, uint16_t attr, uint32_t data);
void nftgui_rule_set_str(struct rule *c, uint16_t attr, const char *data);
void nftgui_rule_set_port(struct rule *c, uint16_t attr, uint32_t data);

const void *nftgui_rule_get_data(struct rule *c, uint16_t attr);
uint32_t nftgui_rule_get_u32(struct rule *c, uint16_t attr);
const char *nftgui_rule_get_str(struct rule *c, uint16_t attr);

int nftables_gui_rule_snprintf(char *buf, size_t size, struct rule *c);
