

int	ft_streq(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (!str2);
	if (!str2)
		return (0);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (!str2[i]);
}
