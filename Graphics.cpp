#include "Graphics.h"
#include <windows.h>

void Color(e_color texte, e_color fond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, fond*16+texte);
}
