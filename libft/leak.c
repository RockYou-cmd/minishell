#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    while(1)
    {
        system("while true; do leaks minishell; done");
        // sleep(2);
        // system("clear");
    }
}