#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

#define test_int(ret, expected) printf("%d: %s\n", ++i, (res += !(ret == expected))? "FAIL" : "OK!")

int	keyeq(char *key, char *envstr);

int	main(void)
{
	int		res = 0;
	int		i = 0;
	t_env	env;

	test_int(keyeq("TEST", "TEST="), 4);
	test_int(keyeq("TES", "TEST="), 0);
	test_int(keyeq("TEST", "TESTE="), 0);
	test_int(keyeq("TEST", "TEST=YES"), 4);
	test_int(keyeq("TES", "TEST=YES"), 0);
	test_int(keyeq("TEST", "TESTE=YES"), 0);

	init_env(&env);
	test_int(env.tab, 0);
	test_int(env.elem_size, 8);
	test_int(env.len, 0);
	test_int(env.msize, 0);

	char	str[] = "TEST=OUI";
	if (add_vector(&env, str)) // 1 leak
		exit(1);
	test_int(ft_streq(get_env_value(&env, "TEST"), "OUI"), 1); // 1 leak
	test_int(ft_streq(get_env_value(&env, "TEST2"), NULL), 1);
	test_int(ft_streq(get_env_value(&env, "TEST3"), NULL), 1);

	if (add_to_env(&env, "TEST2", "NON")) // 2 mallocs + 1 free = 1 leak
		exit(1);
	test_int(ft_streq(get_env_value(&env, "TEST"), "OUI"), 1); // 1 leak
	test_int(ft_streq(get_env_value(&env, "TEST2"), "NON"), 1); // 1 leak
	test_int(ft_streq(get_env_value(&env, "TEST3"), NULL), 1);

	printf("%s\n", !res ? "Everythings is OK!" : "FAIL :{");
}
