/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/03/28 14:04:48 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(char *str, enum e_Type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(str);
	ft_lstadd_back(&g_data->tokens, ft_lstnew(token));
	return (token);
}

void	decide_token_type(char *str)
{
	static t_token	*prev_token;

	if (g_data->tokens == NULL)
		prev_token = NULL;
	if (str[0] == '|')
		prev_token = add_new_token(str, pip);
	else if (ft_strncmp(str, ">>", 2) == 1
		|| str[0] == '>' || str[0] == '<')
		prev_token = add_new_token(str, redir);
	else if (prev_token == NULL || (prev_token && prev_token->type == pip))
		prev_token = add_new_token(str, cmd);
	else if (prev_token->type == redir)
		prev_token = add_new_token(str, file);
	else
		prev_token = add_new_token(str, arg);
}



char	*expand_env_var(char *buf)
{
	char	*tmp[4];

	while (buf)
	{
		tmp[3] = ft_strchr(buf, '$');
		if (tmp[3] == NULL || tmp[3])
			break ;
		tmp[1] = ft_substr(buf, 0, tmp[3] - buf);
		buf = tmp[3] + 1;
		while (ft_isalnum(*buf) == 1 || *buf == '_')
			buf++;
		tmp[0] = ft_substr(tmp[3], 0, buf - tmp[3]);
		tmp[2] = ft_strdup(buf);
		free(buf);
		buf = ft_strjoin(tmp[1], mini_getenv(tmp[0]));
		free(tmp[0]);
		tmp[0] = buf;
		buf = ft_strjoin(buf, tmp[2]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp[2]);
	}
	return (buf);
}

	// while (ft_isalnum(line[i]) == 1)
	// 	i++;
	// if (line[i] == '\"' || line[i] == '\'')
	// {
	// 	quote = line[i++];
	// 	while (line[i] && line[i] != quote)
	// 		i++;
	// 	return (++i);
	// }
	// if (line[i] == '<' || line[i] == '>' || line[i] == '|')
	// 	i++;
	// if (line[i] == '<' || line[i] == '>')
	// 	return (++i);
	// while (ft_isalnum(line[i]) == 1)
	// 	i++;
	// return (i);


char	*get_string_into_buffer(char **line)
{
	char	*index;
	char	*buffer;
	char	*quote[2];

	index = *line;
	while (*index && *index != ' ')
	{
		if (*index == '\"' || *index == '\'')
		{
			quote[0] = index;
			quote[1] = ft_strchr(quote[0], *quote[0]);
			if (quote[1] == NULL)
				return (NULL);
			index = quote[1];
		}
		else if (*index == '<' || *index == '>' || *index == '|')
			break ;
		index++;
	}
	buffer = ft_substr(*line, 0, index - *line);
	*line = index;
	printf("%s\n", buffer);
	return (buffer);
}
 
void	mini_lexer(char *line)
{
	int		i;
	char	*buffer;

	i = 0;
	g_data->tokens = NULL;
	buffer = NULL;
	while (*line)
	{
		while (*line == ' ')
			line++;
		buffer = get_string_into_buffer(&line);
		printf("buff : %s\n", buffer);
		decide_token_type(buffer);
		free(buffer);
	}
}

