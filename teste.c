#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    float a, b, c;
    for(c=0;c<15;c++)
    {
        scanf("%f %f", &a, &b);
        printf("%f\n", b/a);
    }
    return 0;
}
