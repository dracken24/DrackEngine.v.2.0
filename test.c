/* =============================================================================== */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/*               -------------------------------------------------                 */
/*                PROJET: DrackEngine   PAR: Dracken24                             */
/*               -------------------------------------------------                 */
/*                CREATED: 06-12th-2024                                            */
/*                MODIFIED BY: Dracken24                                           */
/*                LAST MODIFIED: 06-12th-2024                                      */
/*               -------------------------------------------------                 */
/*                FILE: test.c                                                     */
/*               -------------------------------------------------                 */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/* =============================================================================== */

#include <unistd.h>

void ft_putstr(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        write(0, &str[i], 1);
        i++;
    }
}

int main(void)
{
    char str[15] = "Hello World !!";

    ft_putstr(str);

    return 0;
}