#include "../libs/utils.h"


tinfo Tinfo = {0};
unsigned short *colors;



void init_color(int total_choices){
  colors = (unsigned short*)calloc(total_choices*3, sizeof(unsigned short));
  for(int i = 0; i < total_choices*3; i++){
    colors[i] = rand()%255;
  }
}
void draw_circle(float length, char *character, int total_choices, float aor){ //aor: angle of rotation
  getTinfo(&Tinfo);
  float div = 2*PI/(total_choices);
  int hpos_x = Tinfo.cols/2 ;
  int hpos_y = Tinfo.rows/2 ;
  int h = 0;
  if(length < 0) h = hpos_y - 5;
  else h = (int)length%hpos_y;
  int k = 0;
  int color[3] = {0};
  for(float i = aor; i < 2*PI+aor; i+=0.05/h){
    int temp_h = 0;
    if(i-aor >= div*k) {
      color[0] = colors[k];
      color[1] = colors[k+1];
      color[2] =  colors[k+2];
      k++;
    }
    while(temp_h <= h-1){
      int x = temp_h*cos(i)*1.7 + hpos_x +1;
      int y = temp_h*sin(i) + hpos_y + 1;
      for(int l = -1; l <= 1; l++){
        printf("\x1b[%d;%df\x1b[38;2;%d;%d;%dm%s\x1b[0m", (y+l), (x+l), color[0], color[1], color[2],character);
      }
      temp_h++;
    }

  }
}

void reset(){
  puts("\x1b[?25h");
  setvbuf(stdout, NULL, _IOFBF, 0);
}
void init(int total_choices){
  atexit(reset);
  srand(time(0));
  system("clear");
  puts("\x1b[?25l");
  setvbuf(stdout, NULL, _IONBF, 0);
  init_color(total_choices);
}


void getTinfo(tinfo *Tinfo){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  Tinfo->cols = w.ws_col;
  Tinfo->rows = w.ws_row;
}

void draw_line(float len, float angle, char *character){
  int hpos_x = Tinfo.cols/2;
  int hpos_y = Tinfo.rows/2 + 1;
  float h = 2*PI*len;
  int x = 0, y = 0;
  float temp_h = 0;
  while(temp_h <= h){
    x = temp_h*cos(angle)*1.7 + hpos_x;
    y = temp_h*sin(angle) + hpos_y;
    printf("\x1b[%d;%df%s", y, x, character);
    temp_h+=0.5;
  }

}

void put_choices(char **choices, int total, int length, float angle){
  float div = 2*PI/total;
  int hpos_x = Tinfo.cols/2;
  int hpos_y = Tinfo.rows/2;
  int x = 0;
  int y = 0;
  int k = 0;
  int word_len =  length*div;
  for(float i = angle; i < PI*2+angle; i+=0.01){
    x = length*cos(i)*1.7 + hpos_x ;
    y = length*sin(i) + hpos_y;
    if(i-angle >= div*(k+0.5) && k != total){
      printf("\x1b[%d;%df\x1b[48;2;%d;%d;%dm%.*s\x1b[0m", y, x, colors[k], colors[k+1], colors[k+2], word_len,choices[k]);
      k++;
    }
  }
  free(colors);
}

void draw_point(float length, char *character, float angle){
  int hpos_x = Tinfo.cols/2;
  int hpos_y = Tinfo.rows/2 + 1;
  float h = length;
  int x = 0, y = 0;
  x = h*cos(angle)*1.7 + hpos_x;
  y = h*sin(angle) + hpos_y;
  printf("\x1b[%d;%df%s", y, x, character);


}

void read_choices(char *path, chinfo *choices){
  FILE *file = fopen(path, "r");
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  int total_words = 0;
  rewind(file);
  char *file_content = (char*)calloc(size+1, sizeof(char));
  fread(file_content, size+1, sizeof(char), file);
  for(int i = 0; file_content[i] != '\0'; i++){
    if(file_content[i] == '\n') total_words++;
  }
  char *temp = strtok(file_content, "\n");
  choices->words = (char**)calloc(total_words, sizeof(char*));
  for(int i = 0; i < total_words; i++){
    choices->words[i] = (char*)calloc(strlen(temp)+1, sizeof(char));
    strncpy(choices->words[i],  temp, strlen(temp));
    temp = strtok(NULL, "\n");
  }
  choices->total = total_words;
  free(file_content);
  fclose(file);
}

