#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <unistd.h>
#include <stdint.h>
#include <wchar.h>

int len_digit(t_flag *flag, int count);
int len_str(t_flag *flag, int count);

int print_base(intmax_t num, int base, t_flag *flag)
{
	int n = 1;
	char c = 'a';
	if (num / base > 0)
		n += print_base(num / base, base, flag);
	if (flag->flag != NULL && (flag->flag[0] == 'X' || flag->flag[1] == 'X' || flag->flag[2] == 'X'))
		c = 'A';
	num =  num % base;
	num += (num > 9 ? c - 10 : '0');
	write (1, &num, 1);
	return (n);
}

// void print_point(t_flag *flag)
// {
// 	while (flag->point-- > 0)
// 			write (1, "0", 1);
// }

int ft_putnbr(intmax_t num, int base, t_flag *flag)
{
	int n = 1;
	if (num / 10 > 0)
		n += ft_putnbr(num / 10, base, flag);
	num %= 10;
	num += '0';
	write(1, &num, 1);
	return (n);
}

//выводит число
int print_num(intmax_t num, t_flag *flag, int fun(intmax_t, int, t_flag*), int base)
{
	if (num == 0 && flag->point == 0)
		return (0);
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
	else if (flag->plus == ' ' && flag->width <= 0)
		write(1, " ", len += 1);
	flag->plus = '\0';
	// print_point(flag);
	int x = flag->point;
	while (x-- > 0)
			write (1, "0", 1);
	len += fun(num, base, flag);
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
	if (num == 0)
		return (1);
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
		if ((*flag)->plus != '+')
			(*flag)->plus = ' ';
		while (**str == ' ')
			(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		if (**str == '*')
		{
			(*flag)->point = va_arg(*ap, int);
			(*str)++;
		}
		else
			(*flag)->point = get_digit(str);
	}
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
		while (**str == '+')
			(*str)++;
	}
}

void plus(char **str, t_flag **flag)
{
	if (**str == '+')
	{
		(*flag)->plus = '+';
		while (**str == '+')
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

int flag_c(char ap, t_flag **flag)
{
	int count = 0;
	// if (ap != NULL)
		count = 1;
	// else
	// 	write(1, "(null)", 6);
	if ((*flag)->point != -1)
	{
		(*flag)->point - count > 0 ? 0 : (count = (*flag)->point);
	}
	(*flag)->width -= count;
	int x = (*flag)->width;
	if ((*flag)->position == '-')
	{
		write(1, &ap, 1);
		while (x-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		write(1, &ap, count);
	}
	return (len_str(*flag, count));
}
int flag_s(char *ap, t_flag **flag)
{
	int count = 0;
	if (ap != NULL)
		count = ft_strlen(ap);
	else
		write(1, "(null)", (count = 6));
	if ((*flag)->point != -1)
	{
		(*flag)->point - count > 0 ? 0 : (count = (*flag)->point);
	}
	(*flag)->width -= count;
	int x = (*flag)->width;
	if (ap != NULL && *ap == '%')
		count = 1;
	if ((*flag)->position == '-')
	{
		write(1, ap, count);
		while (x-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		write(1, ap, count);
	}
	return (len_str(*flag, count));
}

//вывод флага d
/* для остальных флагов нужны почти теже действия
* меняется только тип данных для счетчика и выводимого значения
* хотелось бы передовать адрес функции в функцию в зависимости от
* флагов, если это имеет смысл
*/
// int flag_d(va_list *ap, t_flag **flag)

int len_str(t_flag *flag, int count)
{
	int len = 0;
	if (flag->width > 0)
		len += flag->width;
	if (flag->point == count)
		len += count;
	else
		len += count;
	return (len);
}

int len_digit(t_flag *flag, int count)
{
	int len = 0;
	if (flag->width > 0)
		len += flag->width;
	if (flag->point > 0)
		len += flag->point;
	len += count;
	return (len);
}

int print_position(intmax_t num, t_flag **flag, int fun(intmax_t, int, t_flag*), int base)
{
	int len = 0;
	if ((*flag)->octothorp == '#' && base == 16 && num != 0)
	{
		(*flag)->width -= 2;
		if ((*flag)->point == -1 && (*flag)->kind_width == '0')
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

int check_zero(int *count, intmax_t num, t_flag **flag)
{
	if (num == 0 && (*flag)->point == 0)
		*count = 0;
	if ((*count != 0 && num == 0 && (*flag)->octothorp == '#') || (num == 0 &&(*flag)->octothorp == '#' && (*flag)->flag != NULL &&
	(((*flag)->flag[0] == 'o' || (*flag)->flag[1] == 'o' || (*flag)->flag[2] == 'o'))))
	{
		write(1, "0", 1);
		return (0);
	}
	return (1);
}

void calc_position(t_flag **flag, int count, int base, intmax_t num)
{
	if ((*flag)->point != -1 || (*flag)->position != '\0')
	{
		(*flag)->kind_width = ' ';
		(*flag)->point - count > 0 ? (*flag)->width -= ((*flag)->point - count) : 0;
		(*flag)->point = (*flag)->point - count;
	}
	(*flag)->width -= count;
	if (((num < 0 || (*flag)->plus == '+' ) && base == 10) || ((*flag)->octothorp == '#' && base == 8))
	{
		(*flag)->width -= 1;
		if ((*flag)->point == -1 && (*flag)->kind_width == '0')
		{
			(*flag)->point = (*flag)->width;
			(*flag)->width = 0;
		}
	}
}

int flag_d(intmax_t num, t_flag **flag, int fun(intmax_t, int, t_flag*), int base)
{
	// int len = 0;
	int count = 0;
	if ((*flag)->flag != NULL && ((*flag)->flag[0] == 'u' || (*flag)->flag[1] == 'u' || (*flag)->flag[2] == 'u'))
		(*flag)->plus = '\0';
	if (num == -9223372036854775807 - 1)
	{
		write (1, "-9223372036854775808", 20);
		return (20);
	}
	count = num_count(num);
	if (check_zero(&count, num, flag) == 0)
		return (1);
	calc_position(flag, count, base, num);
	count = print_position(num, flag, fun, base);
	// count > len ? (count = len) : 0;
	// count < len ? (count += len) : 0;
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
	(*node)->point = -1;
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
	if ((*flag)->point == -1)
		point(str, flag, ap);
	//   d, i           o, u, x, X
	// if ((n = check_flag(*str)))
	// 	while (n-- > 0)
	// 		(*flag)->flag[i++] = (*((*str)++));
}

void move_flag(char **str, int n)
{
	while (n-- > 0)
		(*str)++;
			// (*flag)->flag[i++] = (*((*str)++));
}

int diu_flags(va_list *ap, t_flag **flag, char **str)
{
	int n = 0;
	int pc = 0;
	if (**str == 'd' || **str == 'i')
		pc = flag_d((int)va_arg(*ap, int), flag, &ft_putnbr, 10);
	else if (**str == (*((*flag)->flag = "u\0\0")))
		pc = flag_d((unsigned int)va_arg(*ap, unsigned int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "ld", (n = 1)) || !ft_strncmp(*str, "li", (n = 1)))
		pc = flag_d((long)va_arg(*ap, long int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, ((*flag)->flag = "lu\0"), (n = 1)))
		pc = flag_d((unsigned long int)va_arg(*ap, unsigned long int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, ((*flag)->flag = "llu"), (n = 2)))
		pc = flag_d((unsigned long long int)va_arg(*ap, unsigned long long int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "lld", (n = 2)) || !ft_strncmp(*str, "lli", (n = 2)))
		pc = flag_d((long long)va_arg(*ap, long long int), flag, &ft_putnbr, 10);
	else
		return (0);
	move_flag(str, (n += 1));
	return (pc);
}

int oxX_flags(va_list *ap, t_flag **flag, char **str)
{
	int n = 0;
	int pc = 0;
	if (**str == (*((*flag)->flag = "o\0\0")))
		pc = flag_d((unsigned int)va_arg(*ap, unsigned int), flag, &print_base, 8);
	else if (**str == (*((*flag)->flag = "x\0\0")) || **str == (*((*flag)->flag = "X\0\0")))
		pc = flag_d((unsigned int)va_arg(*ap, unsigned int), flag, &print_base, 16);
	else if (!ft_strncmp(*str, ((*flag)->flag = "lo\0"), (n = 1)))
		pc = flag_d((unsigned long int)va_arg(*ap, unsigned long int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, ((*flag)->flag = "llo"), (n = 2)))
		pc = flag_d((unsigned long long int)va_arg(*ap, unsigned long long int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, ((*flag)->flag = "lx\0"), (n = 1)) || !ft_strncmp(*str, ((*flag)->flag = "lX\0"), (n = 1)))
		pc = flag_d((unsigned long)va_arg(*ap, unsigned long int), flag, &print_base, 16);
	else if (!ft_strncmp(*str, ((*flag)->flag = "llx"), (n = 2)) || !ft_strncmp(*str, ((*flag)->flag = "llX"), (n = 2)))
		pc = flag_d((unsigned long long)va_arg(*ap, unsigned long long int), flag, &print_base, 16);
	else
		return (0);
	move_flag(str, (n += 1));
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
	move_flag(str, (n += 1));
	return (pc);
}

int easy_flag(va_list *ap, t_flag **flag, char **str)
{
	int len = 0;
	if (**str == '%')
		len += flag_s("%", flag);
	else if (**str == 's')
		len += flag_s(va_arg(*ap, char*), flag);
	else if (**str == 'c')
		len += flag_c((char)va_arg(*ap, int), flag);
	else
		return (0);
	move_flag(str, 1);
	return (len);
}

void check_flag(char **str, va_list *ap, t_flag **flag, int *len)
{
	int l = 0;
	while (l == 0 && **str != '\0')
	{
		if ((l = easy_flag(ap, flag, str)))
			*len += l;
		else if ((l = diu_flags(ap, flag, str)))
			*len += l;
		else if ((l = oxX_flags(ap, flag, str)))
			*len += l;
		else if ((l = hh_flags(ap, flag, str)))
			*len += l;
		else if (**str != '\0')
			move_flag(str, 1);
	}
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
		check_flag(&str, ap, flag, &len);
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
	ft_printf("%lu", -42);
// 	FAILED TESTS:\n
// # TEST NUMBER (TYPE OF ARG)
//   INSTRUCTION();
//   1. your function ft_printf
//   2. unix function printf
//      (returned value) -->written on stdout<--

// # 0003
  ft_printf("% h\n");
//   1. (    1) -->h<--
//   2. (    0) --><--

// # 0005
  ft_printf("% hZ\n");
//   1. (    2) -->hZ<--
//   2. (    1) -->Z<--

// # 0006
  int x = ft_printf("%05%\n");
  ft_printf("%d", x);
//   1. (    1) -->0000%<--
//   2. (    5) -->0000%<--

// # 0007
  ft_printf("%-05%\n");
//   1. (    1) -->%    <--
//   2. (    5) -->%    <--

// # 0008
  ft_printf("% hZ%\n");
//   1. (    2) -->hZ<--
//   2. (    1) -->Z<--

// # 0011 (char *)
  ft_printf("% Z%s\n", "test");
//   1. (    2) -->Ztest<--
//   2. (    5) -->Ztest<--

// # 0015 (int)
  ft_printf("%jx\n", 4294967295);
//   1. (    2) -->jx<--
//   2. (    8) -->ffffffff<--

// # 0016 (int)
  ft_printf("%jx\n", 4294967296);
//   1. (    2) -->jx<--
//   2. (    9) -->100000000<--

// # 0017 (int)
  ft_printf("%jx\n", -4294967296);
//   1. (    2) -->jx<--
//   2. (   16) -->ffffffff00000000<--

// # 0018 (int)
  ft_printf("%jx\n", -4294967297);
//   1. (    2) -->jx<--
//   2. (   16) -->fffffffeffffffff<--

// # 0019 (int)
  ft_printf("%ll#x\n", 9223372036854775807);
//   1. (    4) -->ll#x<--
//   2. (   18) -->0x7fffffffffffffff<--

// # 0020 (char *)
  ft_printf("%010s is a string", "this\n");
//   1. (   13) -->000000this is a string<--
//   2. (   22) -->000000this is a string<--

// # 0021 (char *)
  ft_printf("%-010s is a string\n", "this");
//   1. (   13) -->this       is a string<--
//   2. (   22) -->this       is a string<--

// # 0022 (char)
  ft_printf("%05c\n", 42);
//   1. (    1) -->c<--
//   2. (    5) -->0000*<--

// # 0024 (int)
  ft_printf("%0 d", 42);
//   1. (    1) --> 42<--
//   2. (    3) --> 42<--

// # 0025 (int)
  ft_printf("%0 d", -42);
//   1. (   -2) -->-42<--
//   2. (    3) -->-42<--

// # 0026 (int)
  ft_printf("% 0d", 42);
//   1. (    1) --> 42<--
//   2. (    3) --> 42<--

// # 0027 (int)
  ft_printf("% 0d", -42);
//   1. (    1) -->-42<--
//   2. (    3) -->-42<--

// # 0028 (int)
  ft_printf("%5+d", 42);
//   1. (    1) -->  +42<--
//   2. (    5) -->  +42<--

// # 0029 (int)
  ft_printf("%5+d", -42);
//   1. (    1) -->  -42<--
//   2. (    5) -->  -42<--

// # 0030 (int)
  ft_printf("%-5+d", 42);
//   1. (   -1) -->+42  <--
//   2. (    5) -->+42  <--

// # 0031 (int)
  ft_printf("%-0+5d", 42);
//   1. (   -1) -->+42  <--
//   2. (    5) -->+42  <--

// # 0032 (int)
  ft_printf("%-5+d", -42);
//   1. (   -1) -->-42  <--
//   2. (    5) -->-42  <--

// # 0033 (int)
  ft_printf("%-0+5d", -42);
//   1. (   -1) -->-42  <--
//   2. (    5) -->-42  <--

// # 0034 (intmax_t)
  ft_printf("%jd", 9223372036854775807);
//   1. (    2) -->jd<--
//   2. (   19) -->9223372036854775807<--

// # 0035 (intmax_t)
  ft_printf("%jd", -9223372036854775808);
//   1. (    2) -->jd<--
//   2. (   20) -->-9223372036854775808<--

// # 0036 (ssize_t)
  ft_printf("%zd", 4294967295);
//   1. (    2) -->zd<--
//   2. (   10) -->4294967295<--

// # 0037 (ssize_t)
  ft_printf("%zd", 4294967296);
//   1. (    2) -->zd<--
//   2. (   10) -->4294967296<--

// # 0038 (ssize_t)
  ft_printf("%zd", -0);
//   1. (    2) -->zd<--
//   2. (    1) -->0<--

// # 0039 (ssize_t)
  ft_printf("%zd", -1);
//   1. (    2) -->zd<--
//   2. (    2) -->-1<--

// # 0040 (intmax_t)
  ft_printf("%ju", 4999999999);
//   1. (    2) -->ju<--
//   2. (   10) -->4999999999<--

// # 0041 (size_t)
  ft_printf("%ju", 4294967296);
//   1. (    2) -->ju<--
//   2. (   10) -->4294967296<--

// # 0042 (unsigned long)
  ft_printf("%U", 4294967295);
//   1. (    1) -->U<--
//   2. (   10) -->4294967295<--

// # 0043 (unsigned long)
  ft_printf("%hU", 4294967296);
//   1. (    2) -->hU<--
//   2. (   10) -->4294967296<--

// # 0044 (unsigned long)
  ft_printf("%U", 4294967296);
//   1. (    1) -->U<--
//   2. (   10) -->4294967296<--

// # 0045 (size_t)
  ft_printf("%zhd", 4294967296);
//   1. (    3) -->zhd<--
//   2. (   10) -->4294967296<--

// # 0046 (unsigned long long)
  ft_printf("%jzd", 9223372036854775807);
//   1. (    3) -->jzd<--
//   2. (   19) -->9223372036854775807<--

// # 0047 (unsigned long long)
  ft_printf("%jhd", 9223372036854775807);
//   1. (    3) -->jhd<--
//   2. (   19) -->9223372036854775807<--

// # 0048 (unsigned long long)
  ft_printf("%lhl", 9223372036854775807);
//   1. (    3) -->lhl<--
//   2. (    0) --><--

// # 0049 (unsigned long long)
  ft_printf("%lhlz", 9223372036854775807);
//   1. (    4) -->lhlz<--
//   2. (    0) --><--

// # 0050 (unsigned long long)
  ft_printf("%zj", 9223372036854775807);
//   1. (    2) -->zj<--
//   2. (    0) --><--

// # 0051 (unsigned long)
  ft_printf("%lhh", 2147483647);
//   1. (    3) -->lhh<--
//   2. (    0) --><--

// # 0052 (unsigned long)
  ft_printf("%hhld", 128);
//   1. (    4) -->hhld<--
//   2. (    3) -->128<--

// # 0053 (int)
  ft_printf("@main_ftprintf: %####0000 33..1..#00d\\n", 256);
//   1. (   37) -->@main_ftprintf: ###0000 33..1..#00d\\n<--
//   2. (   51) -->@main_ftprintf:                               256\\n<--

// # 0054 (int)
  ft_printf("@main_ftprintf: %####0000 33..1d", 256);
//   1. (   30) -->@main_ftprintf: ###0000 33..1d<--
//   2. (   49) -->@main_ftprintf:                               256<--

// # 0055 (int)
  ft_printf("@main_ftprintf: %###-#0000 33...12..#0+0d", 256);
//   1. (   39) -->@main_ftprintf: ##-#0000 33...12..#0+0d<--
//   2. (   49) -->@main_ftprintf: +256                             <--
// \n--------------\n
// SUCCESS TESTS:\n
//    1.      ft_printf("%");                               -> ""
//    2.      ft_printf("% ");                              -> ""
//    3. FAIL ft_printf("% h");                             -> ""
//    4.      ft_printf("%Z");                              -> "Z"
//    5. FAIL ft_printf("% hZ");                            -> "Z"
//    6. FAIL ft_printf("%05%");                            -> "0000%"
//    7. FAIL ft_printf("%-05%");                           -> "%    "
//    8. FAIL ft_printf("% hZ%");                           -> "Z"
//    9.      ft_printf("% Z", "test");                     -> "Z"
//   10.      ft_printf("% Z ", "test");                    -> "Z "
//   11. FAIL ft_printf("% Z%s", "test");                   -> "Ztest"
//   12.      ft_printf("%000   %", "test");                -> "%"
//   13.      ft_printf("%%%", "test");                     -> "%"
//   14.      ft_printf("%%   %", "test");                  -> "%   "
//   15. FAIL ft_printf("%jx", 4294967295);                 -> "ffffffff"
//   16. FAIL ft_printf("%jx", 4294967296);                 -> "100000000"
//   17. FAIL ft_printf("%jx", -4294967296);                -> "ffffffff00000000"
//   18. FAIL ft_printf("%jx", -4294967297);                -> "fffffffeffffffff"
//   19. FAIL ft_printf("%ll#x", 9223372036854775807);      -> "0x7fffffffffffffff"
//   20. FAIL ft_printf("%010s is a string", "this");       -> "000000this is a string"
//   21. FAIL ft_printf("%-010s is a string", "this");      -> "this       is a string"
//   22. FAIL ft_printf("%05c", 42);                        -> "0000*"
//   23.      ft_printf("% Z", 42);                         -> "Z"
//   24. FAIL ft_printf("%0 d", 42);                        -> " 42"
//   25. FAIL ft_printf("%0 d", -42);                       -> "-42"
//   26. FAIL ft_printf("% 0d", 42);                        -> " 42"
//   27. FAIL ft_printf("% 0d", -42);                       -> "-42"
//   28. FAIL ft_printf("%5+d", 42);                        -> "  +42"
//   29. FAIL ft_printf("%5+d", -42);                       -> "  -42"
//   30. FAIL ft_printf("%-5+d", 42);                       -> "+42  "
//   31. FAIL ft_printf("%-0+5d", 42);                      -> "+42  "
//   32. FAIL ft_printf("%-5+d", -42);                      -> "-42  "
//   33. FAIL ft_printf("%-0+5d", -42);                     -> "-42  "
//   34. FAIL ft_printf("%jd", 9223372036854775807);        -> "9223372036854775807"
//   35. FAIL ft_printf("%jd", -9223372036854775808);       -> "-9223372036854775808"
//   36. FAIL ft_printf("%zd", 4294967295);                 -> "4294967295"
//   37. FAIL ft_printf("%zd", 4294967296);                 -> "4294967296"
//   38. FAIL ft_printf("%zd", -0);                         -> "0"
//   39. FAIL ft_printf("%zd", -1);                         -> "-1"
//   40. FAIL ft_printf("%ju", 4999999999);                 -> "4999999999"
//   41. FAIL ft_printf("%ju", 4294967296);                 -> "4294967296"
//   42. FAIL ft_printf("%U", 4294967295);                  -> "4294967295"
//   43. FAIL ft_printf("%hU", 4294967296);                 -> "4294967296"
//   44. FAIL ft_printf("%U", 4294967296);                  -> "4294967296"
//   45. FAIL ft_printf("%zhd", 4294967296);                -> "4294967296"
//   46. FAIL ft_printf("%jzd", 9223372036854775807);       -> "9223372036854775807"
//   47. FAIL ft_printf("%jhd", 9223372036854775807);       -> "9223372036854775807"
//   48. FAIL ft_printf("%lhl", 9223372036854775807);       -> ""
//   49. FAIL ft_printf("%lhlz", 9223372036854775807);      -> ""
//   50. FAIL ft_printf("%zj", 9223372036854775807);        -> ""
//   51. FAIL ft_printf("%lhh", 2147483647);                -> ""
//   52. FAIL ft_printf("%hhld", 128);                      -> "128"
//   53. FAIL ft_printf("@main_ftprintf: %####0000 33..1..#00d\\n", 256); -> "@main_ftprintf:                               256\\n"
//   54. FAIL ft_printf("@main_ftprintf: %####0000 33..1d", 256); -> "@main_ftprintf:                               256"
//   55. FAIL ft_printf("@main_ftprintf: %###-#0000 33...12..#0+0d", 256); -> "@main_ftprintf: +256                             "
	return(0);
}
