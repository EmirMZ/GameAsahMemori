#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>

int GetColumnWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE out;
    
    if (!(out = GetStdHandle(STD_OUTPUT_HANDLE)) ||
        !GetConsoleScreenBufferInfo(out, &info))
        return 80;
    return info.dwSize.X;
}
#else
int GetColumnWidth() {return 80;}
#endif

void print_center(char *text)
{

    const int total_width = GetColumnWidth();
    const int text_width = strlen(text);
    const int field_width = (total_width - text_width) / 2 + text_width;

    printf("%*s\n", field_width, text);
}
