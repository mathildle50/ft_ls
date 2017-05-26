/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:48:27 by mallard           #+#    #+#             */
/*   Updated: 2017/05/22 10:58:31 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	check_option(char *str, char *option)
{
	int				i;
	int				j;

	j = 0;
	i = 1;
	while (str[i] != '\0' && option[j] != '\0')
	{
		if (str[i] == option[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	if (option[j] == '\0' && str[i] != '\0')
		error_option(str[i]);
}

char	**check_file(char **tab)
{
	int				i;
	struct stat		buf;
	char			**tmp;

	i = -1;
	if (!(tmp = newtab(1)))
		return (0);
	tmp[0] = NULL;
	while (tab[++i] != NULL)
	{
		lstat(tab[i], &buf);
		if (errno == ENOENT)
			error_comp(tab[i], tab, &i);
		else if (S_ISDIR(buf.st_mode) == 0)
		{
			if (tmp[0] == NULL)
				tmp[0] = ft_strdup(tab[i]);
			else
				tmp = add_str_to_tab(tmp, tab[i]);
			char_del(tab, i--);
		}
	}
	return (tmp);
}
