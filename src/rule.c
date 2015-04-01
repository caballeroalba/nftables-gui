#include "rule.h"
#include <string.h>




struct rule *nftables_gui_rule_alloc(void)
{
	return (struct rule *)calloc(1,sizeof(struct rule));
}

void nftables_gui_rule_free(struct rule *r)
{
	if (r->flags & (1 << NFTGUI_RULE_NAME))
		xfree(r->rule_name);

	if (r->flags & (1 << NFTGUI_RULE_ACTION))
		xfree(r->action);
		
	if (r->flags & (1 << NFTGUI_RULE_PROTO))
		xfree(r->proto);	
	
	if (r->flags & (1 << NFTGUI_RULE_SRCPORT))
		//xfree(r->srcport);
	if (r->flags & (1 << NFTGUI_RULE_DSTPORT))
	//	xfree(r->dstport);
		
	if (r->flags & (1 << NFTGUI_RULE_IPSRC))
		xfree(r->ipsrc);
		
	if (r->flags & (1 << NFTGUI_RULE_IPDST))
		xfree(r->ipdst);
		
	if (r->flags & (1 << NFTGUI_RULE_SRCNETWORK))
		xfree(r->srcnetwork);
		
	if (r->flags & (1 << NFTGUI_RULE_DSTNETWORK))
		xfree(r->dstnetwork);
		
	if (r->flags & (1 << NFTGUI_RULE_INTERFACE))
		xfree(r->interface);
		

	xfree(r);
}

bool nftgui_rule_is_set(const struct rule *r, uint16_t attr)
{
	return r->flags & (1 << attr);
}

void nftgui_rule_unset(struct rule *r, uint16_t attr)
{
	if (!(r->flags & (1 << attr)))
		return;

	switch (attr) {
	case NFTGUI_RULE_NAME:
		if (r->rule_name) {
			xfree(r->rule_name);
			r->rule_name = NULL;
		}
		break;
	case NFTGUI_RULE_ACTION:
		if (r->action) {
			xfree(r->action);
			r->action = NULL;
		}
		break;
        case NFTGUI_RULE_PROTO:
		if (r->proto) {
			xfree(r->proto);
			r->proto = NULL;
		}
		break;
	case NFTGUI_RULE_SRCPORT:
		if (r->srcport) {
			//xfree(r->srcport);
			r->srcport = 0;
		}
		break;
	case NFTGUI_RULE_DSTPORT:
		if (r->dstport) {
			//xfree(r->dstport);
			r->dstport = 0;
		}
		break;
	case NFTGUI_RULE_IPSRC:
		if (r->ipsrc) {
			xfree(r->ipsrc);
			r->ipsrc = NULL;
		}
		break;
	case NFTGUI_RULE_IPDST:
		if (r->ipdst) {
			xfree(r->ipdst);
			r->ipdst = NULL;
		}
		break;
	case NFTGUI_RULE_SRCNETWORK:
		if (r->srcnetwork) {
			xfree(r->srcnetwork);
			r->srcnetwork = NULL;
		}
		break;
	case NFTGUI_RULE_DSTNETWORK:
		if (r->dstnetwork) {
			xfree(r->dstnetwork);
			r->dstnetwork = NULL;
		}
		break;
	case NFTGUI_RULE_INTERFACE:
		if (r->interface) {
			xfree(r->interface);
			r->action = NULL;
		}
		break;
		
		
	case NFTGUI_RULE_ID:
		break;
	}

	r->flags &= ~(1 << attr);
}

void nftables_gui_rule_set_data(struct rule *r, uint16_t attr, const void *data,
			  uint32_t data_len)
{
	if (attr > NFTGUI_RULE_MAX)
		return;

	switch (attr) {
	case NFTGUI_RULE_NAME:
		if (r->rule_name)
			xfree(r->rule_name);

		r->rule_name = strdup(data);
		break;
	case NFTGUI_RULE_ACTION:
		if (r->action)
			xfree(r->action);

		r->action = strdup(data);
		break;
	case NFTGUI_RULE_PROTO:
		if (r->proto)
			xfree(r->proto);

		r->proto = strdup(data);
		break;
	case NFTGUI_RULE_SRCPORT:
		r->srcport = *((uint32_t *)data);
		break;
	case NFTGUI_RULE_DSTPORT:
		r->dstport = *((uint32_t *)data);
		break;
	case NFTGUI_RULE_IPSRC:
		if (r->ipsrc)
			xfree(r->ipsrc);

		r->ipsrc = strdup(data);
		break;
	case NFTGUI_RULE_IPDST:
		if (r->ipdst)
			xfree(r->ipdst);

		r->ipdst = strdup(data);
		break;
	case NFTGUI_RULE_SRCNETWORK:
		if (r->srcnetwork)
			xfree(r->srcnetwork);

		r->srcnetwork = strdup(data);
		break;
	case NFTGUI_RULE_DSTNETWORK:
		if (r->dstnetwork)
			xfree(r->dstnetwork);

		r->dstnetwork = strdup(data);
		break;
	case NFTGUI_RULE_INTERFACE:
		if (r->interface)
			xfree(r->interface);

		r->interface = strdup(data);
		break;
	case NFTGUI_RULE_ID:
		r->id = *((uint32_t *)data);
		break;
	}

	r->flags |= (1 << attr);
}

void nftgui_rule_set_u32(struct rule *r, uint16_t attr, uint32_t data)
{
	nftables_gui_rule_set_data(r, attr, &data, sizeof(uint32_t));
}

void nftgui_rule_set_port(struct rule *r, uint16_t attr, uint32_t data)
{
  nftables_gui_rule_set_data(r, attr, &data, sizeof(uint32_t));
}

void nftgui_rule_set_str(struct rule *r, uint16_t attr, const char *data)
{
	nftables_gui_rule_set_data(r, attr, data, 0);
}

const void *nftgui_rule_get_data(struct rule *r, uint16_t attr)
{
	if (!(r->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case NFTGUI_RULE_NAME:
		return r->rule_name;
	case NFTGUI_RULE_ACTION:
		return r->action;
	case NFTGUI_RULE_PROTO:
		return r->proto;
	case NFTGUI_RULE_SRCPORT:
		return &r->srcport;
	case NFTGUI_RULE_DSTPORT:
		return &r->dstport;
	case NFTGUI_RULE_IPSRC:
		return r->ipsrc;
	case NFTGUI_RULE_IPDST:
		return r->ipdst;
	case NFTGUI_RULE_SRCNETWORK:
		return r->srcnetwork;
	case NFTGUI_RULE_DSTNETWORK:
		return r->dstnetwork;
	case NFTGUI_RULE_INTERFACE:
		return r->interface;
	case NFTGUI_RULE_ID:
		return &r->id;
	}
	return NULL;
}

uint32_t nftgui_rule_get_u32(struct rule *r, uint16_t attr)
{
	const void *ret = nftgui_rule_get_data(r, attr);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *nftgui_rule_get_str(struct rule *r, uint16_t attr)
{
	return nftgui_rule_get_data(r, attr);
}

int nftables_gui_rule_snprintf(char *buf, size_t size, struct rule *r)
{
	return snprintf(buf, size, "Rule %s action %s ipsrc %s ipdst %s proto %s srcport %d dstport %d ipsrc %s ipdst %s srcnetwork %s dstnetwork %s interface %s",
			r->rule_name, r->action, r->ipsrc , r->ipdst, r->proto, r->srcport, r->dstport
			, r->ipsrc, r->ipdst, r->srcnetwork, r->dstnetwork, r->interface);
}
