/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:35:22 by aderby            #+#    #+#             */
/*   Updated: 2019/09/18 19:01:37 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		identify_line(char *line)
{
	int		i;
	char	*str;

	str = remove_front_spaces(line);
	if (ft_strlen(str) == 0 || str[0] == COMMENT_CHAR)
		return (NULL_FUNCTION);
	if (ft_strnequ(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) ||
			ft_strnequ(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (NAME_COMMENT_FUNCTION);
	i = 0;
	while (str[i] && str[i] != LABEL_CHAR)
	{
		if (ft_strchr(WHITE_SPACE, str[i]))
			break ;
		if (!ft_strchr(LABEL_CHARS, str[i]))
			return (ERROR_FUNCTION);
		i++;
	}
	if (str[i] == LABEL_CHAR)
		return (LABEL_FUNCTION);
	return (INSTRUCTION_FUNCTION);
}

void	parser(int *fd, t_tree **tree, int line_num)
{
	int		function;
	char	*line;
	char	**split;
	char	white_space[9];

	ft_strcpy(white_space, WHITE_SPACE);
	white_space[7] = SEPARATOR_CHAR;
	white_space[8] = '\0';
	while (get_next_line(INPUT, &line))
	{
		line_num++;
		if (ft_strlen(line))
		{
			function = identify_line(line);
			if (function == NAME_COMMENT_FUNCTION)
				split = ft_strsplits(line, COMMENT_DELIMS);
			else
				split = ft_strsplits(line, white_space);
			if (g_parse_function[function])
				g_parse_function[function](tree, split, line_num, fd);
			ft_free_split_string(split);
			split = NULL;
		}
		free(line);
	}
}
