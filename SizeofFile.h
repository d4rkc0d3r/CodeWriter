#ifndef SIZEOFFILE_H_INCLUDED
#define SIZEOFFILE_H_INCLUDED

#include <cstdio>

int SizeOfFile(const char* filename)
{
    FILE* pFile = fopen(filename,"rb");
    if(pFile==NULL)
        return EOF;
    fseek(pFile, 0, SEEK_END);
    int n = ftell(pFile);
    fclose(pFile);
    return n;
}

#endif // SIZEOFFILE_H_INCLUDED
