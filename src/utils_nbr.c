
/// @brief Return the length of an integer
/// @param nbr The integer to get the length
/// @return The length of the integer
int	nbrlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

/// @brief Copy the value of an integer in the string
/// @param s1 The string to copy the integer in
/// @param nbr The integer to copy
/// @param index The index of the string to start the copy
void	cpy_nbr(char *s1, int nbr, int *index)
{
	int	i;

	*index += nbrlen(nbr);
	i = *index - 1;
	if (nbr == 0)
		s1[i] = '0';
	while (nbr)
	{
		s1[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
}
