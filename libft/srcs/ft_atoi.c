/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:29 by leo               #+#    #+#             */
/*   Updated: 2024/03/02 14:26:32 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	return (ret * sign);
}

int	ft_pow(int n, int exp)
{
	int	r;

	r = n;
	while (exp-- > 1)
		r *= n;
	return (r);
}

double	ft_atof(const char *nptr)
{
	double	ret;
	int		sign;
	int		count;

	ret = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' && nptr++)
		sign = -1;
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
		ret = ret * 10 + *nptr++ - '0';
	if (*nptr++ != '.')
		return (ret * sign);
	count = 1;
	while (ft_isdigit(*nptr))
		ret += (*nptr++ - '0') / (double)ft_pow(10, count++);
	return (ret * sign);
}
