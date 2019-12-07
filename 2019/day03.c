/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

#include <stdio.h>
#include "day03_data.c"

//8510
//14218

#define BOARD_SIZE (1024 * 32)
#define BOARD_OFF (BOARD_SIZE/2)

char board[BOARD_SIZE * BOARD_SIZE];

int crossing[2][128];
int crossing_idx;

void trace(int *path, int id)
{
	int x = BOARD_OFF;
	int y = BOARD_OFF;
	int xmin = 99999999, xmax = -99999999;
	int ymin = 99999999, ymax = -99999999;
	
	while(*path) {
		int dir = *path++;
		int num = *path++;
		
		while(num--) {
			int blip = board[BOARD_SIZE * y + x];
				
			if(blip > 0 && blip != id) {
				crossing[crossing_idx][0] = x;
				crossing[crossing_idx][1] = y;
				crossing_idx++;
			}
			
			board[BOARD_SIZE * y + x] = id;
			
			switch(dir) {
			case 1: x--; break;
			case 2: x++; break;
			case 3: y--; break;
			case 4: y++; break;
			}
			
			if(x < xmin) xmin = x;
			if(x > xmax) xmax = x;
			if(y < ymin) ymin = y;
			if(y > ymax) ymax = y;
			
			if(x < 0 || y < 0 || x > BOARD_SIZE || y > BOARD_SIZE)
				printf("Error! Bad coords: %d, %d\n", x, y);
		}
	}
	
	printf("MinMax x: %d, %d   y: %d, %d\n", xmin, xmax, ymin, ymax);
	
}

int trace_steps(int *path, int idx)
{
	int x = BOARD_OFF;
	int y = BOARD_OFF;

	int cx = crossing[idx][0];
	int cy = crossing[idx][1];
	
	int steps = 0;
	
	while(*path) {
		int dir = *path++;
		int num = *path++;
		
		while(num--) {
			if(x == cx && y == cy)
				return steps;

			steps++;

			switch(dir) {
			case 1: x--; break;
			case 2: x++; break;
			case 3: y--; break;
			case 4: y++; break;
			}
		}
	}
}

int get_distance(int *point)
{
	int x = point[0] - BOARD_OFF;
	int y = point[1] - BOARD_OFF;
	
	return abs(x) + abs(y);
}

void show_crossings(void)
{
	int x;
	
	printf("Crossings %d\n", crossing_idx);
	
	for(x = 0; x < crossing_idx; x++) {
		printf(" %4d, %4d -> dist: %d\n", crossing[x][0], crossing[x][1], get_distance(crossing[x]));
	}
}

int main(void)
{
	int x, min = 999999, min_steps = 999999;
	
	trace(input_a, 1);
	trace(input_b, 2);
	
	for(x = 0; x < crossing_idx; x++) {
		int dist = get_distance(crossing[x]);
		
		int steps  = trace_steps(input_a, x);
		    steps += trace_steps(input_b, x);

		if(dist > 0 && dist < min) min = dist;
		if(steps > 0 && steps < min_steps) min_steps = steps;
	}
	
	printf("Min distance: %d\n", min);
	printf("Min steps: %d\n", min_steps);

	return 0;
}