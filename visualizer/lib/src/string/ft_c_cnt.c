#include "libft.h"

int ft_c_cnt(char *str, char c)
{
	int i;
	int cnt;

	i = -1;
	cnt = 0;
	while (str[++i])
		if (str[i] == c)
			cnt++;
	return (cnt);
}
