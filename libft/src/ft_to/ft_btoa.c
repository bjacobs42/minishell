/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:54:45 by bjacobs           #+#    #+#             */
/*   Updated: 2023/04/13 19:56:39 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	ft_baselen(unsigned long long n, int base)
{
	size_t	len;

	len = 1;
	while (n > (unsigned long long)(base - 1))
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_btoa(unsigned long long n, int base)
{
	unsigned long long	rem;
	char				*s;
	size_t				slen;

	slen = ft_baselen(n, base);
	s = (char *)malloc(sizeof(char) * (slen + 1));
	if (!s)
		return (NULL);
	s[slen] = '\0';
	while (slen--)
	{
		rem = n % base;
		if (rem > 9)
			s[slen] = rem + 'a' - 10;
		else
			s[slen] = rem + '0';
		n /= base;
	}
	return (s);
}
