#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include "info.h"

#define PI 3.14

void init(int total_choices);
void getTinfo(tinfo *Tinfo);
void draw_circle(float length, char *character, int total_choices, float angle_of_rotation); 
void draw_line(float length, float angle, char *character);
void put_choices(char **, int , int, float);
void draw_point(float length, char *character, float angle);
void read_choices(char *path, chinfo *);
void reset();
#endif
