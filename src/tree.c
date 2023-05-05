#include "minishell.h"

char	*last_operor(char *str, char *small, int len)
{
	int		i;
	int		j;
	int		count;

	i = len - 1;
	if (!small)
		return (str);
	while (i >= 0)
	{
		if (str[i] == ')')
		{
			count = 1;
			while (--i >= 0 && count)
				count += (str[i] == ')') - (str[i] == '(');
			if (count)
				return (NULL);
		}
		j = 0;
		while (str[i + j] && str[i + j] == small[j])
			j++;
		if (!small[j])
			return (str + i);
		i--;
	}
	return (NULL);
}

t_block	*init_left(t_block *input, char *str_block, t_list **garb)
{
	t_block	*left;

	left = my_malloc(sizeof(struct s_block), garb);
	left->start = input->start;
	left->len = (size_t)(str_block - input->start);
	left->left = NULL;
	left->right = NULL;
	return (left);
}

t_block	*init_right(t_block *input, char *str_block, char *op, t_list **garb)
{
	t_block	*right;

	right= my_malloc(sizeof(struct s_block), garb);
	right->start = str_block + ft_strlen(op);
	right->len = input->len - input->left->len - ft_strlen(op);
	right->left = NULL;
	right->right = NULL;
	return (right);
}

void	put_block(t_block block)
{
	int	i;

	i = 0;
	printf("\"");
	while (i < block.len)
	{
		printf("%c", block.start[i]);
		i++;
	}
	printf("\"");
	printf("\n");
}

void	get_blocks(t_block *input, t_list **garb)
{
	char	*str_block;

	str_block = last_operor(input->start, "&&", input->len);
	if (str_block)
	{
		input->op = AND;
		input->left = init_left(input, str_block, garb);
		input->right = init_right(input, str_block, "&&", garb);
		get_blocks(input->left, garb);
		get_blocks(input->right, garb);
		return ;
	}
	str_block = last_operor(input->start, "||", input->len);
	if (str_block)
	{
		input->op = OR;
		input->left = init_left(input, str_block, garb);
		input->right = init_right(input, str_block, "||", garb);
		get_blocks(input->left, garb);
		get_blocks(input->right, garb);
		return ;
	}
	str_block = last_operor(input->start, "|", input->len);
	if(str_block)
	{
		input->op = PP;
		input->left = init_left(input, str_block, garb);
		input->right = init_right(input, str_block, "|", garb);
		get_blocks(input->left, garb);
		get_blocks(input->right, garb);
		return ;
	}
	input->op = NO_OP;
	input->left = NULL;
	input->right = NULL;
	put_block(*input);
}