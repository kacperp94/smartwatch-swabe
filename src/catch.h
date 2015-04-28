#include <time.h>
#pragma once

typedef struct{
  int is24Pass; // boolean
  int catch_hours;
  float lati;
  float longi;
} catch_t;

void catch_init(catch_t *);
void catch_speak(catch_t *, TextLayer *);
// void catch_destroy(catch_t *);