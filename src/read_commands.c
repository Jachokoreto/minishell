#include "minishell.h"



void	read_commands(t_temp *temp, char *line)
{
	int		i;
	char	**split;

	// while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
	// 	i++;
	split = ft_split(line, ' ');
	i = -1;
	while (++i < 7)
	{
		if (ft_strncmp(split[0], temp->builtins[i], ft_strlen(split[0])) == 0)
		{
				temp->builtin_funcs[i](&split[1]);
		}

	}
	return ;
}
