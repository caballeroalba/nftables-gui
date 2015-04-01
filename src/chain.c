#include "chain.h"
#include <string.h>




struct chain *nftables_gui_chain_alloc(void)
{
	struct chain *c;

	c = calloc(1,sizeof(struct chain));
	if (c ==  NULL)
		return NULL;

	INIT_LIST_HEAD(&c->rules);
    c->flags |= (1 << NFTGUI_CHAIN_NUM_RULES);
	return c;
}

void nftables_gui_chain_free(struct chain *c)
{

	struct rule *r, *tmp;

	if (c->flags & (1 << NFTGUI_CHAIN_CHAIN_NAME))
		xfree(c->chain_name);
  
  if(c->flags & ( 1 << NFTGUI_CHAIN_HOOK))
    xfree(c->hook);

	list_for_each_entry_safe(r, tmp, &c->rules, head) {
		list_del(&r->head);
		nftables_gui_rule_free(r);
	}

	xfree(c);
}

void nftgui_chain_unset_rule(struct chain *c,
					  uint32_t pos)
{
	int i = 0;
	struct rule *r, *tmp;

	if (pos < 0 || pos > c->num_rules)
		return;

	list_for_each_entry_safe(r, tmp, &c->rules, head) {
		if (i == pos) {
			list_del(&r->head);
			nftables_gui_rule_free(r);
			break;
		}

		i++;
	}

	c->num_rules--;
}

static void nftables_gui_chain_set_data(struct chain *c,
					 uint16_t attr, const void *data)
{
	struct rule *r;

	if (attr > NFTGUI_CHAIN_MAX)
		return;

	switch (attr) {
	case NFTGUI_CHAIN_CHAIN_NAME:
		if (c->chain_name)
			xfree(c->chain_name);

		c->chain_name = strdup(data);
		break;

  case NFTGUI_CHAIN_HOOK:
    if(c->hook)
      xfree(c->hook);
    
    c->hook=strdup(data);
    break;

	case NFTGUI_CHAIN_RULE:
		if (c->num_rules > 99) {
			printf("too much rules\n");
			break;
		}
		r = (struct rule *)data;
		list_add(&r->head, &c->rules);
		c->num_rules++;
		break;
	}

	c->flags |= (1 << attr);
}

void nftgui_chain_set_str(struct chain *con,
					uint16_t attr, const char *data)
{
	nftables_gui_chain_set_data(con, attr, data);
}

void nftgui_chain_set_rule(struct chain *con,
					  uint16_t attr, struct rule *r)
{
	nftables_gui_chain_set_data(con, attr, r);
}

const void *nftgui_chain_get_data(struct chain *c,
					      uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct rule *rule;

	if (!(c->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case NFTGUI_CHAIN_CHAIN_NAME:
		return c->chain_name;
	case NFTGUI_CHAIN_NUM_RULES:
		return &c->num_rules;

  case NFTGUI_CHAIN_HOOK:
    return c->hook;
	case NFTGUI_CHAIN_RULE:
		list_for_each_entry(rule, &c->rules, head) {
			if (i == pos)
				break;

			i++;
		}

		return rule;
	}
	return NULL;
}

uint32_t nftgui_chain_get_u32(struct chain *con,
					  uint16_t attr)
{
	const void *ret = nftgui_chain_get_data(con, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *nftgui_chain_get_str(struct chain *con,
					     uint16_t attr)
{
	return nftgui_chain_get_data(con, attr, 0);
}

struct rule *nftgui_chain_get_rule(struct chain *con,
					         uint16_t attr, uint32_t pos)
{
	return (struct rule *)nftgui_chain_get_data(con, attr,
								 pos);
}

int nftables_gui_chain_snprintf(char *buf, size_t size,
				 struct chain *con)
{
	int ret = 0;
	struct rule *c;

	ret += snprintf(buf, size,
			"el chain propiedad de %s, tiene %d y son:\n",
			con->chain_name, con->num_rules);

	list_for_each_entry(c, &con->rules, head) {
		ret += nftables_gui_rule_snprintf(buf + ret, size - ret, c);
		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
