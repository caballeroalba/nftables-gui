#include "table.h"

#define MAX_BUFFER_SIZE 4096

extern char buf_screen[MAX_BUFFER_SIZE];
/* prototipes*/
void create_table(struct table *t);
//void list_tables(struct table_list *list);

struct table_list {
	struct list_head list;
	int elements;
};
void delete_all_tables();
void list_tables(struct table_list *list);
void list_table_details(int ntable, struct table_list *list);
void list_chain_details(int ntable, int nchain, struct table_list *list);
void list_chains(int ntable, struct table_list *list);
void list_rules(struct chain *ch);
void list_rule_details(struct chain *ch, int nrule);
struct rule * get_rule(struct chain *ch, int nrule);
void create_chain(int ntable, struct table_list *list);
void delete_chain(int ntable, struct table_list *list);
void delete_table(int ntable, struct table_list *list);
void create_rule(struct table *t, struct chain *ch);
struct chain * get_chain(struct table *t, int nchain);
struct table * get_table(int ntable, struct table_list *list);
char *trim (char *s);


