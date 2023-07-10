#include<stdio.h>
#include<stdlib.h>

char CoderMin(char c, int CleMin)
{
    return ((char)('a'+(c-'a'+CleMin)%26));
}
char CoderMaj(char c, int CleMaj)
{
    return ((char)('A'+(c-'A'+CleMaj)%26));
}
char CoderNum(char c, int CleNum)
{
    return ((char)('0'+(c-'0'+CleNum)%10));
}
char DeCoderMin(char c, int CleMin)
{
    return ((char)('z'-('z'-c+CleMin)%26));
}
char DeCoderMaj(char c, int CleMaj)
{
    return ((char)('Z'-('Z'-c+CleMaj)%26));
}
char DeCoderNum(char c, int CleNum)
{
    if ((c-'0') < CleNum) return ((char)('9'-(CleNum-(c-'0'+1))));
    return ((char)(c-CleNum));
}
int TypeCar(char c)
{
    if (('a' <= c) && (c <= 'z')) return ((int)1);
    if (('A' <= c) && (c <= 'Z')) return ((int)2);
    if (('0' <= c) && (c <= '9')) return ((int)3);
    return ((int)0);
}
void CoderPhrase(int CleMin, int CleMaj, int CleNum)
{
    char c;
    int rt;
    printf("\nTaper votre phrase : ");
    while ((c=getchar())!='\n')
    {
        rt = TypeCar(c);
        switch (rt)
        {
            case 0: printf("%c",c); break;
            case 1: printf("%c",CoderMin(c, CleMin)); break;
            case 2: printf("%c",CoderMaj(c, CleMaj)); break;
            case 3: printf("%c",CoderNum(c, CleNum)); break;
        }
    }
}
void DeCoderPhrase(int CleMin, int CleMaj, int CleNum)
{
    char c;
    int rt;
    printf("\nTaper votre phrase : ");
    while ((c=getchar())!='\n')
    {
        rt = TypeCar(c);
        switch (rt)
        {
            case 0: printf("%c",c); break;
            case 1: printf("%c",DeCoderMin(c, CleMin)); break;
            case 2: printf("%c",DeCoderMaj(c, CleMaj)); break;
            case 3: printf("%c",DeCoderNum(c, CleNum)); break;
        }
    }
}

void main()
{
    CoderPhrase(3,3,4);
    DeCoderPhrase(3,3,4);
}