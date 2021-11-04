/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizz <luizz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:51:33 by llima-ce          #+#    #+#             */
/*   Updated: 2021/11/04 17:05:02 by luizz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_formated(t_format *buffer, char *formated)
{
	int		a;

	a = 0;
	while (a < buffer->len)
	{
		write(1, &formated[a], 1);
		a++;
	}
	free(formated);
	return(ft_end_struct(buffer));
}

int			ft_printf(const char *format, ...)
{
	t_format	*buffer;
	va_list		args;
	char		*formated;
	int			len;

	if (format == NULL)
		return (0);
	va_start(args, format);
	buffer = ft_start_struct(args);
	formated = ft_vfprintf(format, buffer);
	len = put_formated(buffer, formated);
	va_end(args);
	return (len);
}


static char	*ft_merge(char *all, t_format *buffer ,int *pt_start, int pt_end)
{
	char	*new;
	int		len_all;

	if (all == NULL || *pt_start < 0)
		return (all);
	len_all = buffer->len_all - pt_end + buffer->len + 1;
	new = malloc(len_all * sizeof(char));
	new[len_all - 1] = 0;
	if (new == NULL)
		return (all);
	ft_memcpy(new, all, *pt_start + 1);
	ft_strlcpy(new + *pt_start, buffer->formated_src, buffer->len + 1);
	ft_strlcpy(new + *pt_start + buffer->len, all + *pt_start + pt_end,
		len_all + 1);
	free(all);
	all = NULL;
	*pt_start += buffer->len;
	buffer->len_all = len_all - 1;
	return (new);
}

char	*ft_vfprintf(const char *format, t_format *buffer)
{
	char	*format_tmp;
	int		end_format;
	int		a;

	a = 0;
	format_tmp = ft_strdup(format);
	buffer->len_all = ft_strlen(format_tmp);
	while (format_tmp[a] != 0)
	{
		if (format_tmp[a] == '%')
		{
			end_format = ft_check_all((char *)&format_tmp[a + 1], buffer) + 1;
			if (buffer->formated_src != NULL)
				format_tmp = ft_merge(format_tmp, buffer,&a, end_format);
			ft_reset_struct(buffer);
		}
		else
			a++;
	}
	buffer->len = a;
	return (format_tmp);
}
