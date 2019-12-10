/* Copyright (c) 2019 KrossX <krossx@live.com>
* License: http://www.opensource.org/licenses/mit-license.html  MIT License
*/

#include <math.h>
#include <stdio.h>
#include "day10_data.c"

#define PI 3.1415926535897932384626433832795

#define INPUT input
#define SIZE 36

struct asteroid {
	int x, y, destroyed;
	float angle;
} asteroid[SIZE*SIZE];

int asteroid_count;

double dabs(double x)
{
	return x < 0 ? -x : x;
}

int check_detected(int idx, int *detected)
{
	int i,j;
	int count = 0;
	int x = asteroid[idx].x;
	int y = asteroid[idx].y;
	
	for(i = 0; i < asteroid_count; i++) {
		double dx, dy, len;
		int occluded = 0;
		if(i == idx) continue;
		if(asteroid[i].destroyed) continue;
		
		dx  = asteroid[i].x - x;
		dy  = asteroid[i].y - y;
		len = sqrt(dx*dx + dy*dy);
		dx /= len;
		dy /= len;
		
		for(j = 0; j < asteroid_count; j++) {
			double dx2, dy2, len2;
			if(j == idx) continue;
			if(j == i) continue;
			if(asteroid[j].destroyed) continue;
			
			dx2  = asteroid[j].x - x;
			dy2  = asteroid[j].y - y;
			len2 = sqrt(dx2*dx2 + dy2*dy2);
			dx2 /= len2;
			dy2 /= len2;
			
			if(dabs(dx2-dx) < 0.0001 && dabs(dy2-dy) < 0.0001) {
				if(len2 < len) { occluded = 1; break; }
			}
		}
		
		if(occluded == 0) {
			if(detected) {
				detected[count] = i;
				asteroid[i].angle = asin(dabs(dx)) * 180.0 / PI;
				if(dx >= 0 && dy >= 0) asteroid[i].angle = 180.0 - asteroid[i].angle;
				else if(dx < 0 && dy >= 0) asteroid[i].angle += 180.0;
				else if(dx < 0 && dy < 0) asteroid[i].angle = 360.0 - asteroid[i].angle;
			}
			count++;
		}
	}
	
	return count;
}

void fill_asteroids(void)
{
	int x, y;
	
	for(y = 0; y < SIZE; y++)
	for(x = 0; x < SIZE; x++) {
		char c = INPUT[y * SIZE + x];

		if(c == '#') {
			asteroid[asteroid_count].x = x;
			asteroid[asteroid_count].y = y;
			asteroid[asteroid_count].destroyed = 0;
			asteroid_count++;
		}
	}
}

void run(void)
{
	int x, y, i;
	int detected = 0;
	
	fill_asteroids();
	
	for(i = 0; i < asteroid_count; i++) {
		int check = check_detected(i, NULL);
		
		if(check > detected) {
			detected = check;
			x = asteroid[i].x;
			y = asteroid[i].y;
		}
	}
	
	printf("%d x %d map, %d total asteroids.\n", SIZE, SIZE, asteroid_count);
	printf("Best is (%d,%d) with %d other asteroids detected.\n", x, y, detected);
}

int find_asteroid(int x, int y)
{
	int i;
	
	for(i = 0; i < asteroid_count; i++) {
		if(asteroid[i].x == x && asteroid[i].y == y)
			return i;
	}
	
	return -1;
}

void sort_detected(int *list, int count)
{
	count--;
	
	while(1) {
		int swaps = 0, i;
		
		for(i = 0; i < count; i++) {
			struct asteroid *a1 = &asteroid[list[i]];
			struct asteroid *a2 = &asteroid[list[i+1]];
			
			if(a1->angle > a2->angle) {
				int temp = list[i];
				list[i] = list[i+1];
				list[i+1] = temp;
				swaps++;
			}
		}
		
		if(swaps == 0) break;
	}
}

int main(void)
{
	int on_view[SIZE*SIZE];
	int idx, i;
	
	fill_asteroids();
	idx = find_asteroid(17,22);
	
	while(1) {
		int detected = check_detected(idx, on_view);
		if(!detected) break;
		
		sort_detected(on_view, detected);
		
		for(i = 0; i < detected; i++) {
			
			struct asteroid *a = &asteroid[on_view[i]];

			if(i == 199)
			printf("%d -> (%d, %d) %f\n", i+1, a->x, a->y, a->angle);
					
			
			asteroid[on_view[i]].destroyed = 1;
		}
		
		printf("%d asteroids destroyed.\n", detected);
	}
	
}