#include <stdarg.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <io.h>
#include <stdint.h>
int len_digit(t_flag *flag, int count);

void print_base(intmax_t num, int base, t_flag *flag)
{
	char c = 'a';
	if (num / base > 0)
		print_base(num / base, base, flag);
	if (flag->flag != NULL && (flag->flag[0] == 'X' || flag->flag[1] == 'X' || flag->flag[2] == 'X'))
		c = 'A';
	num =  num % base;
	num += (num > 9 ? c - 10 : '0');
	write (1, &num, 1);
}

// void print_point(t_flag *flag)
// {
// 	while (flag->point-- > 0)
// 			write (1, "0", 1);
// }

void ft_putnbr(intmax_t num, int base, t_flag *flag)
{
	if (num / 10 > 0)
		ft_putnbr(num / 10, base, flag);
	num %= 10;
	num += '0';
	write(1, &num, 1);
}

//выводит число
int print_num(intmax_t num, t_flag *flag, void fun(intmax_t, int, t_flag*), int base)
{
	int len = 0;
	if (num < 0)
	{
		write(1, "-", len += 1);
		num *= -1;
		flag->plus = '\0';
	}
	else if (flag->plus == '+' && base == 10)
		write(1, "+", len += 1);
	else if (flag->octothorp == '#' && base == 8)
		write(1, "0", len += 1);
	else if (flag->octothorp == '#' && flag->flag != NULL && (flag->flag[0] == 'X' || flag->flag[1] == 'X' || flag->flag[2] == 'X'))
		write(1, "0X", len += 2);
	else if (flag->octothorp == '#' && base == 16)
		write(1, "0x", len += 2);
	else if (flag->plus == ' ')
		write(1, " ", len += 1);
	flag->plus = '\0';
	// print_point(flag);
	int x = flag->point;
	while (x-- > 0)
			write (1, "0", 1);
	fun(num, base, flag);
	// if (num / 10 > 0)
	// 	ft_putnbr(num /10, flag);
	// num %= 10;
	// num += '0';
	// write(1, &num, 1);
	return (len);
}
//выводит строку до знака %
int print_str(char *str)
{
	int len = 0;
	while (str[len] && str[len] != '%')
		write(1, &str[len++], 1);
	return (len);
}
// хз зачем
// char *digit(char *str, va_list ap)
// {
// 	int x = va_arg(ap, int);
// 	// ft_putnbr(x);
// 	return (str + 2);
// }
//лень на разных компах подключать библиотеки поэтому
//вставлю тут функции (не забыть бы убрать)
int ft_strncmp(char *str1, char *str2, int n)
{
	while (*str1 ==*str2 && n-- > 0)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
// счетчик цифр в int
int num_count(intmax_t num)
{
	int count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}
//мини atoi
int get_digit(char **str)
{
	int num = 0;
	while (**str >= '0' && **str <= '9')
		num = num * 10 + (*(*str)++ - '0');
	return (num);
}
/*сохранение флага точности, если число не float или double
*то к выводимому числу добавляются 0 с переди
*учитывая флаг ширины
*
*/
void point(char **str, t_flag **flag, va_list *ap)
{
	if (**str == ' ')
	{
		(*flag)->plus = ' ';
		while (**str == ' ')
			(*str)++;
	}
	while (**str == ' ')
			(*str)++;
	if (**str == '.')
		(*str)++;
	if (**str == '*')
	{
		(*flag)->point = va_arg(*ap, int);
		(*str)++;
	}
	else
		(*flag)->point = get_digit(str);
}

void octothorp(char **str, t_flag **flag)
{
	if (**str == '#')
	{
		(*flag)->octothorp = '#';
		(*str)++;
	}
	if (**str == '+')
	{
		(*flag)->plus = '+';
		(*str)++;
	}
}

// сохранение флага ширины и определение чем заполнять ширину 0 или space
void width(char **str, t_flag **flag, va_list *ap)
{
	if (**str == '0')
	{
		while (**str == '0')
			(*str)++;
		(*flag)->kind_width = '0';
	}
	if (**str == '-')
	{
		(*flag)->position = '-';
		(*str)++;
	}
	if (**str == '*')
	{
		(*flag)->width = va_arg(*ap, int);
		(*str)++;
	}
	else
		(*flag)->width = get_digit(str);
}

int ft_strlen(char *str)
{
	int count = 0;
	while (str[count])
		count++;
	return (count);
}

int flag_s(char *ap, t_flag **flag)
{
	char *str;
	str = ap;
	int count = 0;
	// va_arg(*ap, char*);
	if (ap != NULL)
		count = ft_strlen(str);
	else
		write(1, "(null)", 6);
	if ((*flag)->point != 0)
	{
		(*flag)->point - count > 0 ? 0 : (count = (*flag)->point);
	}
	(*flag)->width -= count;
	int x = (*flag)->width;
	if ((*flag)->position == '-')
	{
		write(1, str, count);
		while (x-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		write(1, str, count);
	}
	return (len_digit(*flag, count));
}

//вывод флага d
/* для остальных флагов нужны почти теже действия
* меняется только тип данных для счетчика и выводимого значения
* хотелось бы передовать адрес функции в функцию в зависимости от
* флагов, если это имеет смысл
*/
// int flag_d(va_list *ap, t_flag **flag)

int len_digit(t_flag *flag, int count)
{
	int len = 0;
	if (flag->width > 0)
		len += flag->width;
	if (flag->point)
		len += flag->point;
	len += count;
	return (len);
}

int print_position(intmax_t num, t_flag **flag, void fun(intmax_t, int, t_flag*), int base)
{
	int len = 0;
	if ((*flag)->octothorp == '#' && base == 16)
	{
		(*flag)->width -= 2;
		if ((*flag)->point == 0 && (*flag)->kind_width == '0')
		{
			(*flag)->point = (*flag)->width;
			(*flag)->width = 0;
		}
	}
	int x = (*flag)->width;
	if (((*flag)->position != '\0'))
	{
		len = print_num(num, *flag, fun, base);
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		len = print_num(num, *flag, fun, base);
	}
	return (len);
}

int flag_d(intmax_t num, t_flag **flag, void fun(intmax_t, int, t_flag*), int base)
{
	// int num = va_arg(*ap, int);
	int count = num_count(num);
	if ((*flag)->point != 0 || (*flag)->position != '\0')
	{
		(*flag)->kind_width = ' ';
		(*flag)->point - count > 0 ? (*flag)->width -= ((*flag)->point - count) : 0;
		(*flag)->point = (*flag)->point - count;
	}
	(*flag)->width -= count;
	if (((num < 0 || (*flag)->plus == '+' ) && base == 10) || ((*flag)->octothorp == '#' && base == 8))
	{
		(*flag)->width -= 1;
		if ((*flag)->point == 0 && (*flag)->kind_width == '0')
		{
			(*flag)->point = (*flag)->width;
			(*flag)->width = 0;
		}
	}
	count += print_position(num, flag, fun, base);
	// if (((*flag)->position != '\0'))
	// {
	// 	ft_putnbr(num, *flag);
	// 	while ((*flag)->width-- > 0)
	// 		write(1, &(*flag)->kind_width, 1);
	// }
	// else
	// {
	// 	while ((*flag)->width-- > 0)
	// 		write(1, &(*flag)->kind_width, 1);
	// 	ft_putnbr(num, *flag);
	// }
	return (len_digit(*flag, count));
}
//еще одна
char *ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (str);
}
//проверка на валидный флаг, возвращает 0 если такого флага нет
// int check_flag(char *str)
// {
// 	//   d, i           o, u, x, X
// 	if (!ft_strncmp(str, "hhd", 2) || !ft_strncmp(str, "hhi", 2)
// 	|| !ft_strncmp(str, "hho", 2) || !ft_strncmp(str, "hhu", 2)
// 	|| !ft_strncmp(str, "hhx", 2) || !ft_strncmp(str, "hhX", 2)
// 	|| !ft_strncmp(str, "lld", 2) || !ft_strncmp(str, "lli", 2)
// 	|| !ft_strncmp(str, "llo", 2) || !ft_strncmp(str, "llu", 2)
// 	|| !ft_strncmp(str, "llx", 2) || !ft_strncmp(str, "llX", 2))
// 		return (3);
// 	if (!ft_strncmp(str, "hd", 1) || !ft_strncmp(str, "hi", 1)
// 	|| !ft_strncmp(str, "ho", 1) || !ft_strncmp(str, "hu", 1)
// 	|| !ft_strncmp(str, "hx", 1) || !ft_strncmp(str, "hX", 1)
// 	|| !ft_strncmp(str, "ld", 1) || !ft_strncmp(str, "li", 1)
// 	|| !ft_strncmp(str, "lo", 1) || !ft_strncmp(str, "lu", 1)
// 	|| !ft_strncmp(str, "lx", 1) || !ft_strncmp(str, "lX", 1))
// 		return (2);
// 	if (*str == 'd' || *str == 'i' || *str == 'o' || *str == 'u'
// 	|| *str == 'x' || *str == 'X' || *str == '%' || *str == 's')
// 		return (1);
// 	return (0);
// }
// возможно мне не нужен односвязный список, достаточно каждый раз обнулять одну структуру
//
// int flag_oxX(intmax_t num, t_flag **flag)
// {
// 	// int num = va_arg(*ap, int);
// 	int count = num_count(num);
// 	if ((*flag)->point != 0 || (*flag)->position != '\0')
// 	{
// 		(*flag)->kind_width = ' ';
// 		(*flag)->point - count > 0 ? (*flag)->width -= ((*flag)->point - count) : 0;
// 		(*flag)->point = (*flag)->point - count;
// 	}
// 	if (num < 0)
// 		(*flag)->width -= 1;
// 	int x = (*flag)->width - count;
// 	if (((*flag)->position != '\0'))
// 	{
// 		ft_putnbr(num, *flag);
// 		while (x-- > 0)
// 			write(1, &(*flag)->kind_width, 1);
// 	}
// 	else
// 	{
// 		while (x-- > 0)
// 			write(1, &(*flag)->kind_width, 1);
// 		ft_putnbr(num, *flag);
// 	}
// 	return (len_digit(*flag, count));
// }

void list_start(t_flag **node)
{
	(*node)->flag = NULL;
	// (*node)->flag[0] = '\0';
	// (*node)->flag[1] = '\0';
	// (*node)->flag[2] = '\0';
	(*node)->kind_width = ' ';
	(*node)->point = 0;
	(*node)->width = 0;
	(*node)->next = NULL;
	(*node)->position = '\0';
	(*node)->plus = '\0';
	// (*node)->argc = (char *)malloc(sizeof(char) * (num_count));
}
//ищет ширину, точность, и валидный флаг
/*если будет медленно работать с большими числами
* стоит сначало как то обработать валидный флаг, а потом уже
* искать ширину и точность
*/
void get_flag(char **str, t_flag **flag, va_list *ap)
{
	int	i;
	int n;

	i = 0;
	n = 0;
	list_start(flag);
	octothorp(str, flag);
	width(str, flag, ap);
	point(str, flag, ap);
	if ((*flag)->octothorp != '#')
		octothorp(str, flag);
	if ((*flag)->width == 0)
		width(str, flag, ap);
	if ((*flag)->point == 0)
		point(str, flag, ap);
	//   d, i           o, u, x, X
	// if ((n = check_flag(*str)))
	// 	while (n-- > 0)
	// 		(*flag)->flag[i++] = (*((*str)++));
}

void move_flag(t_flag **flag, char **str, int n)
{
	int i = 0;
	while (n-- > 0)
		(*((*str)++));
			// (*flag)->flag[i++] = (*((*str)++));
}

int diu_flags(va_list *ap, t_flag **flag, char **str)
{
	int n = 0;
	int pc = 0;
	if (**str == 'd' || **str == 'i')
		pc = flag_d((int)va_arg(*ap, int), flag, &ft_putnbr, 10);
	else if (**str == 'u')
		pc = flag_d((unsigned int)va_arg(*ap, unsigned int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "ld", (n = 1)) || !ft_strncmp(*str, "li", (n = 1)))
		pc = flag_d((long)va_arg(*ap, long int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "lu", (n = 1)))
		pc = flag_d((unsigned long int)va_arg(*ap, unsigned long int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "llu", (n = 2)))
		pc = flag_d((unsigned long long int)va_arg(*ap, unsigned long long int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "lld", (n = 2)) || !ft_strncmp(*str, "lli", (n = 2)))
		pc = flag_d((long long)va_arg(*ap, long long int), flag, &ft_putnbr, 10);
	else
		return (0);
	move_flag(flag, str, (n += 1));
	return (pc);
}

int oxX_flags(va_list *ap, t_flag **flag, char **str)
{
	int n = 0;
	int pc = 0;
	if (**str == 'o')
		pc = flag_d((unsigned int)va_arg(*ap, unsigned int), flag, &print_base, 8);
	else if (**str == (*((*flag)->flag = "x\0\0")) || **str == (*((*flag)->flag = "X\0\0")))
		pc = flag_d((unsigned int)va_arg(*ap, unsigned int), flag, &print_base, 16);
	else if (!ft_strncmp(*str, "lo", (n = 1)))
		pc = flag_d((unsigned long int)va_arg(*ap, unsigned long int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, "llo", (n = 2)))
		pc = flag_d((unsigned long long int)va_arg(*ap, unsigned long long int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, ((*flag)->flag = "lx\0"), (n = 1)) || !ft_strncmp(*str, ((*flag)->flag = "lX\0"), (n = 1)))
		pc = flag_d((unsigned long)va_arg(*ap, unsigned long int), flag, &print_base, 16);
	else if (!ft_strncmp(*str, ((*flag)->flag = "llx"), (n = 2)) || !ft_strncmp(*str, ((*flag)->flag = "llX"), (n = 2)))
		pc = flag_d((unsigned long long)va_arg(*ap, unsigned long long int), flag, &print_base, 16);
	else
		return (0);
	move_flag(flag, str, (n += 1));
	return (pc);
}

int hh_flags(va_list *ap, t_flag **flag, char **str)
{
	int n = 0;
	int pc = 0;
	if (!ft_strncmp(*str, "ho", (n = 1)))
		pc = flag_d((unsigned short)va_arg(*ap, unsigned int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, "hho", (n = 2)))
		pc = flag_d((unsigned char)va_arg(*ap, unsigned int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, "hx", (n = 1)) || !ft_strncmp(*str, ((*flag)->flag = "hX"), (n = 1)))
		pc = flag_d((unsigned short)va_arg(*ap, unsigned int), flag, &print_base, 16);
	else if (!ft_strncmp(*str, "hhx", (n = 2)) || !ft_strncmp(*str, ((*flag)->flag = "hhX"), (n = 2)))
		pc = flag_d((unsigned char)va_arg(*ap, unsigned int), flag, &print_base, 16);
	else if (!ft_strncmp(*str, "hd", (n = 1)) || !ft_strncmp(*str, "hi", (n = 1)))
		pc = flag_d((short)va_arg(*ap, int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "hu", (n = 1)))
		pc = flag_d((unsigned short)va_arg(*ap, unsigned int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "hhu", (n = 2)))
		pc = flag_d((unsigned char)va_arg(*ap, unsigned int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "hhd", (n = 2)) || !ft_strncmp(*str, "hhi", (n = 2)))
		pc = flag_d((signed char)va_arg(*ap, int), flag, &ft_putnbr, 10);
	else
		return (0);
	move_flag(flag, str, (n += 1));
	return (pc);
}

int easy_flag(va_list *ap, t_flag **flag, char **str)
{
	int len = 0;
	if (*str[len] == '%')
		len += flag_s("%", flag);
	else if (*str[len] == 's')
		len += flag_s(va_arg(*ap, char*), flag);
	else
		return (0);
	move_flag(flag, str, 1);
	return (len);
}

//пока не решил как будет называться
//вывод след строки и флага будет идти через цикл скорее всего
int parser(char *str, va_list *ap, t_flag **flag)
{
	char *start;
	int len = 0;
    	while (*str != '\0')
	{
		start = str;
		int l = 0;
		str = ft_strchr(str, '%');
		if (*str != '\0')
			str++;
		get_flag(&str, flag, ap);
		len += print_str(start);
		if ((l = easy_flag(ap, flag, &str)))
			len += l;
		else if ((l = diu_flags(ap, flag, &str)))
			len += l;
		else if ((l = oxX_flags(ap, flag, &str)))
			len += l;
		else if ((l = hh_flags(ap, flag, &str)))
			len += l;
	}
	return (len);
}
//тупо набор функций
int ft_printf(char *format, ...)
{
	int len = 0;
	va_list ap;
	t_flag *flag = NULL;
	flag = (t_flag *)malloc(sizeof(t_flag));
	va_start(ap, format);
	len = parser(format, &ap, &flag);
	va_end(ap);
	return (len);
}
#define ANSI_COLOR_GREEN   "\x1b[32m"
int main ()
{
// 	FAILED TESTS:\n
// # TEST NUMBER (TYPE OF ARG)
//   INSTRUCTION();
//   1. your function ft_printf
//   2. unix function printf
//      (returned value) -->written on stdout<--

// # 0007
  ft_printf("%5%");
//   1. (    1) -->    %<--
//   2. (    5) -->    %<--
ft_printf("\n");
// # 0008
  ft_printf("%-5%");
//   1. (    1) -->%    <--
//   2. (    5) -->%    <--
ft_printf("\n");
// # 0012 (int)
  ft_printf("%x", 42);
//   1. (    1) -->9A<--
//   2. (    2) -->2a<--
ft_printf("\n");
// # 0013 (int)
  ft_printf("%X", 42);
//   1. (    1) -->9A<--
//   2. (    2) -->2A<--
ft_printf("\n");
// # 0014 (int)
  ft_printf("%x", 0);
//   1. (   -1) -->7<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0015 (int)
  ft_printf("%X", 0);
//   1. (   -1) -->7<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0016 (int)
  ft_printf("%x", -42);
//   1. (    9) -->FFFFFFD=<--
//   2. (    8) -->ffffffd6<--
ft_printf("\n");
// # 0017 (int)
  ft_printf("%X", -42);
//   1. (    9) -->FFFFFFD=<--
//   2. (    8) -->FFFFFFD6<--
ft_printf("\n");
// # 0018 (int)
  ft_printf("%x", 4294967296);
//   1. (   -1) -->7<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0019 (int)
  ft_printf("%X", 4294967296);
//   1. (   -1) -->7<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0020 (int)
  ft_printf("%x", 2);
//   1. (   -1) -->7<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0021 (int)
  ft_printf("%10x", 42);
//   1. (    1) -->        9A<--
//   2. (   10) -->        2a<--
ft_printf("\n");
// # 0022 (int)
  ft_printf("%-10x", 42);
//   1. (   -1) -->9A        <--
//   2. (   10) -->2a        <--
ft_printf("\n");
// # 0023 (int)
  ft_printf("%llx", 4294967296);
  printf("%llx", 4294967296);
//   1. (    9) -->877777777<--
//   2. (    9) -->100000000<--
ft_printf("\n");
// # 0024 (int)
  ft_printf("%llX", 4294967296);
//   1. (    9) -->877777777<--
//   2. (    9) -->100000000<--
ft_printf("\n");
// # 0025 (int)
  ft_printf("%hx", 4294967296);
//   1. (    2) -->hx<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0026 (int)
  ft_printf("%hhX", 4294967296);
//   1. (    3) -->hhX<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0027 (int)
  ft_printf("%llx", 9223372036854775807); //error
//   1. (   18) -->>FFFFFFFFFFFFFFF<--
//   2. (   16) -->7fffffffffffffff<--
ft_printf("\n");
// # 0028 (int)
  ft_printf("%llx", 9223372036854775808);
  printf("%llx", 9223372036854775808);
//   1. (   18) -->>FFFFFFFFFFFFFFF<--
//   2. (   16) -->7fffffffffffffff<--
ft_printf("\n");
// # 0029 (int)
  ft_printf("%010x", 542);
//   1. (    2) -->000000098E<--
//   2. (   10) -->000000021e<--
ft_printf("\n");
// # 0030 (int)
  ft_printf("%-15x", 542);
//   1. (   -1) -->98E            <--
//   2. (   15) -->21e            <--
ft_printf("\n");
// # 0031 (int)
  ft_printf("%2x", 542);
//   1. (    2) -->98E<--
//   2. (    3) -->21e<--
ft_printf("\n");
// # 0032 (int)
  ft_printf("%.2x", 5427);
//   1. (    1) -->8<::<--
//   2. (    4) -->1533<--
ft_printf("\n");
// # 0033 (int)
  ft_printf("%5.2x", 5427);
//   1. (    1) --> 8<::<--
//   2. (    5) --> 1533<--
ft_printf("\n");
// # 0034 (int)
  ft_printf("%#x", 42);
//   1. (    1) -->9A<--
//   2. (    4) -->0x2a<--
ft_printf("\n");
// # 0035 (int)
  ft_printf("%#llx", 9223372036854775807);
//   1. (   18) -->>FFFFFFFFFFFFFFF<--
//   2. (   18) -->0x7fffffffffffffff<--
ft_printf("\n");
// # 0036 (int)
  ft_printf("%#x", 0);
//   1. (   -1) -->7<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0037 (int)
  ft_printf("%#x", 42);
//   1. (    1) -->9A<--
//   2. (    4) -->0x2a<--
ft_printf("\n");
// # 0038 (int)
  ft_printf("%#X", 42);
//   1. (    1) -->9A<--
//   2. (    4) -->0X2A<--
ft_printf("\n");
// # 0039 (int)
  ft_printf("%#8x", 42);
//   1. (    1) -->    9A<--
//   2. (    8) -->    0x2a<--
ft_printf("\n");
// # 0040 (int)
  ft_printf("%#08x", 42);
//   1. (    1) -->00009A<--
//   2. (    8) -->0x00002a<--
ft_printf("\n");
// # 0041 (int)
  ft_printf("%#-08x", 42);
//   1. (   -1) -->9A    <--
//   2. (    8) -->0x2a    <--
ft_printf("\n");
// # 0042 (int)
  ft_printf("@moulitest: %#.x %#.0x", 0, 0); //error
  printf("@moulitest: %#.x %#.0x", 0, 0);
//   1. (   11) -->@moulitest: 7 7<--
//   2. (   13) -->@moulitest:  <--
ft_printf("\n");
// # 0043 (int)
  ft_printf("@moulitest: %.x %.0x", 0, 0); //error
//   1. (   11) -->@moulitest: 7 7<--
//   2. (   13) -->@moulitest:  <--
ft_printf("\n");
// # 0044 (int)
  ft_printf("@moulitest: %5.x %5.0x", 0, 0); //error
//   1. (   11) -->@moulitest:      7      7<--
//   2. (   23) -->@moulitest:            <--
ft_printf("\n");
// # 0045 (char *)
  ft_printf("%s", "abc");
//   1. (    1) -->abc<--
//   2. (    3) -->abc<--
ft_printf("\n");
// # 0046 (char *)
  ft_printf("%s", "this is a string");
//   1. (    1) -->this is a string<--
//   2. (   16) -->this is a string<--
ft_printf("\n");
// # 0047 (char *)
  ft_printf("%s ", "this is a string");
//   1. (    2) -->this is a string <--
//   2. (   17) -->this is a string <--
ft_printf("\n");
// # 0048 (char *)
  ft_printf("%s  ", "this is a string");
//   1. (    3) -->this is a string  <--
//   2. (   18) -->this is a string  <--
ft_printf("\n");
// # 0049 (char *)
  ft_printf("this is a %s", "string");
//   1. (   11) -->this is a string<--
//   2. (   16) -->this is a string<--
ft_printf("\n");
// # 0050 (char *)
  ft_printf("%s is a string", "this");
//   1. (   13) -->this is a string<--
//   2. (   16) -->this is a string<--
ft_printf("\n");
// # 0051 (char *)
  ft_printf("Line Feed %s", "\\n");
//   1. (   11) -->Line Feed \\n<--
//   2. (   12) -->Line Feed \\n<--
ft_printf("\n");
// # 0052 (char *)
  ft_printf("%10s is a string", "this");
//   1. (   13) -->      this is a string<--
//   2. (   22) -->      this is a string<--
ft_printf("\n");
// # 0053 (char *)
  ft_printf("%.2s is a string", "this");
//   1. (   13) -->th is a string<--
//   2. (   14) -->th is a string<--
ft_printf("\n");
// # 0054 (char *)
  ft_printf("%5.2s is a string", "this");
//   1. (   13) -->   th is a string<--
//   2. (   17) -->   th is a string<--
ft_printf("\n");
// # 0055 (char *)
  ft_printf("%10s is a string", "");
//   1. (   13) -->           is a string<--
//   2. (   22) -->           is a string<--
ft_printf("\n");
// # 0056 (char *)
  ft_printf("%.2s is a string", "");
//   1. (   13) --> is a string<--
//   2. (   12) --> is a string<--
ft_printf("\n");
// # 0057 (char *)
  ft_printf("%5.2s is a string", "");
//   1. (   13) -->      is a string<--
//   2. (   17) -->      is a string<--
ft_printf("\n");
// # 0058 (char *)
  ft_printf("%-10s is a string", "this");
//   1. (   13) -->this       is a string<--
//   2. (   22) -->this       is a string<--
ft_printf("\n");
// # 0059 (char *)
  ft_printf("%-.2s is a string", "this");
//   1. (   13) -->th is a string<--
//   2. (   14) -->th is a string<--
ft_printf("\n");
// # 0060 (char *)
  ft_printf("%-5.2s is a string", "this");
//   1. (   13) -->th    is a string<--
//   2. (   17) -->th    is a string<--
ft_printf("\n");
// # 0061 (char *)
  ft_printf("%-10s is a string", "");
//   1. (   13) -->           is a string<--
//   2. (   22) -->           is a string<--
ft_printf("\n");
// # 0062 (char *)
  ft_printf("%-.2s is a string", "");
//   1. (   13) --> is a string<--
//   2. (   12) --> is a string<--
ft_printf("\n");
// # 0063 (char *)
  ft_printf("%-5.2s is a string", "");
//   1. (   13) -->      is a string<--
//   2. (   17) -->      is a string<--
ft_printf("\n");
// # 0064 (char *)
  ft_printf("%s %s", "this", "is");
//   1. (    3) -->this is<--
//   2. (    7) -->this is<--
ft_printf("\n");
// # 0065 (char *)
  ft_printf("%s %s %s", "this", "is", "a");
//   1. (    5) -->this is a<--
//   2. (    9) -->this is a<--
ft_printf("\n");
// # 0066 (char *)
  ft_printf("%s %s %s %s", "this", "is", "a", "multi");
//   1. (    7) -->this is a multi<--
//   2. (   15) -->this is a multi<--
ft_printf("\n");
// # 0067 (char *)
  ft_printf("%s %s %s %s string. gg!", "this", "is", "a", "multi", "string");
//   1. (   19) -->this is a multi string. gg!<--
//   2. (   27) -->this is a multi string. gg!<--
ft_printf("\n");
// # 0068 (char *)
  ft_printf("%s%s%s%s%s", "this", "is", "a", "multi", "string");
//   1. (    5) -->thisisamultistring<--
//   2. (   18) -->thisisamultistring<--
ft_printf("\n");
// # 0069 (NULL)
  ft_printf("@moulitest: %s", NULL);
// includes/projects/ft_printf/ft_printf_main.sh: line 206: printf: @moulitest: includes/projects/ft_printf/ft_printf_main.sh: line 159: 31193 Segmentation fault: 11  ./tmp/ft_printf_s sN "@moulitest: %s" ""$: invalid number
//   1. (    0) -->@moulitest: includes/projects/ft_printf/ft_printf_main.sh: line 159: 31193 Segmentation fault: 11  ./tmp/ft_printf_s sN "@moulitest: %s" "NULL"$<--
//   2. (   18) -->@moulitest: (null)<--
ft_printf("\n");
// # 0070 (NULL)
//   ft_printf("%.2c", NULL); //error
//   1. (    1) -->c<--
//   2. (    1) -->^@<--
ft_printf("\n");
// # 0071 (NULL)
//   ft_printf("%s %s", NULL, "string"); //error
// includes/projects/ft_printf/ft_printf_main.sh: line 206: printf: includes/projects/ft_printf/ft_printf_main.sh: line 159: 31299 Segmentation fault: 11  ./tmp/ft_printf_s sN "%s %s" "" "string"$: invalid number
//   1. (    0) -->includes/projects/ft_printf/ft_printf_main.sh: line 159: 31299 Segmentation fault: 11  ./tmp/ft_printf_s sN "%s %s" "NULL" "string"$<--
//   2. (   13) -->(null) string<--
ft_printf("\n");
// # 0072 (char)
  ft_printf("%c", 42); //error
//   1. (    1) -->c<--
//   2. (    1) -->*<--
ft_printf("\n");
// # 0073 (char)
  ft_printf("%5c", 42); //error
//   1. (    1) -->c<--
//   2. (    5) -->    *<--
ft_printf("\n");
// # 0074 (char)
  ft_printf("%-5c", 42); //error
//   1. (    1) -->c<--
//   2. (    5) -->*    <--
ft_printf("\n");
// # 0075 (char)
  ft_printf("@moulitest: %c", 0); //error
//   1. (   13) -->@moulitest: c<--
//   2. (   13) -->@moulitest: ^@<--
ft_printf("\n");
// # 0076 (char)
  ft_printf("%2c", 0); //error
//   1. (    1) -->c<--
//   2. (    2) --> ^@<--
ft_printf("\n");
// # 0077 (char)
  ft_printf("null %c and text", 0); //error
//   1. (   15) -->null c and text<--
//   2. (   15) -->null ^@ and text<--
ft_printf("\n");
// # 0078 (char)
  ft_printf("% c", 0); //error
//   1. (    1) -->c<--
//   2. (    1) -->^@<--
ft_printf("\n");
// # 0079 (int)
  ft_printf("%o", 40);
//   1. (    1) -->50<--
//   2. (    2) -->50<--
ft_printf("\n");
// # 0080 (int)
  ft_printf("%5o", 41);
//   1. (    1) -->   51<--
//   2. (    5) -->   51<--
ft_printf("\n");
// # 0081 (int)
  ft_printf("%05o", 42);
//   1. (    1) -->00052<--
//   2. (    5) -->00052<--
ft_printf("\n");
// # 0082 (int)
  ft_printf("%-5o", 2500);
//   1. (   -1) -->4704 <--
//   2. (    5) -->4704 <--
ft_printf("\n");
// # 0083 (int)
  ft_printf("%#6o", 2500);
//   1. (    3) --> 04704<--
//   2. (    6) --> 04704<--
ft_printf("\n");
// # 0084 (int)
  ft_printf("%-#6o", 2500);
//   1. (   -1) -->04704 <--
//   2. (    6) -->04704 <--
ft_printf("\n");
// # 0085 (int)
  ft_printf("%-05o", 2500);
//   1. (   -1) -->4704 <--
//   2. (    5) -->4704 <--
ft_printf("\n");
// # 0086 (int)
  ft_printf("%-5.10o", 2500);
//   1. (    3) -->0000004704<--
//   2. (   10) -->0000004704<--
ft_printf("\n");
// # 0087 (int)
  ft_printf("%-10.5o", 2500);
//   1. (    3) -->04704     <--
//   2. (   10) -->04704     <--
ft_printf("\n");
// # 0088 (int)
  ft_printf("@moulitest: %o", 0);
//   1. (   11) -->@moulitest: 0<--
//   2. (   13) -->@moulitest: 0<--
ft_printf("\n");
// # 0089 (int)
  ft_printf("@moulitest: %.o %.0o", 0, 0); //error
//   1. (   11) -->@moulitest: 0 0<--
//   2. (   13) -->@moulitest:  <--
ft_printf("\n");
// # 0090 (int)
  ft_printf("@moulitest: %5.o %5.0o", 0, 0); //error
//   1. (   11) -->@moulitest:      0      0<--
//   2. (   23) -->@moulitest:            <--
ft_printf("\n");
// # 0091 (int)
  ft_printf("@moulitest: %#.o %#.0o", 0, 0); //error
//   1. (   11) -->@moulitest: 00 00<--
//   2. (   15) -->@moulitest: 0 0<--
ft_printf("\n");
// # 0092 (int)
  ft_printf("@moulitest: %.10o", 42);
//   1. (   13) -->@moulitest: 0000000052<--
//   2. (   22) -->@moulitest: 0000000052<--
ft_printf("\n");
// # 0093 (int)
  ft_printf("%d", 1);
//   1. (    0) -->1<--
//   2. (    1) -->1<--
ft_printf("\n");
// # 0094 (int)
  ft_printf("the %d", 1);
//   1. (    4) -->the 1<--
//   2. (    5) -->the 1<--
ft_printf("\n");
// # 0095 (int)
  ft_printf("%d is one", 1);
//   1. (    7) -->1 is one<--
//   2. (    8) -->1 is one<--
ft_printf("\n");
// # 0096 (int)
  ft_printf("%d", -1);
//   1. (    0) -->-1<--
//   2. (    2) -->-1<--
ft_printf("\n");
// # 0097 (int)
  ft_printf("%d", 4242);
//   1. (    3) -->4242<--
//   2. (    4) -->4242<--
ft_printf("\n");
// # 0098 (int)
  ft_printf("%d", -4242);
//   1. (    3) -->-4242<--
//   2. (    5) -->-4242<--
ft_printf("\n");
// # 0099 (int)
  ft_printf("%d", 2147483647);
//   1. (    9) -->2147483647<--
//   2. (   10) -->2147483647<--
ft_printf("\n");
// # 0100 (int)
  ft_printf("%d", 2147483648);
//   1. (    9) -->-2147483648<--
//   2. (   11) -->-2147483648<--
ft_printf("\n");
// # 0101 (int)
  ft_printf("%d", -2147483648);
//   1. (    9) -->-2147483648<--
//   2. (   11) -->-2147483648<--
ft_printf("\n");
// # 0102 (int)
  ft_printf("%d", -2147483649);
//   1. (    9) -->2147483647<--
//   2. (   10) -->2147483647<--
ft_printf("\n");
// # 0103 (int)
  ft_printf("% d", 42);
//   1. (    1) --> 42<--
//   2. (    3) --> 42<--
ft_printf("\n");
// # 0104 (int)
  ft_printf("% d", -42);
//   1. (    1) -->-42<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0105 (int)
  ft_printf("%+d", 42);
//   1. (    1) -->+42<--
//   2. (    3) -->+42<--
ft_printf("\n");
// # 0106 (int)
  ft_printf("%+d", -42);
//   1. (    1) -->-42<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0107 (int)
  ft_printf("%+d", 0);
//   1. (   -1) -->+0<--
//   2. (    2) -->+0<--
ft_printf("\n");
// # 0108 (int)
//   ft_printf("%+d", 4242424242424242424242);
//   1. (    0) -->-1<--
//   2. (    2) -->-1<--

// # 0109 (int)
  ft_printf("% +d", 42);
//   1. (    2) -->+d<--
//   2. (    3) -->+42<--
ft_printf("\n");
// # 0110 (int)
  ft_printf("% +d", -42);
//   1. (    2) -->+d<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0111 (int)
  ft_printf("%+ d", 42); //error
//   1. (    1) --> 42<--
//   2. (    3) -->+42<--
ft_printf("\n");
// # 0112 (int)
  ft_printf("%+ d", -42);
//   1. (    1) -->-42<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0113 (int)
  ft_printf("%  +d", 42); //error
//   1. (    2) -->+d<--
//   2. (    3) -->+42<--
ft_printf("\n");
// # 0114 (int)
  ft_printf("%  +d", -42); //error
//   1. (    2) -->+d<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0115 (int)
  ft_printf("%+  d", 42); //error
//   1. (    1) --> 42<--
//   2. (    3) -->+42<--
ft_printf("\n");
// # 0116 (int)
  ft_printf("%+  d", -42);
//   1. (    1) -->-42<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0117 (int)
  ft_printf("% ++d", 42); //error
//   1. (    3) -->++d<--
//   2. (    3) -->+42<--
ft_printf("\n");
// # 0118 (int)
  ft_printf("% ++d", -42); //error
//   1. (    3) -->++d<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0119 (int)
  ft_printf("%++ d", 42); //error
//   1. (    1) --> 42<--
//   2. (    3) -->+42<--
ft_printf("\n");
// # 0120 (int)
  ft_printf("%++ d", -42);
//   1. (    1) -->-42<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0121 (int)
  ft_printf("%0d", -42);
//   1. (   -2) -->-42<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0122 (int)
  ft_printf("%00d", -42);
//   1. (   -2) -->-42<--
//   2. (    3) -->-42<--
ft_printf("\n");
// # 0123 (int)
  ft_printf("%5d", 42);
//   1. (    1) -->   42<--
//   2. (    5) -->   42<--
ft_printf("\n");
// # 0124 (int)
  ft_printf("%05d", 42);
//   1. (    1) -->00042<--
//   2. (    5) -->00042<--
ft_printf("\n");
// # 0125 (int)
  ft_printf("%0+5d", 42);
//   1. (    1) -->+0042<--
//   2. (    5) -->+0042<--
ft_printf("\n");
// # 0126 (int)
  ft_printf("%5d", -42);
//   1. (    1) -->  -42<--
//   2. (    5) -->  -42<--
ft_printf("\n");
// # 0127 (int)
  ft_printf("%05d", -42);
//   1. (    1) -->-0042<--
//   2. (    5) -->-0042<--
ft_printf("\n");
// # 0128 (int)
  ft_printf("%0+5d", -42);
//   1. (    1) -->-0042<--
//   2. (    5) -->-0042<--
ft_printf("\n");
// # 0129 (int)
  ft_printf("%-5d", 42);
//   1. (   -1) -->42   <--
//   2. (    5) -->42   <--
ft_printf("\n");
// # 0130 (int)
  ft_printf("%-05d", 42);
//   1. (   -1) -->42   <--
//   2. (    5) -->42   <--
ft_printf("\n");
// # 0131 (int)
  ft_printf("%-5d", -42);
//   1. (   -1) -->-42  <--
//   2. (    5) -->-42  <--
ft_printf("\n");
// # 0132 (int)
  ft_printf("%-05d", -42);
//   1. (   -1) -->-42  <--
//   2. (    5) -->-42  <--
ft_printf("\n");
// # 0133 (short)
  ft_printf("%hd", 32767); //error
//   1. (    2) -->hd<--
//   2. (    5) -->32767<--
ft_printf("\n");
// # 0134 (short)
//   ft_printf("%hd", −32768);
//   1. (    2) -->hd<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0135 (short)
  ft_printf("%hd", 32768); //error
//   1. (    2) -->hd<--
//   2. (    6) -->-32768<--
ft_printf("\n");
// # 0136 (short)
//   ft_printf("%hd", −32769);
//   1. (    2) -->hd<--
//   2. (    1) -->0<--

// # 0137 (signed char)
  ft_printf("%hhd", 127); //error
//   1. (    3) -->hhd<--
//   2. (    3) -->127<--
ft_printf("\n");
// # 0138 (signed char)
  ft_printf("%hhd", 128); //error
//   1. (    3) -->hhd<--
//   2. (    4) -->-128<--
ft_printf("\n");
// # 0139 (signed char)
  ft_printf("%hhd", -128); //error
//   1. (    3) -->hhd<--
//   2. (    4) -->-128<--
ft_printf("\n");
// # 0140 (signed char)
  ft_printf("%hhd", -129); //error
//   1. (    3) -->hhd<--
//   2. (    3) -->127<--
ft_printf("\n");
// # 0141 (long)
  ft_printf("%ld", 2147483647);
//   1. (    9) -->2147483647<--
//   2. (   10) -->2147483647<--
ft_printf("\n");
// # 0142 (long)
  ft_printf("%ld", -2147483648);
//   1. (    9) -->-2147483648<--
//   2. (   11) -->-2147483648<--
ft_printf("\n");
// # 0143 (long)
  ft_printf("%ld", 2147483648);
//   1. (    9) -->2147483648<--
//   2. (   10) -->2147483648<--
ft_printf("\n");
// # 0144 (long)
  ft_printf("%ld", -2147483649); //error
//   1. (    9) -->-2147483649<--
//   2. (   11) -->-2147483649<--
ft_printf("\n");
// # 0145 (long long)
  ft_printf("%lld", 9223372036854775807);
//   1. (   18) -->9223372036854775807<--
//   2. (   19) -->9223372036854775807<--
ft_printf("\n");
// # 0146 (long long)
  ft_printf("%lld", -9223372036854775808); //error
//   1. (   18) -->-(<--
//   2. (   20) -->-9223372036854775808<--
ft_printf("\n");
// # 0147 (int)
  ft_printf("%d", 1);
//   1. (    0) -->1<--
//   2. (    1) -->1<--
ft_printf("\n");
// # 0148 (int)
  ft_printf("%d %d", 1, -2);
//   1. (    1) -->1 -2<--
//   2. (    4) -->1 -2<--
ft_printf("\n");
// # 0149 (int)
  ft_printf("%d %d %d", 1, -2, 33);
//   1. (    3) -->1 -2 33<--
//   2. (    7) -->1 -2 33<--
ft_printf("\n");
// # 0150 (int)
  ft_printf("%d %d %d %d", 1, -2, 33, 42);
//   1. (    5) -->1 -2 33 42<--
//   2. (   10) -->1 -2 33 42<--
ft_printf("\n");
// # 0151 (int)
  ft_printf("%d %d %d %d gg!", 1, -2, 33, 42, 0);
//   1. (    9) -->1 -2 33 42 gg!<--
//   2. (   14) -->1 -2 33 42 gg!<--
ft_printf("\n");
// # 0152 (int)
  ft_printf("%4.15d", 42);
//   1. (    1) -->000000000000042<--
//   2. (   15) -->000000000000042<--
ft_printf("\n");
// # 0153 (int)
  ft_printf("%.2d", 4242);
//   1. (    1) -->4242<--
//   2. (    4) -->4242<--
ft_printf("\n");
// # 0154 (int)
  ft_printf("%.10d", 4242);
//   1. (    3) -->0000004242<--
//   2. (   10) -->0000004242<--
ft_printf("\n");
// # 0155 (int)
  ft_printf("%10.5d", 4242);
//   1. (    3) -->     04242<--
//   2. (   10) -->     04242<--
ft_printf("\n");
// # 0156 (int)
  ft_printf("%-10.5d", 4242);
//   1. (    3) -->04242     <--
//   2. (   10) -->04242     <--
ft_printf("\n");
// # 0157 (int)
  ft_printf("% 10.5d", 4242); //error
//   1. (    3) -->.5d<--
//   2. (   10) -->     04242<--
ft_printf("\n");
// # 0158 (int)
  ft_printf("%+10.5d", 4242);
//   1. (    3) -->    +04242<--
//   2. (   10) -->    +04242<--
ft_printf("\n");
// # 0159 (int)
  ft_printf("%-+10.5d", 4242);
//   1. (    3) -->+04242    <--
//   2. (   10) -->+04242    <--
ft_printf("\n");
// # 0160 (int)
  ft_printf("%03.2d", 0); //error
//   1. (   -1) --> 000<--
//   2. (    3) --> 00<--
ft_printf("\n");
// # 0161 (int)
  ft_printf("%03.2d", 1);
//   1. (    0) --> 01<--
//   2. (    3) --> 01<--
ft_printf("\n");
// # 0162 (int)
  ft_printf("%03.2d", -1);
//   1. (    0) -->-01<--
//   2. (    3) -->-01<--
ft_printf("\n");
// # 0163 (int)
  ft_printf("@moulitest: %.10d", -42);
//   1. (   13) -->@moulitest: -0000000042<--
//   2. (   23) -->@moulitest: -0000000042<--
ft_printf("\n");
// # 0164 (int)
  ft_printf("@moulitest: %.d %.0d", 42, 43);
//   1. (   15) -->@moulitest: 42 43<--
//   2. (   17) -->@moulitest: 42 43<--
ft_printf("\n");
// # 0165 (int)
  ft_printf("@moulitest: %.d %.0d", 0, 0); //error
//   1. (   11) -->@moulitest: 0 0<--
//   2. (   13) -->@moulitest:  <--
ft_printf("\n");
// # 0166 (int)
  ft_printf("@moulitest: %5.d %5.0d", 0, 0); //error
//   1. (   11) -->@moulitest:      0      0<--
//   2. (   23) -->@moulitest:            <--
ft_printf("\n");
// # 0167 (unsigned int)
  ft_printf("%u", 0);
//   1. (   -1) -->0<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0168 (unsigned int)
  ft_printf("%u", 1);
//   1. (    0) -->1<--
//   2. (    1) -->1<--
ft_printf("\n");
// # 0169 (unsigned int)
  ft_printf("%u", -1);
//   1. (    9) -->4294967295<--
//   2. (   10) -->4294967295<--
ft_printf("\n");
// # 0170 (unsigned int)
  ft_printf("%u", 4294967295);
//   1. (    9) -->4294967295<--
//   2. (   10) -->4294967295<--
ft_printf("\n");
// # 0171 (unsigned int)
  ft_printf("%u", 4294967296);
//   1. (   -1) -->0<--
//   2. (    1) -->0<--
ft_printf("\n");
// # 0172 (unsigned int)
  ft_printf("%5u", 4294967295);
//   1. (    9) -->4294967295<--
//   2. (   10) -->4294967295<--
ft_printf("\n");
// # 0173 (unsigned int)
  ft_printf("%15u", 4294967295);
//   1. (    9) -->     4294967295<--
//   2. (   15) -->     4294967295<--
ft_printf("\n");
// # 0174 (unsigned int)
  ft_printf("%-15u", 4294967295);
//   1. (   -1) -->4294967295     <--
//   2. (   15) -->4294967295     <--
ft_printf("\n");
// # 0175 (unsigned int)
  ft_printf("%015u", 4294967295);
//   1. (    9) -->000004294967295<--
//   2. (   15) -->000004294967295<--
ft_printf("\n");
// # 0176 (unsigned int)
  ft_printf("% u", 4294967295); //error
//   1. (    9) --> 4294967295<--
//   2. (   10) -->4294967295<--
ft_printf("\n");
// # 0177 (unsigned int)
  ft_printf("%+u", 4294967295); //error
//   1. (    9) -->+4294967295<--
//   2. (   10) -->4294967295<--
ft_printf("\n");
// # 0178 (unsigned long)
  ft_printf("%lu", 4294967295);
//   1. (    9) -->4294967295<--
//   2. (   10) -->4294967295<--
ft_printf("\n");
// # 0179 (unsigned long)
  ft_printf("%lu", 4294967296); //error
//   1. (    9) -->4294967296<--
//   2. (   10) -->4294967296<--
ft_printf("\n");
// # 0180 (unsigned long) //error
  ft_printf("%lu", -42);
//   1. (    1) -->-42<--
//   2. (   20) -->18446744073709551574<--
ft_printf("\n");
// # 0181 (unsigned long long)
  ft_printf("%llu", 4999999999);
//   1. (    9) -->4999999999<--
//   2. (   10) -->4999999999<--
ft_printf("\n");
// # 0182 (unsigned int)
//   ft_printf("@moulitest: %.5u", 42);
//  ft_printf("");                                -> ""
//  ft_printf("\\n");                             -> "\\n"
//  ft_printf("test");                            -> "test"
//  ft_printf("test\\n");                         -> "test\\n"
//  ft_printf("1234");                            -> "1234"
//  ft_printf("%%");                              -> "%"
//  ft_printf("%5%");                             -> "    %"
//  ft_printf("%-5%");                            -> "%    "
//  ft_printf("%.0%");                            -> "%"
//  ft_printf("%%", "test");                      -> "%"
//  ft_printf("%   %", "test");                   -> "%"
//  ft_printf("%x", 42);                          -> "2a"
//  ft_printf("%X", 42);                          -> "2A"
//  ft_printf("%x", 0);                           -> "0"
//  ft_printf("%X", 0);                           -> "0"
//  ft_printf("%x", -42);                         -> "ffffffd6"
//  ft_printf("%X", -42);                         -> "FFFFFFD6"
//  ft_printf("%x", 4294967296);                  -> "0"
//  ft_printf("%X", 4294967296);                  -> "0"
//  ft_printf("%x", test);                        -> "0"
//  ft_printf("%10x", 42);                        -> "        2a"
//  ft_printf("%-10x", 42);                       -> "2a        "
//  ft_printf("%lx", 4294967296);                 -> "100000000"
//  ft_printf("%llX", 4294967296);                -> "100000000"
//  ft_printf("%hx", 4294967296);                 -> "0"
//  ft_printf("%hhX", 4294967296);                -> "0"
//  ft_printf("%llx", 9223372036854775807);       -> "7fffffffffffffff"
//  ft_printf("%llx", 9223372036854775808);       -> "7fffffffffffffff"
//  ft_printf("%010x", 542);                      -> "000000021e"
//  ft_printf("%-15x", 542);                      -> "21e            "
//  ft_printf("%2x", 542);                        -> "21e"
//  ft_printf("%.2x", 5427);                      -> "1533"
//  ft_printf("%5.2x", 5427);                     -> " 1533"
//  ft_printf("%#x", 42);                         -> "0x2a"
//  ft_printf("%#llx", 9223372036854775807);      -> "0x7fffffffffffffff"
//  ft_printf("%#x", 0);                          -> "0"
//  ft_printf("%#x", 42);                         -> "0x2a"
//  ft_printf("%#X", 42);                         -> "0X2A"
//  ft_printf("%#8x", 42);                        -> "    0x2a"
//  ft_printf("%#08x", 42);                       -> "0x00002a"
//  ft_printf("%#-08x", 42);                      -> "0x2a    "
//  ft_printf("@moulitest: %#.x %#.0x", 0, 0);    -> "@moulitest:  "
//  ft_printf("@moulitest: %.x %.0x", 0, 0);      -> "@moulitest:  "
//  ft_printf("@moulitest: %5.x %5.0x", 0, 0);    -> "@moulitest:            "
//  ft_printf("%s", "abc");                       -> "abc"
//  ft_printf("%s", "this is a string");          -> "this is a string"
//  ft_printf("%s ", "this is a string");         -> "this is a string "
//  ft_printf("%s  ", "this is a string");        -> "this is a string  "
//  ft_printf("this is a %s", "string");          -> "this is a string"
//  ft_printf("%s is a string", "this");          -> "this is a string"
//  ft_printf("Line Feed %s", "\\n");             -> "Line Feed \\n"
//  ft_printf("%10s is a string", "this");        -> "      this is a string"
//  ft_printf("%.2s is a string", "this");        -> "th is a string"
//  ft_printf("%5.2s is a string", "this");       -> "   th is a string"
//  ft_printf("%10s is a string", "");            -> "           is a string"
//  ft_printf("%.2s is a string", "");            -> " is a string"
//  ft_printf("%5.2s is a string", "");           -> "      is a string"
//  ft_printf("%-10s is a string", "this");       -> "this       is a string"
//  ft_printf("%-.2s is a string", "this");       -> "th is a string"
//  ft_printf("%-5.2s is a string", "this");      -> "th    is a string"
//  ft_printf("%-10s is a string", "");           -> "           is a string"
//  ft_printf("%-.2s is a string", "");           -> " is a string"
//  ft_printf("%-5.2s is a string", "");          -> "      is a string"
//  ft_printf("%s %s", "this", "is");             -> "this is"
//  ft_printf("%s %s %s", "this", "is", "a");     -> "this is a"
//  ft_printf("%s %s %s %s", "this", "is", "a", "multi"); -> "this is a multi"
//  ft_printf("%s %s %s %s string. gg!", "this", "is", "a", "multi", "string"); -> "this is a multi string. gg!"
//  ft_printf("%s%s%s%s%s", "this", "is", "a", "multi", "string"); -> "thisisamultistring"
//  ft_printf("@moulitest: %s", NULL);            -> "@moulitest: (null)"
//  ft_printf("%.2c", NULL);                      -> "^@"
//  ft_printf("%s %s", NULL, string);             -> "(null) string"
//  ft_printf("%c", 42);                          -> "*"
//  ft_printf("%5c", 42);                         -> "    *"
//  ft_printf("%-5c", 42);                        -> "*    "
//  ft_printf("@moulitest: %c", 0);               -> "@moulitest: ^@"
//  ft_printf("%2c", 0);                          -> " ^@"
//  ft_printf("null %c and text", 0);             -> "null ^@ and text"
//  ft_printf("% c", 0);                          -> "^@"
//  ft_printf("%o", 40);                          -> "50"
//  ft_printf("%5o", 41);                         -> "   51"
//  ft_printf("%05o", 42);                        -> "00052"
//  ft_printf("%-5o", 2500);                      -> "4704 "
//  ft_printf("%#6o", 2500);                      -> " 04704"
//  ft_printf("%-#6o", 2500);                     -> "04704 "
//  ft_printf("%-05o", 2500);                     -> "4704 "
//  ft_printf("%-5.10o", 2500);                   -> "0000004704"
//  ft_printf("%-10.5o", 2500);                   -> "04704     "
//  ft_printf("@moulitest: %o", 0);               -> "@moulitest: 0"
//  ft_printf("@moulitest: %.o %.0o", 0, 0);      -> "@moulitest:  "
//  ft_printf("@moulitest: %5.o %5.0o", 0, 0);    -> "@moulitest:            "
//  ft_printf("@moulitest: %#.o %#.0o", 0, 0);    -> "@moulitest: 0 0"
//  ft_printf("@moulitest: %.10o", 42);           -> "@moulitest: 0000000052"
//  ft_printf("%d", 1);                           -> "1"
//  ft_printf("the %d", 1);                       -> "the 1"
//  ft_printf("%d is one", 1);                    -> "1 is one"
//  ft_printf("%d", -1);                          -> "-1"
//  ft_printf("%d", 4242);                        -> "4242"
//  ft_printf("%d", -4242);                       -> "-4242"
//  ft_printf("%d", 2147483647);                  -> "2147483647"
//  ft_printf("%d", 2147483648);                  -> "-2147483648"
//  ft_printf("%d", -2147483648);                 -> "-2147483648"
//  ft_printf("%d", -2147483649);                 -> "2147483647"
//  ft_printf("% d", 42);                         -> " 42"
//  ft_printf("% d", -42);                        -> "-42"
//  ft_printf("%+d", 42);                         -> "+42"
//   ft_printf("%+d", -42);                        -> "-42"
//   ft_printf("%+d", 0);                          -> "+0"
//  ft_printf("%+d", 4242424242424242424242);     -> "-1"
//   ft_printf("% +d", 42);                        -> "+42"
//   ft_printf("% +d", -42);                       -> "-42"
//   ft_printf("%+ d", 42);                        -> "+42"
//   ft_printf("%+ d", -42);                       -> "-42"
//   ft_printf("%  +d", 42);                       -> "+42"
//   ft_printf("%  +d", -42);                      -> "-42"
//   ft_printf("%+  d", 42);                       -> "+42"
//   ft_printf("%+  d", -42);                      -> "-42"
//   ft_printf("% ++d", 42);                       -> "+42"
//   ft_printf("% ++d", -42);                      -> "-42"
//   ft_printf("%++ d", 42);                       -> "+42"
//   ft_printf("%++ d", -42);                      -> "-42"
//   ft_printf("%0d", -42);                        -> "-42"
//   ft_printf("%00d", -42);                       -> "-42"
//   ft_printf("%5d", 42);                         -> "   42"
//   ft_printf("%05d", 42);                        -> "00042"
//   ft_printf("%0+5d", 42);                       -> "+0042"
//   ft_printf("%5d", -42);                        -> "  -42"
//   ft_printf("%05d", -42);                       -> "-0042"
//   ft_printf("%0+5d", -42);                      -> "-0042"
//   ft_printf("%-5d", 42);                        -> "42   "
//   ft_printf("%-05d", 42);                       -> "42   "
//   ft_printf("%-5d", -42);                       -> "-42  "
//   ft_printf("%-05d", -42);                      -> "-42  "
//   ft_printf("%hd", 32767);                      -> "32767"
//   ft_printf("%hd", −32768);                   -> "0"
//   ft_printf("%hd", 32768);                      -> "-32768"
//   ft_printf("%hd", −32769);                   -> "0"
//   ft_printf("%hhd", 127);                       -> "127"
//   ft_printf("%hhd", 128);                       -> "-128"
//   ft_printf("%hhd", -128);                      -> "-128"
//  ft_printf("%hhd", -129);                      -> "127"
//  ft_printf("%ld", 2147483647);                 -> "2147483647"
//  ft_printf("%ld", -2147483648);                -> "-2147483648"
//  ft_printf("%ld", 2147483648);                 -> "2147483648"
//  ft_printf("%ld", -2147483649);                -> "-2147483649"
//  ft_printf("%lld", 9223372036854775807);       -> "9223372036854775807"
//  ft_printf("%lld", -9223372036854775808);      -> "-9223372036854775808"
//  ft_printf("%d", 1);                           -> "1"
//  ft_printf("%d %d", 1, -2);                    -> "1 -2"
//  ft_printf("%d %d %d", 1, -2, 33);             -> "1 -2 33"
//  ft_printf("%d %d %d %d", 1, -2, 33, 42);      -> "1 -2 33 42"
//  ft_printf("%d %d %d %d gg!", 1, -2, 33, 42, 0); -> "1 -2 33 42 gg!"
//  ft_printf("%4.15d", 42);                      -> "000000000000042"
//  ft_printf("%.2d", 4242);                      -> "4242"
//  ft_printf("%.10d", 4242);                     -> "0000004242"
//  ft_printf("%10.5d", 4242);                    -> "     04242"
//  ft_printf("%-10.5d", 4242);                   -> "04242     "
//  ft_printf("% 10.5d", 4242);                   -> "     04242"
//  158. FAIL ft_printf("%+10.5d", 4242);                   -> "    +04242"
//  ft_printf("%-+10.5d", 4242);                  -> "+04242    "
//  ft_printf("%03.2d", 0);                       -> " 00"
//  ft_printf("%03.2d", 1);                       -> " 01"
//  ft_printf("%03.2d", -1);                      -> "-01"
//  ft_printf("@moulitest: %.10d", -42);          -> "@moulitest: -0000000042"
//  ft_printf("@moulitest: %.d %.0d", 42, 43);    -> "@moulitest: 42 43"
//  ft_printf("@moulitest: %.d %.0d", 0, 0);      -> "@moulitest:  "
//  ft_printf("@moulitest: %5.d %5.0d", 0, 0);    -> "@moulitest:            "
//  ft_printf("%u", 0);                           -> "0"
//  ft_printf("%u", 1);                           -> "1"
//  ft_printf("%u", -1);                          -> "4294967295"
//  ft_printf("%u", 4294967295);                  -> "4294967295"
//  ft_printf("%u", 4294967296);                  -> "0"
//  ft_printf("%5u", 4294967295);                 -> "4294967295"
//  ft_printf("%15u", 4294967295);                -> "     4294967295"
//  ft_printf("%-15u", 4294967295);               -> "4294967295     "
//  ft_printf("%015u", 4294967295);               -> "000004294967295"
//  ft_printf("% u", 4294967295);                 -> "4294967295"
//  ft_printf("%+u", 4294967295);                 -> "4294967295"
//  ft_printf("%lu", 4294967295);                 -> "4294967295"
//  ft_printf("%lu", 4294967296);                 -> "4294967296"
//  ft_printf("%lu", -42);                        -> "18446744073709551574"
//  ft_printf("%llu", 4999999999);                -> "4999999999"
//  ft_printf("@moulitest: %.5u", 42);            -> "@moulitest: 00042"
	return (0);
}
