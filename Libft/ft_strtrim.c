/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 06:41:53 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/17 14:41:45 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	unsigned int	start;
	unsigned int	end;
	char			*str;
	size_t			len;

	start = 0;
	if (s == NULL)
		return (NULL);
	end = ft_strlen(s) - 1;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	if (start == ft_strlen(s))
		return (ft_strdup(""));
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	len = end - start + 1;
	if ((str = malloc(sizeof(*str) * (len + 1))) == NULL)
		return (NULL);
	str = ft_strsub(s, start, len);
	str[end + 1] = '\0';
	return (str);
}
