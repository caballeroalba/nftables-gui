#include "rule.h"
#include <string.h>




struct rule *nftables_gui_rule_alloc(void)
{
	return (struct rule *)calloc(1,sizeof(struct rule));
}

void nftables_gui_rule_free(struct rule *r)
{
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_RULE_NAME))
		xfree(r->rule_name);

	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_ACTION))
		xfree(r->action);
		
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_PROTO))
		xfree(r->proto);	
	
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_SRCPORT))
		//xfree(r->srcport);

        if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_DSTPORT))
	//	xfree(r->dstport);
		
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_IPSRC))
		xfree(r->ipsrc);
		
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_IPDST))
		xfree(r->ipdst);
		
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_SRCNETWORK))
		xfree(r->srcnetwork);
		
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_DSTNETWORK))
		xfree(r->dstnetwork);
		
	if (r->flags & (1 << NFTABLES_GUI_RULE_ATTR_INTERFACE))
		xfree(r->interface);
		

	xfree(r);
}

bool nftables_gui_rule_attr_is_set(const struct rule *r, uint16_t attr)
{
	return r->flags & (1 << attr);
}

void nftables_gui_rule_attr_unset(struct rule *r, uint16_t attr)
{
	if (!(r->flags & (1 << attr)))
		return;

	switch (attr) {
	case NFTABLES_GUI_RULE_ATTR_RULE_NAME:
		if (r->rule_name) {
			xfree(r->rule_name);
			r->rule_name = NULL;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_ACTION:
		if (r->action) {
			xfree(r->action);
			r->action = NULL;
		}
		break;
        case NFTABLES_GUI_RULE_ATTR_PROTO:
		if (r->proto) {
			xfree(r->proto);
			r->proto = NULL;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_SRCPORT:
		if (r->srcport) {
			//xfree(r->srcport);
			r->srcport = 0;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_DSTPORT:
		if (r->dstport) {
			//xfree(r->dstport);
			r->dstport = 0;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_IPSRC:
		if (r->ipsrc) {
			xfree(r->ipsrc);
			r->ipsrc = NULL;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_IPDST:
		if (r->ipdst) {
			xfree(r->ipdst);
			r->ipdst = NULL;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_SRCNETWORK:
		if (r->srcnetwork) {
			xfree(r->srcnetwork);
			r->srcnetwork = NULL;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_DSTNETWORK:
		if (r->dstnetwork) {
			xfree(r->dstnetwork);
			r->dstnetwork = NULL;
		}
		break;
	case NFTABLES_GUI_RULE_ATTR_INTERFACE:
		if (r->interface) {
			xfree(r->interface);
			r->action = NULL;
		}
		break;
		
		
	case NFTABLES_GUI_RULE_ATTR_ID:
		break;
	}

	r->flags &= ~(1 << attr);
}

void nftables_gui_rule_set_data(struct rule *r, uint16_t attr, const void *data,
			  uint32_t data_len)
{
	if (attr > NFTABLES_GUI_RULE_ATTR_MAX)
		return;

	switch (attr) {
	case NFTABLES_GUI_RULE_ATTR_RULE_NAME:
		if (r->rule_name)
			xfree(r->rule_name);

		r->rule_name = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_ACTION:
		if (r->action)
			xfree(r->action);

		r->action = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_PROTO:
		if (r->proto)
			xfree(r->proto);

		r->proto = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_SRCPORT:
		r->srcport = *((uint32_t *)data);
		break;
	case NFTABLES_GUI_RULE_ATTR_DSTPORT:
		r->dstport = *((uint32_t *)data);
		break;
	case NFTABLES_GUI_RULE_ATTR_IPSRC:
		if (r->ipsrc)
			xfree(r->ipsrc);

		r->ipsrc = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_IPDST:
		if (r->ipdst)
			xfree(r->ipdst);

		r->ipdst = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_SRCNETWORK:
		if (r->srcnetwork)
			xfree(r->srcnetwork);

		r->srcnetwork = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_DSTNETWORK:
		if (r->dstnetwork)
			xfree(r->dstnetwork);

		r->dstnetwork = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_INTERFACE:
		if (r->interface)
			xfree(r->interface);

		r->interface = strdup(data);
		break;
	case NFTABLES_GUI_RULE_ATTR_ID:
		r->id = *((uint32_t *)data);
		break;
	}

	r->flags |= (1 << attr);
}

void nftables_gui_rule_attr_set_u32(struct rule *r, uint16_t attr, uint32_t data)
{
	nftables_gui_rule_set_data(r, attr, &data, sizeof(uint32_t));
}

void nftables_gui_rule_attr_set_port(struct rule *r, uint16_t attr, uint32_t data)
{
  nftables_gui_rule_set_data(r, attr, &data, sizeof(uint32_t));
}

void nftables_gui_rule_attr_set_str(struct rule *r, uint16_t attr, const char *data)
{
	nftables_gui_rule_set_data(r, attr, data, 0);
}

const void *nftables_gui_rule_attr_get_data(struct rule *r, uint16_t attr)
{
	if (!(r->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case NFTABLES_GUI_RULE_ATTR_RULE_NAME:
		return r->rule_name;
	case NFTABLES_GUI_RULE_ATTR_ACTION:
		return r->action;
	case NFTABLES_GUI_RULE_ATTR_PROTO:
		return r->proto;
	case NFTABLES_GUI_RULE_ATTR_SRCPORT:
		return &r->srcport;
	case NFTABLES_GUI_RULE_ATTR_DSTPORT:
		return &r->dstport;
	case NFTABLES_GUI_RULE_ATTR_IPSRC:
		return r->ipsrc;
	case NFTABLES_GUI_RULE_ATTR_IPDST:
		return r->ipdst;
	case NFTABLES_GUI_RULE_ATTR_SRCNETWORK:
		return r->srcnetwork;
	case NFTABLES_GUI_RULE_ATTR_DSTNETWORK:
		return r->dstnetwork;
	case NFTABLES_GUI_RULE_ATTR_INTERFACE:
		return r->interface;
	case NFTABLES_GUI_RULE_ATTR_ID:
		return &r->id;
	}
	return NULL;
}

uint32_t nftables_gui_rule_attr_get_u32(struct rule *r, uint16_t attr)
{
	const void *ret = nftables_gui_rule_attr_get_data(r, attr);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *nftables_gui_rule_attr_get_str(struct rule *r, uint16_t attr)
{
	return nftables_gui_rule_attr_get_data(r, attr);
}

int nftables_gui_rule_snprintf(char *buf, size_t size, struct rule *r)
{
	return snprintf(buf, size, "Rule %s action %s ipsrc %s ipdst %s proto %s srcport %d dstport %d ipsrc %s ipdst %s srcnetwork %s dstnetwork %s interface %s",
			r->rule_name, r->action, r->ipsrc , r->ipdst, r->proto, r->srcport, r->dstport
			, r->ipsrc, r->ipdst, r->srcnetwork, r->dstnetwork, r->interface);
}
