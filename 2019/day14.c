/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>
#include "day14_data.c"

typedef __int64 s64;

struct reaction {
	struct item { int id; int count; } in[10], out;
} reaction[70];

int ridx;

struct link {
	struct node *n;
	int req;
};

struct node {
	struct link parent[10];
	struct link child[10];
	
	int id;
	int prod;
	s64 total;
	double total2;
	double total3;
} node[70];

int nidx;

int id_encode(char *str)
{
	int out = 0;
	while(*str) out = (out << 5) | ((*str++ - 'A' + 1) & 0x1F);
	return out;
}

void id_decode(int id, char *str)
{
	int i;
	for(i = 0; i < 7; i++) {
		char c = (id >> ((6-i)*5)) & 0x1F;
		if(!c) continue;
		*str++ = c + 'A' - 1;
	}
	
	*str = 0;
}

int parse_pair(char *str, char *sout, int *num)
{
	char *start = str;
	int n = 0;

	while(*str != ' ') n = n * 10 + *str++ - '0'; str++;
	while(*str >= 'A') *sout++ = *str++;
	
	if(*str == ' ') str+=1;
	if(*str == ',') str+=2;
	
	*sout = 0;
	*num = n;

	return str - start;
}

void parse_input(char *str)
{
	while(*str)
	{
		int n, i = 0;
		char id[20];
		
		while(*str != '=') {
			str += parse_pair(str, id, &n);
			reaction[ridx].in[i].count = n;
			reaction[ridx].in[i++].id = id_encode(id);
		}
		
		str += 3;
		str += parse_pair(str, id, &n);
		reaction[ridx].out.count = n;
		reaction[ridx].out.id = id_encode(id);
		ridx++;

		while(*str++ != '\n');
	}
}

struct node* find_node(int id)
{
	int i;
	for(i = 0; i < nidx; i++)
		if(node[i].id == id)
			return &node[i];

	return NULL;
}

void add_child(struct node *cur, struct node *child, int req)
{
	int i;

	for(i = 0; i < 10; i++) {
		if(cur->child[i].n == NULL) {
			cur->child[i].n = child;
			cur->child[i].req = req;
			return;
		}
	}
}


void generate_nodes(void)
{
	int i, j;
	
	for(i = 0; i < ridx; i++) {
		int id = reaction[i].out.id;
		if(find_node(id)) continue;
		node[nidx].id = id;
		node[nidx].prod = reaction[i].out.count;
		
		for(j = 0; j < 10; j++) {
			node[nidx].parent[j].n = (void*)reaction[i].in[j].id;
			node[nidx].parent[j].req  = reaction[i].in[j].count;
		}
		
		nidx++;
	}
	
	for(i = 0; i < ridx; i++)
	for(j = 0; j < 10; j++) {
		int id = reaction[i].in[j].id;
		if(!id) continue;
		if(find_node(id)) continue;
		node[nidx].id = id;
		nidx++;
	}
	
	for(i = 0; i < nidx; i++) {
		int id = node[i].id;
		
		for(j = 0; j < 10; j++) {
			struct link *parent = &node[i].parent[j];
			if(!parent->n) continue;
			parent->n = find_node((int)parent->n);
			add_child(parent->n, &node[i], parent->req);
		}
	}
}

int scaleup(struct node *n)
{
	int out;
	if(!n->prod || !n->total) return 1;
	
	out = n->total / n->prod;
	if(n->total > out*n->prod) out++;
	return out;
}

double scaleup3(struct node *n)
{
	if(!n->prod || !n->total3) return 1;
	
	return n->total3 / (double)n->prod;
}

void calculate_nodes_bw(struct node *n)
{
	struct link *lnk = n->child;
	int i;
	
	n->total   = 0;
	n->total3  = 0;
	
	for(i = 0; i < 10; i++) {
		struct node *child = lnk[i].n;
		if(!child) continue;
		n->total  += lnk[i].req * scaleup(child);
		n->total3 += lnk[i].req * scaleup3(child);
	}
	
	lnk = n->parent;
	for(i = 0; i < 10; i++) {
		struct node *parent = lnk[i].n;
		if(!parent) continue;
		calculate_nodes_bw(parent);
	}
}

void calculate_nodes_fw(struct node *n)
{
	struct link *lnk = n->parent;
	int i, j, *bignum;
	char buffer[8];
	id_decode(n->id, buffer);
	bignum = (int*)&n->total2;
	
	for(i = 0; i < 10; i++) {
		struct node *parent = lnk[i].n;
		if(!parent || !parent->total2) continue;
		n->total2 = (parent->total2 * n->total3) / parent->total3;
		n->total2 = (n->total2 / n->prod) * n->prod;
		break;
	}
	
	lnk = n->child;
	for(i = 0; i < 10; i++) {
		struct node *child = lnk[i].n;
		if(!child) continue;
		calculate_nodes_fw(child);
	}
}

int main(void)
{
	struct node *fuel, *ore;
	s64 x;
	
	parse_input(input);
	generate_nodes();
	
	fuel = find_node(id_encode("FUEL"));
	calculate_nodes_bw(fuel);
	
	ore = find_node(id_encode("ORE"));
	printf("Total ORE required: %d\n", ore->total);
	
	fuel->total  = 1;
	fuel->total3 = 1;
	ore->total2 = 1000000000000;
	calculate_nodes_fw(ore);
	
	//might be off by one
	printf("Total FUEL produced: %f\n", fuel->total2);
	
	return 0;
}