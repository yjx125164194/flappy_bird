#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#define empty     0
#define wall      1
#define pillar    2
#define bird      3

#define wall_wide   3
#define pillar_wide 5

#define LENGTH    100
#define WIDE      20

struct Block 
{
    _Bool status;
    int content;
}block[WIDE][LENGTH];

void init_block(struct Block fp[WIDE][LENGTH])
{
  int i,j;
  for(i = 0;i < WIDE;i++)
  {
    for(j = 0;j < LENGTH;j++)
    {
      fp[i][j].status = 0;
      if(i < wall_wide || i >=  WIDE - wall_wide)
      {
        fp[i][j].content = wall; 
      }
      else
      {
        fp[i][j].content = empty; 
      }
    }
  }
}

void print_block(struct Block fp[WIDE][LENGTH])
{
  system("clear");
  
  int i,j;

  for(i = 0;i < WIDE;i++)
  {
    for(j = 0;j < LENGTH;j++)
    {
      switch(fp[i][j].content)
      {
        case empty:
          printf(" ");
          break;
        case wall:
          printf("*");
          break;
        case pillar:
          printf("X");
          break;
        case bird:
          printf("O");
          break;
        defalut:break;
      }
    }
    printf("\n");
  }
  sleep(1);
}


int main(int argc,char ** argv)
{
  init_block(block);
  while(1)
  {
    print_block(block); 
  }
  return 0;
}
