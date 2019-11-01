#include <stdarg.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

void ft_putnbr(int num);

void ft_putnbr(int num)
{
	if (num / 10 > 0)
		ft_putnbr(num /10);
	num %= 10;
	num += '0';
	write(1, &num, 1);
}

char *print_str(char *str)
{
	while (*str && *str != '%')
		write(1, str++, 1);
	return (str);
}

char *digit(char *str, va_list ap)
{
	int x = va_arg(ap, int);
	ft_putnbr(x);
	return (str + 2);
}

char *persent(char *str, va_list ap)
{
	write(1, "%%", 1);
	return (str + 2);
}

int ft_strncmp(char *str1, char *str2, int n)
{
	while (*str1 ==*str2 && n-- > 0)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

int num_count(int num)
{
	int count = 0;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

void flag_d(char *str, va_list ap)
{

}

char *width(char *str, va_list ap)
{
	int num = 0;
	int point = 0;
	if (*str == '0')
	{
		while (*str == '0')
			str++;
		point = 1;
	}
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - '0');
	int x = va_arg(ap, int);
	num -= num_count(x);
	if (point == 1)
		while (num-- > 0)
			write (1, "0", 1);
	else
		while (num-- > 0)
			write (1, " ", 1);
	ft_putnbr(x);
	return (str + 1);
}

int parser(char *str, va_list ap)
{
	int point = 0;
	str = print_str(str);
	if (!ft_strncmp(str, "%d", 1))
		str = digit(str, ap);
	if (!ft_strncmp(str, "%%", 1))
		str = persent(str, ap);
	if (*str == '%' && *(str + 1) >= '0')
		str = width(str + 1, ap);
	if (*str != '\0')
		parser(str, ap);
	return (1);
}

void ft_printf(char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	parser(format, ap);
	va_end(ap);

}

int main ()
{
	int x = 42;
	// ft_printf("some text for test %d one more text befor next %%", x);
	ft_printf("%10d", 54);
	ft_printf("%010d", 54);
	// printf("%0000000005d", 42);
	//printf("**%5d**%5.3d**%05d**%05.3d**\n", 6, 6, 6, 6);
	return (0);
}
