/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:34 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/09 17:01:12 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// int	del_key(void *content, char **args)
// {
// 	t_env	*tmp;

// 	tmp = (t_env *)content;
// 	if (ft_strncmp(tmp->key, args[0], ft_strlen(args[0])) == 0)
// 	{
// 		ft_lstdelone(,);
// 		return (1);
// 	}
// 	return (0);
// }

void	unset(char **args)
{
	t_env	*tmp;
	t_list	*curnode;
	t_list	*prevnode;
	int		i;

	i = 0;
	while (args[++i])
	{
		curnode = g_data->env_list;
		prevnode = NULL;
		while (curnode)
		{
			tmp = (t_env *)curnode->content;
			if (ft_strncmp(tmp->key, args[i], ft_strlen(args[0])) == 0)
			{
				if (prevnode == NULL)
					g_data->env_list = curnode->next;
				else
					prevnode->next = curnode->next;
				ft_lstdelone(curnode, free);
				break ;
			}
			prevnode = curnode;
			curnode = curnode->next;
		}
	}
}
