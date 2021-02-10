#include<stdio.h>                                                                                           
#include<stdlib.h>    
                                                                                     
   // The sample buffer contains "©ha®a©te®s" in UTF-8
    unsigned char buffer[15] = { 0xc2, 0xa9, 0x68, 0x61, 0xc2, 0xae, 0x61, 0xc2, 0xa9, 0x74, 0x65, 0xc2, 0xae, 0x73, 0x00 };
    // utf8 is the pointer to your UTF-8 string
    char* utf8 = (char*)buffer;
    // convert multibyte UTF-8 to wide string UTF-16
    int length = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8, -1, NULL, 0);
    if (length > 0)
    {
        wchar_t* wide = new wchar_t[length];
        MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8, -1, wide, length);

        // convert it to ANSI, use setlocale() to set your locale, if not set
        size_t convertedChars = 0;
        char* ansi = new char[length];
        wcstombs_s(&convertedChars, ansi, length, wide, _TRUNCATE);
    }
