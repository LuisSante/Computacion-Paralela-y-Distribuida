#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*-----------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int n = 10; // shared
    int a = 7;  // shared

// implicito
#pragma omp parallel for
    for (int i = 0; i < n; i++) // i private
    {
        int b = a + i; // b private
    }
    return 0;

// explicito
#pragma omp parallel for shared(n, a)
    for (int i = 0; i < n; i++)
    {
        int b = a + i;
    }

    int b;
#pragma omp parallel for shared(n, a) private(b)
    for (int i = 0; i < n; i++)
    {
        b = a + i;
    }

    // default
    //establece los atributos de uso compartido de datos de todas las variables en la construcción para compartir
    int a, b, c, n;

#pragma omp parallel for default(shared)
    for (int i = 0; i < n; i++)
    {
        // using a, b, c
    }
}