/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprt_put_k.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okurache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 15:50:54 by okurache          #+#    #+#             */
/*   Updated: 2018/01/28 15:50:55 by okurache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static void			put_time(t_printff *const fl, const t_time_t *const time)
{
	fl->ptchr('T');
	ftprt_putnchar(fl, '0', (size_t)(2
		- ftprt_ulen(time->hour, 1, 0)));
	ftprt_put_unumber_smpl(fl, time->hour);
	fl->ptchr(':');
	ftprt_putnchar(fl, '0', (size_t)(2
		- ftprt_ulen(time->minute, 1, 0)));
	ftprt_put_unumber_smpl(fl, time->minute);
	fl->ptchr(':');
	ftprt_putnchar(fl, '0', (size_t)(2
		- ftprt_ulen(time->second, 1, 0)));
	ftprt_put_unumber_smpl(fl, time->second);
	fl->ptchr('Z');
}

void				ftprt_put_k(t_printff *const fl, va_list *const arg)
{
	const t_time_t *const	time = construct_t_time_t_uf(va_arg(*arg, time_t));
	const size_t			len = (fl->flags[0]) ? 10 : 20;

	if (len < fl->width && (!fl->flags[2]))
		ftprt_putnchar(fl, ' ', fl->width - len);
	ftprt_putnchar(fl, '0', (size_t)(4
		- ftprt_ulen(time->year, 1, 0)));
	ftprt_put_unumber_smpl(fl, time->year);
	fl->ptchr('-');
	ftprt_putnchar(fl, '0', (size_t)(2
		- ftprt_ulen(time->month, 1, 0)));
	ftprt_put_unumber_smpl(fl, time->month);
	fl->ptchr('-');
	ftprt_putnchar(fl, '0', (size_t)(2
		- ftprt_ulen(time->day, 1, 0)));
	ftprt_put_unumber_smpl(fl, time->day);
	if (fl->flags[0])
		put_time(fl, time);
	if (len < fl->width && fl->flags[2])
		ftprt_putnchar(fl, ' ', fl->width - len);
	destruct_const_t_time_t(time);
	fl->count += ft_max_size_t(len, fl->width);
}
