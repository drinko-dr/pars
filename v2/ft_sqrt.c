int ft_sqrt(int num)
{
	int		i;

	i = 1;
	if (num <= 0)
		return (0);
	while (i * i < num)
	{
		i++;
	}
	return (i);
}
