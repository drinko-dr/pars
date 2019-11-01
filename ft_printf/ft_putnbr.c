#include <io.h>

void ft_putnbr(int num)
{
	if (num / 10 > 0)
		ft_putnbr(num /10);
	num %= 10;
	write(1, &num, 1);
}
