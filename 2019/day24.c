/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdlib.h>
#include <stdio.h>
#include "day24_data.c"

typedef __int16 s16;
typedef __int32 s32;

typedef unsigned __int16 u16;
typedef unsigned __int32 u32;

//16bit tiles, -32768, 32767 levels
char tile_data[0x10000][5*5+3]; // 3 padding, 28
int level_min, level_max;

struct change_step { s16 level; char pos, c; };
struct change_step change[0x10000];
int changeidx;

u32 pattern[0x1000];
u32 pidx;

u32 find_duplicate(u32 id)
{
	int i;
	for(i = 0; i < pidx; i++)
		if(pattern[i] == id)
			return id;

	return 0;
}

u32 encode_state(char *data)
{
	u32 encoded = 0;
	int i;
	for(i = 0; i < 25; i++)
		encoded |= data[i] == '#'? 1 << i : 0;
	
	return encoded;
}

char get_pixel(int x, int y, char *data)
{
	if(x<0 || x>=5) return 0;
	if(y<0 || y>=5) return 0;
	return data[y*5+x];
}

void step(void)
{
	int x, y;
	char prev[5*5];
	memcpy(prev, input, 5*5);
	
	for(y = 0; y < 5; y++)
	for(x = 0; x < 5; x++) {
		char c = get_pixel(x,y,prev);
		int count = 0;
		if(get_pixel(x+1,y,prev) == '#') count++;
		if(get_pixel(x-1,y,prev) == '#') count++;
		if(get_pixel(x,y+1,prev) == '#') count++;
		if(get_pixel(x,y-1,prev) == '#') count++;
		
		if(c == '.' && (count == 1 || count == 2))
			input[y*5+x] = '#';
		
		if(c == '#' && count != 1)
			input[y*5+x] = '.';
	}
	
}

int render(char *data)
{
	int x, y;
	
	for(y = 0; y < 5; y++) {
		for(x = 0; x < 5; x++) {
			putchar(data[y*5+x]);
		}
	
		printf("\n");
	}
}

void run1(void)
{
	u32 rating;
	
	while(1) {
		step();
		render(input);
		rating = encode_state(input);
		if(find_duplicate(rating)) break;
		pattern[pidx++] = rating;
	}
	
	printf("Biodiversity rating: %u\n", rating);
}

int get_bug(int pos, s16 level)
{
	return tile_data[(u16)level][pos-1] == '#';
}

int check_adj(int pos, s16 level)
{
	int count = 0;
	
	switch(pos) { // UP, LEFT, RIGHT, DOWN
	case  1:
		count += get_bug( 8,level-1);
		count += get_bug(12,level-1);
		count += get_bug( 2,level);
		count += get_bug( 6,level);
		break;
	case  2:
		count += get_bug(8,level-1);
		count += get_bug(1,level);
		count += get_bug(3,level);
		count += get_bug(7,level);
		break;
	case  3:
		count += get_bug(8,level-1);
		count += get_bug(2,level);
		count += get_bug(4,level);
		count += get_bug(8,level);
		break;
	case  4:
		count += get_bug(8,level-1);
		count += get_bug(3,level);
		count += get_bug(5,level);
		count += get_bug(9,level);
		break;
	case  5:
		count += get_bug( 8,level-1);
		count += get_bug( 4,level);
		count += get_bug(14,level-1);
		count += get_bug(10,level);
		break;
	case  6:
		count += get_bug( 1,level);
		count += get_bug(12,level-1);
		count += get_bug( 7,level);
		count += get_bug(11,level);
		break;
	case  7: 
		count += get_bug( 2,level);
		count += get_bug( 6,level);
		count += get_bug( 8,level);
		count += get_bug(12,level);
		break;
	case  8:
		count += get_bug(3,level);
		count += get_bug(7,level);
		count += get_bug(9,level);
		count += get_bug(1,level+1);
		count += get_bug(2,level+1);
		count += get_bug(3,level+1);
		count += get_bug(4,level+1);
		count += get_bug(5,level+1);
		break;
	case  9:
		count += get_bug( 4,level);
		count += get_bug( 8,level);
		count += get_bug(10,level);
		count += get_bug(14,level);
		break;
	case 10:
		count += get_bug( 5,level);
		count += get_bug( 9,level);
		count += get_bug(14,level-1);
		count += get_bug(15,level);
		break;
	case 11: 
		count += get_bug( 6,level);
		count += get_bug(12,level-1);
		count += get_bug(12,level);
		count += get_bug(16,level);
		break;
	case 12: 
		count += get_bug( 7,level);
		count += get_bug(11,level);
		count += get_bug( 1,level+1);
		count += get_bug( 6,level+1);
		count += get_bug(11,level+1);
		count += get_bug(16,level+1);
		count += get_bug(21,level+1);
		count += get_bug(17,level);
		break;
	case 13:
		// ??
		break;
	case 14: 
		count += get_bug( 9,level);
		count += get_bug( 5,level+1);
		count += get_bug(10,level+1);
		count += get_bug(15,level+1);
		count += get_bug(20,level+1);
		count += get_bug(25,level+1);
		count += get_bug(15,level);
		count += get_bug(19,level);
		break;
	case 15:
		count += get_bug(10,level);
		count += get_bug(14,level);
		count += get_bug(14,level-1);
		count += get_bug(20,level);
		break;
	case 16:
		count += get_bug(11,level);
		count += get_bug(12,level-1);
		count += get_bug(17,level);
		count += get_bug(21,level);
		break;
	case 17: 
		count += get_bug(12,level);
		count += get_bug(16,level);
		count += get_bug(18,level);
		count += get_bug(22,level);
		break;
	case 18:
		count += get_bug(21,level+1);
		count += get_bug(22,level+1);
		count += get_bug(23,level+1);
		count += get_bug(24,level+1);
		count += get_bug(25,level+1);
		count += get_bug(17,level);
		count += get_bug(19,level);
		count += get_bug(23,level);
		break;
	case 19:
		count += get_bug(14,level);
		count += get_bug(18,level);
		count += get_bug(20,level);
		count += get_bug(24,level);
		break;
	case 20: 
		count += get_bug(15,level);
		count += get_bug(19,level);
		count += get_bug(14,level-1);
		count += get_bug(25,level);
		break;
	case 21: 
		count += get_bug(16,level);
		count += get_bug(12,level-1);
		count += get_bug(22,level);
		count += get_bug(18,level-1);
		break;
	case 22: 
		count += get_bug(17,level);
		count += get_bug(21,level);
		count += get_bug(23,level);
		count += get_bug(18,level-1);
		break;
	case 23:
		count += get_bug(18,level);
		count += get_bug(22,level);
		count += get_bug(24,level);
		count += get_bug(18,level-1);
		break;
	case 24:
		count += get_bug(19,level);
		count += get_bug(23,level);
		count += get_bug(25,level);
		count += get_bug(18,level-1);
		break;
	case 25: 
		count += get_bug(20,level);
		count += get_bug(24,level);
		count += get_bug(14,level-1);
		count += get_bug(18,level-1);
		break;
	}
	
	return count;
}

void add_change(s16 level, char pos, char c)
{
	change[changeidx].level = level;
	change[changeidx].pos   = pos-1;
	change[changeidx].c     = c;
	changeidx++;
}

void step2(s16 level)
{
	char *data = tile_data[(u16)level];
	int x, y;
	
	for(y = 0; y < 5; y++)
	for(x = 0; x < 5; x++) {
		int count;
		int pos = y*5+x+1;
		char c = data[pos-1];
		if(c == '?') continue;
		
		count = check_adj(pos,level);

		if(c == '.' && (count == 1 || count == 2))
			add_change(level,pos,'#');
		
		if(c == '#' && count != 1)
			add_change(level,pos,'.');
	}
}

void apply_changes(void)
{
	int i;
	for(i = 0; i < changeidx; i++)
		tile_data[(u16)change[i].level][change[i].pos] = change[i].c;
	
	changeidx = 0;
}

int main(void)
{
	int i, j, step;
	u32 count = 0;
	
	memset(tile_data, '.', sizeof(tile_data));
	memcpy(tile_data, input, 5*5);
	
	for(i = 0; i < 65536; i++) {
		tile_data[i][12] = '?';
		//tile_data[i][25] = 0;
		//tile_data[i][26] = 0;
		//tile_data[i][27] = 0;
	}
	
	for(step = 0; step < 200; step++) {
		for(i = -32768; i <= 32767; i++)
			step2(i);
		
		apply_changes();
	}
	
	for(i = 0; i < 65536; i++)
	for(j = 0; j < 25; j++) {
		if(tile_data[i][j] == '#') count++;
	}
	
	printf("Bug count: %u\n", count);
}