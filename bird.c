#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#define empty     0
#define wall      1
#define pillar    2
#define bird      3

#define wall_wide     3
#define pillar_wide   5
#define pillar_length 4
#define pillar_gap    8

#define LENGTH    100
#define WIDE      20

struct Block 
{
    _Bool status;
    int content;
}block[WIDE][LENGTH];

static int count = 0;

int random_wide(void)
{
  return (rand() % (pillar_length + 1));
}

void init_block(struct Block fp[WIDE][LENGTH])
{
  int i,j;
  for(i = 0;i < WIDE;i++)
  {
    for(j = 0;j < LENGTH;j++)
    {
      fp[i][j].status = false;
      if(i < wall_wide || i >=  WIDE - wall_wide)
      {
        fp[i][j].content = wall; 
        fp[i][j].status = true;
      }
      else
      {
        fp[i][j].content = empty; 
        fp[i][j].status = false;
      }
    }
  }
}
void shift_block(struct Block fp[WIDE][LENGTH])
{
  int i,j;
  static int roll = 0;

  if(!(count % (pillar_length + pillar_gap)))
  {
    roll = random_wide();
  }
  for(i = 0;i < WIDE;i++)
  {
    for(j = 0;j < LENGTH - 1;j++)
    {
      fp[i][j].content = fp[i][j+1].content;
    }
  }
  
  for(i = 0;i < WIDE;i++)
  {
    if(((count - 1)%(pillar_length + pillar_gap) < pillar_length) 
      &&((i >= wall_wide 
          && i < wall_wide + pillar_wide + roll)
        ||(i >= WIDE - pillar_wide - wall_wide + roll
          && i < WIDE - wall_wide))
      ) 
    {
      fp[i][LENGTH-1].content = pillar;
      fp[i][LENGTH-1].status = true;
    }
    else if(i < wall_wide || i >=  WIDE - wall_wide)
    {
      fp[i][LENGTH-1].content = wall;
      fp[i][LENGTH-1].status = true;
    }
    else
    {
      fp[i][LENGTH-1].content = empty;
      fp[i][LENGTH-1].status = false;
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
  count++;
  sleep(1);
}


int main(int argc,char ** argv)
{
  srand((unsigned int) time(0));

  init_block(block);
  while(1)
  {
    print_block(block); 
    shift_block(block);
  }
  return 0;
}
