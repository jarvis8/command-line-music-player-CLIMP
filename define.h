#ifndef DEFINE_LIBRARY 
#define DEFINE_LIBRARY 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <dirent.h>
#include <iterator>
#include <map>

#include <stdlib.h>
#include <conio.h>
#include <time.h>// to check clockticks. (Here) Used to delay program the wait for user input and for srand(), Functions -> clock() and time()
#include <string.h>
#include <windows.h>
using namespace std;

#define UP 72 // Up arrow key. When arrow keys are pressed 2 values are returned and 2nd value is used to identify which key is pressed.
#define DOWN 80 // Down arrow key
#define LEFT 75// Left arrow key
#define RIGHT 77// Right arrow key
#define ESC 27
#define SPACE 32// Space key
#define leftBorder 10
#define rightBorder 100
#define topBorder 10
#define bottomBorder 50

#define xZero 0
#define yZero 1
//#define xMargin cout<<"                    "; //20
#define xMargin cout<<"                                                  "; //50

#define gotoxy(x,y) printf("\033[%d;%dH",(y),(x)); // terminal ANSI escape sequence to take cursor to x(%dH),y(%d) coordinate
#define gotoy(y) printf("\033[%d;%dH",(y),(xZero));
#define cLine cout<<"\x1b[2K";
#define clearLine(x,y) gotoxy(x,y) cLine ;
#define clearLineY(y) gotoxy(xZero,y) cLine ;
#define clear system("cls");// clearing terminal screen

#define pixelWidth 54
#define pixelHeight 18

#define blackTextForegroundColor cout<<"\x1b[30m";
#define redTextForegroundColor cout<<"\x1b[31m";
#define greenTextForegroundColor cout<<"\x1b[32m";
#define yellowTextForegroundColor cout<<"\x1b[33m";
#define blueTextForegroundColor cout<<"\x1b[34m";
#define magentaTextForegroundColor cout<<"\x1b[35m";
#define cyanTextForegroundColor cout<<"\x1b[36m";
#define whiteTextForegroundColor cout<<"\x1b[37m";
#define defaultTextForegroundColor cout<<"\x1b[39m";

#define blackTextBackgroundColor cout<<"\x1b[40m";
#define redTextBackgroundColor cout<<"\x1b[41m";
#define greenTextBackgroundColor cout<<"\x1b[42m";
#define yellowTextBackgroundColor cout<<"\x1b[43m";
#define blueTextBackgroundColor cout<<"\x1b[44m";
#define magentaTextBackgroundColor cout<<"\x1b[45m";
#define cyanTextBackgroundColor cout<<"\x1b[46m";
#define whiteTextBackgroundColor cout<<"\x1b[47m";
#define defaultTextBackgroundColor cout<<"\x1b[49m";

#define yellowColor blackTextForegroundColor yellowTextBackgroundColor 
#define defaultColor defaultTextBackgroundColor defaultTextForegroundColor

#define showCursor fputs("\e[?25h",stdout);
#define hideCursor fputs("\e[?25l",stdout);

#define horizontalFill xMargin cout<<"****************************************************\n";
#define horizontalBlank xMargin  cout<<"*                                                  *\n";
#define instruction1  xMargin  cout<<"*   - Use Arrow Keys To Move                       *\n";
#define instruction2  xMargin  cout<<"*   - Space to Select                              *\n";
#define instructions instruction1 instruction2;
#define instructionBox horizontalFill instructions horizontalFill;

#define PlayingBackSelected clearLineY(yZero+1) xMargin cout<<"*  ";yellowColor cout<<"<";defaultColor cout<<"                  "; greenTextForegroundColor cout<<"C L I M P";defaultTextForegroundColor cout<<"                 ";redTextBackgroundColor cout<<"X";defaultTextBackgroundColor cout<<"  *\n";
#define PlayingExitSelected clearLineY(yZero+1) xMargin  cout<<"*  <                  "; greenTextForegroundColor cout<<"C L I M P";defaultTextForegroundColor cout<<"                 ";yellowColor cout<<"X";defaultColor cout<<"  *\n";
#define PlayingBackAndExitUnselected clearLineY(yZero+1) xMargin cout<<"*  <                  "; greenTextForegroundColor cout<<"C L I M P";defaultTextForegroundColor cout<<"                 ";redTextBackgroundColor cout<<"X";defaultTextBackgroundColor cout<<"  *\n";
#define nowPlaying clearLineY(yZero+3) xMargin cout<<"*                    Now Playing:                  *\n";

#define pauseUnselected  clearLineY(yZero+9) xMargin cout<<"*                        ";cyanTextForegroundColor cout<<"||";defaultTextForegroundColor cout<<"                        *\n";
#define pauseSelected clearLineY(yZero+9)   xMargin  cout<<"*                        ";yellowColor cout<<"||";defaultColor cout<<"                        *\n";
#define playSelected   clearLineY(yZero+9)  xMargin  cout<<"*                        ";yellowColor cout<<" >";defaultColor cout<<"                        *\n";
#define playUnselected clearLineY(yZero+9) xMargin   cout<<"*                        ";cyanTextForegroundColor cout<<" >";defaultTextForegroundColor cout<<"                        *\n";

#define shuffleSelected clearLineY(yZero+6) xMargin  cout<<"*                      ",yellowColor cout<<"Shuffle";defaultColor cout<<"                     *\n";
#define shuffleUnselected clearLineY(yZero+6) xMargin cout<<"*                      Shuffle                     *\n";
#define showListSelected clearLineY(yZero+10) xMargin  cout<<"*                     ",yellowColor cout<<"Show List";defaultColor cout<<"                    *\n";
#define showListUnselected clearLineY(yZero+10) xMargin cout<<"*                     Show List                    *\n";
#define welcomeExitSelected clearLineY(yZero+1) xMargin  cout<<"*                     "; greenTextForegroundColor cout<<"C L I M P";defaultTextForegroundColor cout<<"                 ";yellowColor cout<<"X";defaultColor cout<<"  *\n";
#define welcomeExitUnselected clearLineY(yZero+1) xMargin cout<<"*                     "; greenTextForegroundColor cout<<"C L I M P";defaultTextForegroundColor cout<<"                 ";redTextBackgroundColor cout<<"X";defaultTextBackgroundColor cout<<"  *\n";

#define prevAndNextUnselected clearLineY(yZero+13) xMargin cout<<"*  <Previous                                Next>  *\n";
#define prevSelected clearLineY(yZero+13) xMargin cout<<"*  ";yellowColor cout<<"<Previous";defaultColor cout<<"                                Next>  *\n";
#define nextSelected clearLineY(yZero+13) xMargin cout<<"*  <Previous                                ";yellowColor cout<<"Next>";defaultColor cout<<"  *\n";
#define replayUnselected clearLineY(yZero+11) xMargin  cout<<"*                      Replay                      *\n";
#define replaySelected clearLineY(yZero+11) xMargin  cout<<"*                      ";yellowColor cout<<"Replay";defaultColor cout<<"                      *\n";
#define track1 clearLineY(yZero+6) xMargin cout<<"*                     Track: ";
#define track2 cout<<"                     *\n";
#define duration1 clearLineY(yZero+7) xMargin cout<<"*                  Duration: ";
#define duration2 cout<<"                  *\n";

#define selectSongUnselected clearLineY(yZero+3) xMargin cout<<"*                    Select Song                   *\n";
#define selectSongSelected clearLineY(yZero+3) xMargin cout<<"*                    ";yellowColor cout<<"Select Song";defaultColor cout<<"                   *\n";
#define heading clearLineY(yZero+4) xMargin cout<<"* Track  Title               Artist       Duration *\n";


////////////////////////////////////////////////////////////////////////////////////////////
#endif