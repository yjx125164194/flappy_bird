#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"game.h"

#define wall_wide     3
#define pillar_wide   5
#define pillar_length 4
#define pillar_gap    8

#define LENGTH    30
#define WIDE      20
#define SPEED	  500*1000

#define bird_init_x  10
#define bird_init_y  10

#define bird_up     0
#define bird_down   1
#define bird_right  2
#define bird_left   3


static int count = 0;

Block_type block[WIDE][LENGTH];
Location_type bird_location[2][2];

int random_wide(void)
{
  return (rand() % (pillar_length * 2 - 1) - (pillar_length - 1));
}

void init_block(Block_type fp[WIDE][LENGTH])
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
  
  fp[bird_init_x][bird_init_y].content = bird;
  fp[bird_init_x+1][bird_init_y].content = bird;
  fp[bird_init_x][bird_init_y+1].content = bird;
  fp[bird_init_x+1][bird_init_y+1].content = bird;

}
void init_bird_location(Location_type bird_fp[2][2])
{
  bird_fp[0][0].x = bird_init_x;
  bird_fp[0][0].y = bird_init_y;
  bird_fp[0][1].x = bird_init_x;
  bird_fp[0][1].y = bird_init_y+1;
  bird_fp[1][0].x = bird_init_x+1;
  bird_fp[1][0].y = bird_init_y;
  bird_fp[1][1].x = bird_init_x+1;
  bird_fp[1][1].y = bird_init_y+1;
}
void shift_bird_location(Location_type bird_fp[2][2],int direction)
{
  switch(direction)
  {
    case bird_down:
      bird_fp[0][0].y++;
      bird_fp[0][1].y++;
      bird_fp[1][0].y++;
      bird_fp[1][1].y++;
      break;
    case bird_up:
      bird_fp[0][0].y--;
      bird_fp[0][1].y--;
      bird_fp[1][0].y--;
      bird_fp[1][1].y--;
      break;
    case bird_right:
      bird_fp[0][0].x++;
      bird_fp[0][1].x++;
      bird_fp[1][0].x++;
      bird_fp[1][1].x++;
      break;
    case bird_left:
      bird_fp[0][0].x--;
      bird_fp[0][1].x--;
      bird_fp[1][0].x--;
      bird_fp[1][1].x--;
    default:break;
  }
}
int print_bird_location(Block_type fp[WIDE][LENGTH],
                        Location_type bird_fp[2][2])
{
  int i,j;

  for(i = 0;i < 2;i++)
  {
    for(j = 0;j < 2;j++)
    {
      if(bird_fp[i][j].x < 0 || bird_fp[i][j].x >= LENGTH)
      {
        return 1;
      }
      else if(fp[bird_fp[i][j].y][bird_fp[i][j].x].status)
      {
        return 1;
      }
      else
      {      
        fp[bird_fp[i][j].y][bird_fp[i][j].x].content = bird;
      }
    }
  }
  return 0;
}
int shift_block(Block_type fp[WIDE][LENGTH],int direction)
{
  int i,j;
  static int roll = 0;

  if(!((count - 1) % (pillar_length + pillar_gap)))
  {
    roll = random_wide();
  }
  for(i = 0;i < WIDE;i++)
  {
    for(j = 0;j < LENGTH - 1;j++)
    {
      fp[i][j].content = fp[i][j+1].content;
      fp[i][j].status = fp[i][j+1].status;
      if(fp[i][j].content == bird)
      {
        fp[i][j].content = empty;
      }
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
  shift_bird_location(bird_location,direction);
  return print_bird_location(block,bird_location);
}

void print_block(Block_type fp[WIDE][LENGTH])
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
  usleep(SPEED);
  count++;
}


int main(int argc,char ** argv)
{
  int direction;
  
  srand((unsigned int) time(0));

  init_block(block);
  init_bird_location(bird_location);
  
  print_block(block);

  while(1)
  {
    if(!kbhit())
    {
      direction = bird_down;
    }
    else
    {
      switch(sh_getch())
      {
        case '8':
          direction = bird_up;
          break;
        case '4':
          direction = bird_left;
          break;
        case '6':
          direction = bird_right;
          break;
        case '5':
          direction = bird_down;
          break;
        case 'q':
          exit(0);
       default:
          direction = bird_down;
          break;
      }
    }
    setbuf(stdin,NULL);
    /*while(getchar() != '\n')
    {
      continue;
    }*/
    if(shift_block(block,direction))
    {
      break;
    }
    print_block(block);
  }
  printf("\n************************************\n");
  printf("you dead!you have moved %d distance!\n",count);
  printf("************************************\n");
  return 0;
}
