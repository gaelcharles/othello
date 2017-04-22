#include "Console.h"
#include <conio.h>
#include <allegro.h>
#include <winalleg.h>

Console* Console::m_instance = NULL;

Console::Console()
{
    m_instance = NULL;
}

Console::~Console()
{

}

void Console::deleteInstance()
{
    delete m_instance;
    m_instance = NULL;
}

Console* Console::getInstance()
{
    if (!Console::m_instance)
    {
        m_instance = new Console();
    }

    return m_instance;
}


void Console::gotoLigCol(int lig, int col)
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void Console::gotoDamierXY(int x, int y)
{
    gotoLigCol(2*y+1, 4*x+2);
}

int Console::getInputKey()
{
    return getch();
}

bool Console::isKeyboardPressed()
{
    return kbhit();
}

void Console::setColor(e_color texte, e_color fond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,fond*16+texte);
}

void Console::espacer(int espacement)
{
    if(espacement >= 0 && espacement < 80)
    {
        for(int i(0) ; i<espacement ; i++)
            std::cout << ' ';
    }
}
