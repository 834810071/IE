
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>

char* getMemory(char *p)
{
    p=(char *)malloc(100);
    assert(p != NULL);
    return p;
}
int main() {
    char *str = NULL;
    str = getMemory(str);
    strcpy(str, "he");
    printf("%s", str);

    return 0;
}
