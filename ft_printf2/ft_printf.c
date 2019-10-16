#include <stdarg.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <io.h>
#include <stdint.h>

void print_point(t_flag *flag)
{
	while (flag->point-- > 0)
			write (1, "0", 1);
}

//выводит число
void ft_putnbr(intmax_t num, t_flag *flag)
{
	if (num < 0)
	{
		write(1, "-", 1);
		num *= -1;
		flag->plus = '\0';
	}
	else if (flag->plus == '+' && (flag->flag[0] != 'u'
	&& flag->flag[1] != 'u' && flag->flag[2] != 'u'))
	{
		write(1, "+", 1);
		flag->plus = '\0';
	}
	else if (flag->plus == ' ')
		write(1, " ", 1);
	print_point(flag);
	if (num / 10 > 0)
		ft_putnbr(num /10, flag);
	num %= 10;
	num += '0';
	write(1, &num, 1);
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
char *digit(char *str, va_list ap)
{
	int x = va_arg(ap, int);
	// ft_putnbr(x);
	return (str + 2);
}
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
	int num = 0;
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
// сохранение флага ширины и определение чем заполнять ширину 0 или space
void width(char **str, t_flag **flag, va_list *ap)
{
	int num = 0;
	if (**str == '+')
	{
		(*flag)->plus = '+';
		(*str)++;
	}
	if (**str == '0' && *(*str - 1) == '%')
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

int flag_s(va_list *ap, t_flag **flag)
{
	char *str = va_arg(*ap, char*);
	int count = ft_strlen(str);
	if ((*flag)->point != 0)
	{
		(*flag)->point - count > 0 ? 0 : (count = (*flag)->point);
	}
	int x = (*flag)->width - count;
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
	return (1);
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

int flag_d(intmax_t num, t_flag **flag)
{
	// int num = va_arg(*ap, int);
	int count = num_count(num);
	if ((*flag)->point != 0 || (*flag)->position != '\0')
	{
		(*flag)->kind_width = ' ';
		(*flag)->point - count > 0 ? (*flag)->width -= ((*flag)->point - count) : 0;
		(*flag)->point = (*flag)->point - count;
	}
	if (num < 0)
		(*flag)->width -= 1;
	int x = (*flag)->width - count;
	if (((*flag)->position != '\0'))
	{
		ft_putnbr(num, *flag);
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		ft_putnbr(num, *flag);
	}
	return (len_digit(*flag, count));
}
//еще одна
char *ft_strchr(char *str, char c)
{
	char *temp;
	temp = str;
	while (*temp)
	{
		if (*temp == c)
			return (temp);
		temp++;
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
void list_start(t_flag **node)
{
	(*node)->flag[0] = '\0';
	(*node)->flag[1] = '\0';
	(*node)->flag[2] = '\0';
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
void *get_flag(char **str, t_flag **flag, va_list *ap)
{
	int	i;
	int n;

	i = 0;
	n = 0;
	list_start(flag);
	width(str, flag, ap);
	point(str, flag, ap);
	//   d, i           o, u, x, X
	// if ((n = check_flag(*str)))
	// 	while (n-- > 0)
	// 		(*flag)->flag[i++] = (*((*str)++));
}

void save_flag(t_flag **flag, char **str, int n)
{
	int i = 0;
	while (n-- > 0)
			(*flag)->flag[i++] = (*((*str)++));
}

int diu_flags(va_list *ap, t_flag **flag, char **str)
{
	int n = 0;
	int pc = 0;
	if (**str == 'd' || **str == 'i')
		pc = flag_d((int)va_arg(*ap, int), flag);
	else if (**str == 'u')
		pc = flag_d((unsigned int)va_arg(*ap, unsigned int), flag);
	else if (!ft_strncmp(*str, "ld", (n = 1)) || !ft_strncmp(*str, "li", (n = 1)))
		pc = flag_d((long)va_arg(*ap, long int), flag);
	else if (!ft_strncmp(*str, "lu", (n = 1)))
		pc = flag_d((unsigned long int)va_arg(*ap, unsigned long int), flag);
	else if (!ft_strncmp(*str, "llu", (n = 2)))
		pc = flag_d((unsigned long long int)va_arg(*ap, unsigned long long int), flag);
	else if (!ft_strncmp(*str, "lld", (n = 2)) || !ft_strncmp(*str, "lli", (n = 2)))
		pc = flag_d((long long)va_arg(*ap, long long int), flag);
	else
		return (0);
	save_flag(flag, str, (n += 1));
	return (pc);
}

int oxX_flags(va_list *ap, t_flag **flag, char **str)
{
	int n = 0;
	int pc = 0;
	if (**str == 'o')
		pc = flag_d((int)va_arg(*ap, int), flag);
	else if (**str == 'x' || **str == 'X')
		pc = flag_d((int)va_arg(*ap, int), flag);
	else if (!ft_strncmp(*str, "lo", (n = 1)))
		pc = flag_d((long int)va_arg(*ap, long int), flag);
	else if (!ft_strncmp(*str, "llo", (n = 2)))
		pc = flag_d((long long int)va_arg(*ap, long long int), flag);
	else if (!ft_strncmp(*str, "lx", (n = 1)) || !ft_strncmp(*str, "lX", (n = 1)))
		pc = flag_d((long)va_arg(*ap, long int), flag);
	else if (!ft_strncmp(*str, "llx", (n = 2)) || !ft_strncmp(*str, "llX", (n = 2)))
		pc = flag_d((long)va_arg(*ap, long int), flag);
	else
		return (0);
	save_flag(flag, str, (n += 1));
	return (pc);
}

int easy_flag(va_list *ap, t_flag **flag, char **str)
{
	int len = 0;
	if (*str[len] == '%')
	{
		write(1, "%%", 1);
		len++;
	}
	else if ((*flag)->flag[0] == 's')
		flag_s(ap, flag);
	else
		return (0);
	save_flag(flag, str, 1);
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
		str++;
		get_flag(&str, flag, ap);
		len += print_str(start);
		if ((l = easy_flag(ap, flag, &str)))
			len += l;
		else if ((l = diu_flags(ap, flag, &str)))
			len += l;
		else if ((l = oxX_flags(ap, flag, &str)))
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

int main ()
{
	// ft_printf("some text for test %d one more text befor next %%", x);
	// ft_printf("%10d", 54);
	int y = printf("%5d %5% %5.6%\n", 5);
	int x = ft_printf("%5d %5% %5.6%\n", 5);
	printf("printf = %d\n", y);
	ft_printf("ft_printf = %d", x);
	// ft_printf("some text %0-010.1s", "one");
	// ft_printf("some text %*d", 20, 42);

	// printf("\n", 6, 6, 6, 6);
	return (0);
}
