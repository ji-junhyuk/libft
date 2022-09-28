#include <stdio.h>

int main(int argc, char **argv,char **envp)
{
    int i = 0;

    printf("=== environment list ===\n");
    for(i=0; envp[i];i++)
    {
        printf("<%2d>: %s\n", i, envp[i]);
    }
    return 0;
}
