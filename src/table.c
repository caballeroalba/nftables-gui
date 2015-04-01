#include "table.h"
#include <string.h>



struct table *nftgui_table_alloc(void)
{
	struct table *c;

	c = calloc(1,sizeof(struct table));
	if (c ==  NULL)
		return NULL;

	INIT_LIST_HEAD(&c->chains);
    c->flags |= (1 << NFTGUI_TABLE_NUM_CHAINS);
	return c;
}

void nftgui_table_free(struct table *c)
{

	struct chain *r, *tmp;

	if (c->flags & (1 << NFTGUI_TABLE_TABLE_NAME))
		xfree(c->table_name);

  	if(c->flags & ( 1 << NFTGUI_TABLE_FAMILY))
    		xfree(c->family);

	list_for_each_entry_safe(r, tmp, &c->chains, head) {
		list_del(&r->head);
		nftables_gui_chain_free(r);
	}

	xfree(c);
}

void nftgui_table_unset_chain(struct table *c,
					  uint32_t pos)
{
	int i = 0;
	struct chain *r, *tmp;

	if (pos < 0 || pos > c->num_chains)
		return;

	list_for_each_entry_safe(r, tmp, &c->chains, head) {
		if (i == pos) {
			list_del(&r->head);
			nftables_gui_chain_free(r);
			break;
		}

		i++;
	}

	c->num_chains--;
}

static void nftgui_table_set_data(struct table *c,
					 uint16_t attr, const void *data)
{
	struct chain *r;

	if (attr > NFTGUI_TABLE_MAX)
		return;

	switch (attr) {
	case NFTGUI_TABLE_TABLE_NAME:
		if (c->table_name)
			xfree(c->table_name);

		c->table_name = strdup(data);
		break;

  case NFTGUI_TABLE_FAMILY:
    if(c->family)
      xfree(c->family);
    
    c->family=strdup(data);
    break;

	case NFTGUI_TABLE_CHAIN:
		if (c->num_chains > 99) {
			printf("too much chains\n");
			break;
		}
		r = (struct chain *)data;
		list_add(&r->head, &c->chains);
		c->num_chains++;
		break;
	}

	c->flags |= (1 << attr);
}

void nftgui_table_set_str(struct table *con,
					uint16_t attr, const char *data)
{
	nftgui_table_set_data(con, attr, data);
}

void nftgui_table_set_chain(struct table *con,
					  uint16_t attr, struct chain *data)
{
	nftgui_table_set_data(con, attr, data);
}

const void *nftgui_table_get_data(struct table *c,
					      uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct chain *cn;

	if (!(c->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case NFTGUI_TABLE_TABLE_NAME:
		return c->table_name;
	case NFTGUI_TABLE_NUM_CHAINS:
		return &c->num_chains;

  case NFTGUI_TABLE_FAMILY:
    return c->family;
	case NFTGUI_TABLE_CHAIN:
		list_for_each_entry(cn, &c->chains, head) {
			if (i == pos)
				break;

			i++;
		}

		return cn;
	}
	return NULL;
}

uint32_t nftgui_table_get_u32(struct table *con,
					  uint16_t attr)
{
	const void *ret = nftgui_table_get_data(con, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *nftgui_table_get_str(struct table *con,
					     uint16_t attr)
{
	return nftgui_table_get_data(con, attr, 0);
}

struct chain *nftgui_table_get_chain(struct table *con,
					         uint16_t attr, uint32_t pos)
{
	return (struct chain *)nftgui_table_get_data(con, attr,
								 pos);
}

int nftgui_table_snprintf(char *buf, size_t size,
				 struct table *con)
{
	int ret = 0;
	struct chain *c;

	ret += snprintf(buf, size,
			"table %s type %s has %d chains:\n",
			con->table_name,con->family, con->num_chains);

	list_for_each_entry(c, &con->chains, head) {
		ret += nftables_gui_chain_snprintf(buf + ret, size - ret, c);
		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
