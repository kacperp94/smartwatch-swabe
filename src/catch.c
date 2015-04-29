#include <pebble.h>
#include <time.h>
#include "catch.h"


//IDK, if it should be here or in main
//enum {
//KEY_SUM = 0,
//};
void catch_init(catch_t *cptr)
{
  cptr->is24Pass = 0;
  cptr->catch_hours = 0;
  cptr->lati = 0;
  cptr->longi = 0;
}
  
void catch_speak(catch_t *cptr, TextLayer * text_layer)
{
  char daybuf[10];
  char houbuf[10];
  // Get current time
  time_t current_time;
  time (&current_time);
  struct tm * timeinfo = localtime (&current_time);
    
    strftime (houbuf,80,"%H",timeinfo);
    strftime (daybuf,80,"%e",timeinfo);
    
    int temp_hours = atoi(houbuf);
    int temp_days = atoi(daybuf);
    temp_hours += temp_days * 24;
    
    int diff_hours = temp_hours - cptr->catch_hours;
    
    if(diff_hours >= 24 || cptr->catch_hours == 0)
    {
      cptr->is24Pass = 1;
      cptr->catch_hours = temp_hours;
      text_layer_set_text(text_layer, "Can catch!");
      //if(user clicks catch)
      //{take value of sum calculated in .js}
    }
    else
    {
      cptr->is24Pass = 0;
      text_layer_set_text(text_layer, "Wait to catch!");
    } 

}