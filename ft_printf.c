/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:24:28 by dpark             #+#    #+#             */
/*   Updated: 2022/06/10 21:24:29 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

void	ft_putchar_fd(char c, int fd, int *len)
{
	write(fd, &c, 1);
	*len = *len + 1;
	return ;
}

void	ft_putnbr_fd(int n, int fd, int *len)
{	
	char	c;

	if (n == -2147483648)
	{
		ft_putnbr_fd(n / 10, fd, len);
		ft_putnbr_fd(8, 1, len);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', 1, len);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd, len);
	c = '0' + (n % 10);
	ft_putchar_fd(c, 1, len);
}

void	find_type(va_list ap, const char *str, int *len)
{
	unsigned int	i;

    if (*str == 'i' || *str == 'd')
    {
        i = va_arg(ap, int);
        ft_putnbr_fd(i, 1, len);
    }
}


int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	ap;

	len = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			find_type(ap, str, &len);
			if (len < 0)
				return (-1);
		}
		else
			ft_putchar_fd(*str, 1, &len);
		str++;
	}
	va_end(ap);
	return (len);
}
