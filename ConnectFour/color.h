#include <windows.h>

enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
};
const int FOREGROUND[] = 
{0,                                                                     //Black
FOREGROUND_BLUE,                                                        //Blue
FOREGROUND_GREEN,                                                       //Green
FOREGROUND_BLUE|FOREGROUND_GREEN,                                       //Cyan
FOREGROUND_RED,                                                         //Red
FOREGROUND_RED|FOREGROUND_BLUE,                                         //Magenta
FOREGROUND_RED|FOREGROUND_GREEN,                                        //Brown
FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,                        //Light Gray
0|FOREGROUND_INTENSITY,                                                  //Dark Gray
FOREGROUND_BLUE|FOREGROUND_INTENSITY,                                   //Light Blue
FOREGROUND_GREEN|FOREGROUND_INTENSITY,                                  //Light Green
FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY,                  //Light Cyan
FOREGROUND_RED|FOREGROUND_INTENSITY,                                    //Light Red
FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY,                    //Light Magenta
FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY,                    //Yellow
FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY     //White
};
const int BACKGROUND[] = 
{0,                                                                     //Black
BACKGROUND_BLUE,                                                        //Blue
BACKGROUND_GREEN,                                                       //Green
BACKGROUND_BLUE|BACKGROUND_GREEN,                                       //Cyan
BACKGROUND_RED,                                                         //Red
BACKGROUND_RED|BACKGROUND_BLUE,                                         //Magenta
BACKGROUND_RED|BACKGROUND_GREEN,                                        //Brown
BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE,                        //Light Gray
0|BACKGROUND_INTENSITY,                                                  //Dark Gray
BACKGROUND_BLUE|BACKGROUND_INTENSITY,                                   //Light Blue
BACKGROUND_GREEN|BACKGROUND_INTENSITY,                                  //Light Green
BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY,                  //Light Cyan
BACKGROUND_RED|BACKGROUND_INTENSITY,                                    //Light Red
BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_INTENSITY,                    //Light Magenta
BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY,                    //Yellow
BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY     //White
};
void setcolor(int foreground,int background)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,FOREGROUND[foreground] | BACKGROUND[background]);
}
