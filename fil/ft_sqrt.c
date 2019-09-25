int ft_sqrt(int num)
{
	int		i;

	i = 1;
	if (num <= 0)
		return (0);
	while (i * i < num)
	{
		i++;
		if (i * i > num)
			return (i - 1);
	}
	return (i);
}
