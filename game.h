#include<stdbool.h>

enum Content
{
	empty,
	wall,
	snake,
	bird,
	ball,
	pillar
};

struct Block
{
	_Bool status;
	enum Content content;
};

struct Location
{
    int x;
    int y;
};

typedef struct Block Block_type;
typedef struct Location Location_type;

extern int sh_getch(void);
extern int kbhit(void);
