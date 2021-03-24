/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awali-al <awali-al@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:55:09 by mobounya          #+#    #+#             */
/*   Updated: 2020/12/01 11:29:45 by awali-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*cut_varname(char *value)
{
	unsigned int	i;
	char			*var_name;

	i = 0;
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
		i++;
	var_name = ft_strsub(value, 0, i);
	return (var_name);
}

char	*do_stuff(char *value, char *var_value, size_t name_len, size_t len)
{
	char	*part1;
	char	*part2;
	char	*part3;
	char	*temp;
	char	*new_string;

	part1 = ft_strsub(value, 0, len);
	if (var_value == NULL)
		part2 = ft_strdup("");
	else
		part2 = ft_strdup(var_value);
	part3 = ft_strdup(value + len + name_len + 1);
	temp = ft_strjoin(part1, part2);
	new_string = ft_strjoin(temp, part3);
	free(part1);
	free(part2);
	free(part3);
	free(temp);
	return (new_string);
}

char	*ft_replace_variables(char *value, char **env)
{
	char			*new_value;
	unsigned int	i;
	char			*var_name;
	char			*var_value;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			var_name = cut_varname(value + i + 1);
			var_value = ft_getenv(var_name, env);
			new_value = do_stuff(value, var_value, ft_strlen(var_name), i);
			ft_memdel((void**)&var_name);
			ft_memdel((void**)&var_value);
			ft_memdel((void**)&value);
			value = new_value;
			if (var_value)
				i += ft_strlen(var_value);
		}
		else
			i++;
	}
	return (value);
}

char	*ft_replace_home(char *value, char **env)
{
	char	*home_value;
	char	*temp;

	home_value = ft_getenv("HOME", env);
	if (home_value && *home_value)
	{
		temp = ft_strjoin(home_value, value + 1);
		free(home_value);
		return (temp);
	}
	else
		temp = ft_strdup(value + 1);
	return (temp);
}
