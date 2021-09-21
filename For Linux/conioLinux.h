/* Released under Public Domain: Do whatever you like with this file :D */
#ifdef Linux

#include <stdlib.h>
#define clrscr() system("clear")

#include <termios.h>
#include <stdio.h>

static struct termios old, xnew;

/* Initialize xnew terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  xnew = old; /* make xnew settings same as old settings */
  xnew.c_lflag &= ~ICANON; /* disable buffered i/o */
  xnew.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &xnew); /* use these xnew terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

#else 

#include <conio.h>
 
#endif

#ifdef CodeBlocksinWindows
#ifndef Linux
#include <stdlib.h>
#define clrscr() system("cls")
#endif
#endif