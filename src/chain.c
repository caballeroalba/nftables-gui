#include "chain.h"
#include <string.h>


struct chain {
  struct list_head rules;
  const char *chain_name;
  const char *hook;
  uint32_t num_rules;

  uint32_t flags;
};


struct chain *nftables_gui_chain_alloc(void)
{
	struct chain *c;

	c = malloc(sizeof(struct chain));
	if (c ==  NULL)
		return NULL;

	INIT_LIST_HEAD(&c->rules);

	return c;
}

void nftables_gui_chain_free(struct chain *c)
{
	int i;
	struct rule *r, *tmp;

	if (c->flags & (1 << NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME))
		xfree(c->chain_name);
  
  if(c->flags & ( 1 << NFTABLES_GUI_CHAIN_ATTR_HOOK))
    xfree(c->hook);

	list_for_each_entry_safe(r, tmp, &c->rules, head) {
		list_del(&r->head);
		nftables_gui_rule_free(r);
	}

	xfree(c);
}

void nftables_gui_chain_attr_unset_rule(struct chain *c,
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

	if (attr > NFTABLES_GUI_CHAIN_ATTR_MAX)
		return;

	switch (attr) {
	case NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME:
		if (c->chain_name)
			xfree(c->chain_name);

		c->chain_name = strdup(data);
		break;

  case NFTABLES_GUI_CHAIN_ATTR_HOOK:
    if(c->hook)
      xfree(c->hook);
    
    c->hook=strdup(data);
    break;

	case NFTABLES_GUI_CHAIN_ATTR_RULE:
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

void nftables_gui_chain_attr_set_str(struct chain *con,
					uint16_t attr, const char *data)
{
	nftables_gui_chain_set_data(con, attr, data);
}

void nftables_gui_chain_attr_set_rule(struct chain *con,
					  uint16_t attr, struct rule *data)
{
	nftables_gui_chain_set_data(con, attr, data);
}

const void *nftables_gui_chain_attr_get_data(struct chain *c,
					      uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct rule *rule;

	if (!(c->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case NFTABLES_GUI_CHAIN_ATTR_CHAIN_NAME:
		return c->chain_name;
	case NFTABLES_GUI_CHAIN_ATTR_NUM_RULES:
		return &c->num_rules;

  case NFTABLES_GUI_CHAIN_ATTR_HOOK:
    return c->hook;
	case NFTABLES_GUI_CHAIN_ATTR_RULE:
		list_for_each_entry(rule, &c->rules, head) {
			if (i == pos)
				break;

			i++;
		}

		return rule;
	}
	return NULL;
}

uint32_t nftables_gui_chain_attr_get_u32(struct chain *con,
					  uint16_t attr)
{
	const void *ret = nftables_gui_chain_attr_get_data(con, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *nftables_gui_chain_attr_get_str(struct chain *con,
					     uint16_t attr)
{
	return nftables_gui_chain_attr_get_data(con, attr, 0);
}

struct rule *nftables_gui_chain_attr_get_coche(struct chain *con,
					         uint16_t attr, uint32_t pos)
{
	return (struct rule *)nftables_gui_chain_attr_get_data(con, attr,
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
