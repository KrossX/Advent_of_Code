/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdlib.h>
#include <stdio.h>
#include "day06_data.c"

struct node {
	int id;
	int child_num;
	struct node *parent, *child;
};

int find_children(int id, int *child)
{
	int (*data)[2] = (void*)input;
	int count = 0;
	
	while(data[0][0]) {
		if(data[0][0] == id) {
			*child++ = data[0][1];
			count++;
		}
		data++;
	}
	
	return count;
}

int child_pack[512];

void fill_node(struct node *n)
{
	n->child_num = find_children(n->id, child_pack);
	
	if(!n->child_num) {
		n->child = NULL;
	} else {
		n->child = malloc(sizeof(struct node) * n->child_num);
		
		if(!n->child) {
			printf("Error! Could not alloc memory.\n");
			return;
		} else {
			int i;
			
			for(i = 0; i < n->child_num; i++) {
				n->child[i].id = child_pack[i];
				n->child[i].parent = n;
			}
			
			for(i = 0; i < n->child_num; i++) {
				fill_node(&n->child[i]);
			}
		}
	}
}

int steps_total;

void walk_node(struct node *n, int level)
{
	int i;
	
	steps_total += level++;
	
	for(i = 0; i < n->child_num; i++) {
		walk_node(&n->child[i], level);
	}
}

struct node* find_node(struct node *n, int id)
{
	int i;
	
	if(n->id == id) return n;
	
	for(i = 0; i < n->child_num; i++) {
		struct node *nn = find_node(&n->child[i], id);
		if(nn) return nn;
	}
	
	return NULL;
}

int parent_pack[512];

void orbital_tansfer_steps(struct node *n)
{
	struct node *you = find_node(n, *(int*)"YOU");
	struct node *san = find_node(n, *(int*)"SAN");
	
	struct node *test = you;
	int i = 0, j;
	int steps_you = 0, steps_san = 0, common_parent = 0;
	
	while(test->parent) {
		test = test->parent;
		parent_pack[i++] = test->id;
	}
	
	test = san;
	
	while(test && common_parent == 0) {
		for(j = 0; j < i; j++) {
			if(parent_pack[j] == test->id) {
				common_parent = test->id;
				break;
			}
		}

		test = test->parent;
		steps_san++;
	}
	
	test = you;
	
	for(j = 0; j < i; j++) {
		if(parent_pack[j] == common_parent)
			break;
	}
	
	printf("Transfer steps: %d\n", steps_san + j - 2);
}

int main(void)
{
	struct node orbit;
	
	orbit.id = *(int*)"COM";
	orbit.parent = NULL;
		
	fill_node(&orbit);
	walk_node(&orbit, 0);
	
	printf("Total steps: %d\n", steps_total);
	
	orbital_tansfer_steps(&orbit);

	return 0;
}
