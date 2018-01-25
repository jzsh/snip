#include <uci.h>
#include <ucimap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

/* traverse all options */
int show_options(struct uci_section *s)
{
	struct uci_element *oe = NULL;
	struct uci_option *o = NULL;

	uci_foreach_element(&s->options, oe) {
		o = uci_to_option(oe);
		if(o->type == UCI_TYPE_STRING)
			printf("\toption\t%s\t%s\n", oe->name, o->v.string);
		else {
			struct uci_element *le = NULL;
			char *value = NULL;
			uci_foreach_element(&o->v.list, le) {
				value = list_to_element(le)->name;
				printf("\tlist\t%s\t%s\n", oe->name, value);
			}
		}
	}
	return 0;
}

void show_package(struct uci_package *pkg)
{
	int Npkg = 0;
	struct uci_package *p = NULL;
	struct uci_element *e = NULL;

	uci_foreach_element(&pkg->e.list, e) {
		Npkg++;
		printf("package name : %s\n", e->name);
		printf("type: %d\n", e->type);
		p = uci_to_package(e);
		printf("%s\n", p->path);
		printf("%s\n", p->e.name);
	}
	/* package stored in first node */	
	printf("number of packages node = %d\n", Npkg);
	printf("package name : %s\n", e->name);
	printf("type: %d\n", e->type);
	p = uci_to_package(e);
	printf("package path : %s\n", p->path);

	/* traverse all sections */
	uci_foreach_element(&pkg->sections, e) {
		struct uci_section *s = uci_to_section(e);

		printf("section name : %s", e->name);
		if(!strncmp(e->name, "cfg", 3) && s->anonymous == true) printf("\tanonymous");
		fputs("\n", stdout);
		printf("section type : %s\n", s->type);
		printf("section belongs to package : %s\n", s->package->e.name);
		show_options(s);
	}
}

/** 
 * define ucimap data struct, function 
 */

struct list_head dhcps;

/* type is dhcp */
struct uci_dhcp {
	struct ucimap_section_data map;
	struct list_head list;

	const char *interface;
	bool enable;
	const char *leasetime;
	unsigned char *start_ip;
	unsigned char *end_ip;
	int test;
	struct ucimap_list *dhcp_option;
};

static int
dhcp_parse_ip(void *section, struct uci_optmap *om, union ucimap_data *data, const char *str)
{
	unsigned char *target;
	int tmp[4];
	int i;

	if (sscanf(str, "%d.%d.%d.%d", &tmp[0], &tmp[1], &tmp[2], &tmp[3]) != 4)
		return -1;

	target = malloc(4);
	if (!target)
		return -1;

	data->ptr = target;
	for (i = 0; i < 4; i++)
		target[i] = (char) tmp[i];

	return 0;
}
static int
dhcp_format_ip(void *section, struct uci_optmap *om, union ucimap_data *data, char **str)
{
	static char buf[16];
	unsigned char *ip = (unsigned char *) data->ptr;

	if (ip) {
		sprintf(buf, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
		*str = buf;
	} else {
		*str = NULL;
	}

	return 0;
}

static void
dhcp_free_ip(void *section, struct uci_optmap *om, void *ptr)
{
	free(ptr);
}

static int
dhcp_init(struct uci_map *map, void *section, struct uci_section *s)
{
	struct uci_dhcp *dhcp = section;

	INIT_LIST_HEAD(&dhcp->list);
	dhcp->test = -1;
	return 0;
}
static int
dhcp_add(struct uci_map *map, void *section)
{
	struct uci_dhcp *dhcp= section;

	list_add_tail(&dhcp->list, &dhcps);

	return 0;
}

static struct ucimap_section_data *
dhcp_allocate(struct uci_map *map, struct uci_sectionmap *sm, struct uci_section *s)
{
	struct uci_dhcp *p = malloc(sizeof(struct uci_dhcp));
	if (!p)
		return NULL;
	memset(p, 0, sizeof(struct uci_dhcp));
	return &p->map;
}

struct my_optmap {
	struct uci_optmap map;
	int test;
};

static struct uci_sectionmap dhcp_dhcp;

static struct my_optmap dhcp_options[] = {
	{
		.map = {
			UCIMAP_OPTION(struct uci_dhcp, interface),
			.type = UCIMAP_STRING,
			.data.s.maxlen = 32,
		}
	},
	{
		.map = {
			UCIMAP_OPTION(struct uci_dhcp, enable),
			.type = UCIMAP_BOOL,
		}
	},
	{
		.map = {
			UCIMAP_OPTION(struct uci_dhcp, leasetime),
			.type = UCIMAP_STRING,
		}
	},
	{
		.map = {
			UCIMAP_OPTION(struct uci_dhcp, start_ip),
			.type = UCIMAP_CUSTOM,
			.parse = dhcp_parse_ip,
			.format = dhcp_format_ip,
			.free = dhcp_free_ip,
		}
	},
	{
		.map = {
			UCIMAP_OPTION(struct uci_dhcp, end_ip),
			.type = UCIMAP_CUSTOM,
			.parse = dhcp_parse_ip,
			.format = dhcp_format_ip,
			.free = dhcp_free_ip,
		}
	},
	{
		.map = {
			UCIMAP_OPTION(struct uci_dhcp, test),
			.type = UCIMAP_INT,
		}
	},
	{
		.map = {
			UCIMAP_OPTION(struct uci_dhcp, dhcp_option),
			.type = UCIMAP_LIST | UCIMAP_STRING,
			.data.s.maxlen = 32,
		}
	}
};

static struct uci_sectionmap dhcp_dhcp = {
	UCIMAP_SECTION(struct uci_dhcp, map),
	.type = "dhcp",
	.alloc = dhcp_allocate,
	.init = dhcp_init,
	.add = dhcp_add,
	.options = &dhcp_options[0].map,
	.n_options = ARRAY_SIZE(dhcp_options),
	.options_size = sizeof(struct my_optmap)
};

static struct uci_sectionmap *dhcp_smap[] = {
	&dhcp_dhcp,
// 	&dhcp_alias,
};

static struct uci_map dhcp_map = {
	.sections = dhcp_smap,
	.n_sections = ARRAY_SIZE(dhcp_smap),
};

int main(int argc, char **argv)
{
	struct uci_context *ctx;
	struct uci_package *pkg;

	ctx = uci_alloc_context();
	uci_set_confdir(ctx, "config");

	char *config = "dhcp";
	if(argc > 1) config = argv[1];

	if(uci_load(ctx, config, &pkg) != UCI_OK) {
		printf("Error: Can't load package\n");
		goto cleanup;
	}

	show_package(pkg);


	/* demostrate for ucimap lib
	*****************************/

	struct uci_dhcp *dhcp;
	struct list_head *p;
	int i, n;
	INIT_LIST_HEAD(&dhcps);

	ucimap_init(&dhcp_map);
	ucimap_parse(&dhcp_map, pkg);

	list_for_each(p, &dhcps) {
		const unsigned char *startip, *endip;
		dhcp = list_entry(p, struct uci_dhcp, list);
		startip = dhcp->start_ip;
		endip = dhcp->end_ip;
		if (!startip) endip = (const unsigned char *) "\x00\x00\x00\x00";
		if (!endip) endip = (const unsigned char *) "\x00\x00\x00\x00";
		printf("New dhcp section \n"
			"	ifname: %s\n"
			"	start_ip: %d.%d.%d.%d\n"
			"	end_ip: %d.%d.%d.%d\n"
			"	test: %d\n"
			"	enabled: %s\n",
			dhcp->interface,
			startip[0], startip[1], startip[2], startip[3],
			endip[0], endip[1], endip[2], endip[3],
			dhcp->test,
			(dhcp->enable ? "on" : "off"));
		n = dhcp->dhcp_option->n_items;
		for(i = 0; i < n; i++) {
			printf("dhcp_option: %s\n", dhcp->dhcp_option->item[i].s);
		}
	}
	
	ucimap_cleanup(&dhcp_map);

	uci_unload(ctx, pkg); // release pkg
cleanup:
	uci_free_context(ctx);
	return 0;
}

