#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../libs/utils.h"
#define INC_R 0.01
int main(int argc, char **argv){
  
  chinfo choices_info = {0};
  if(argc < 2){
    fprintf(stderr, "A file containing choices needs to be provided: spin <path_to_file>\n");
    exit(-1);
  }
  read_choices(argv[1], &choices_info);
  tinfo Tinfo = {0};
  getTinfo(&Tinfo);
  init(3);
  float starting_pos = rand()%200;
  float angle_starting_position = rand()%200;
  draw_circle(-1, "█", choices_info.total, angle_starting_position);
  put_choices(choices_info.words, choices_info.total, Tinfo.rows/3 - 5, angle_starting_position);
  float j = 0;
  for(float i = 0; 1 ; i+=INC_R){
    draw_point(Tinfo.rows/2 - 5, "\x1b[38;2;223;98;38m██\x1b[0m", i+starting_pos);
    if((int)exp(j) >= 1000*Tinfo.rows && (int)time(0)%5 == 0) break;
    usleep(exp(j+=INC_R));
    draw_point(Tinfo.rows/2 - 5, "\x1b[48;2;255;255;255m  \x1b[0m", (i+starting_pos)-INC_R);
  }
  for(int i = 0; i < choices_info.total; i++){
    free(choices_info.words[i]);
  }
  free(choices_info.words);
  printf("\x1b[%d;0f",Tinfo.rows);
  return 0;
}
