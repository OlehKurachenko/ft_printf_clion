#include "ft_printf.h"

static void		put_afterpoint_part(long double val, const long double base,
	t_printff *const fl, t_putchar f_putchar)
{
	// TODO correct this?
	const unsigned char	is_capital = (unsigned char)(fl->len_flag == 22);
	size_t				prec;

	if (fl->precision || fl->flags[0])
		f_putchar('.');
	if (!fl->precision)
		return ;
	prec = fl->precision;
	val = (val - (uintmax_t)(val)) * base;
	while (prec > 0)
	{
		f_putchar(ftprt_getupdecimal((unsigned char)(val), is_capital));
		val = (val - (uintmax_t)(val)) * base;
		--prec;
	}
}

static void		put_prepoint_part(long double *const val, const long double base,
	t_printff *const fl, t_putchar f_putchar)
{
	const unsigned char	is_capital = (unsigned char)(fl->len_flag == 22);
	long double			downstep;

	downstep = 1l;
	while (*val / downstep >= base)
		downstep *= base;
	fl->flags[4] = 1;
	while (*val >= 1l || fl->flags[4])
	{
		f_putchar(ftprt_getupdecimal((unsigned char)(*val / downstep),
									  is_capital));
		*val -= (uintmax_t)(*val/downstep);
		downstep /= base;
		fl->flags[4] = 0;
	}
}

/*
**	Here, flag[6] will be used to show that number is < 0
*/

void			ftprt_put_float_base(long double val, const long double base,
	t_printff *const fl, t_putchar f_putchar)
{
	val += 0.5l * ft_ldpow(1l / base, (size_t)fl->precision);
	put_prepoint_part(&val, base, fl, f_putchar);
	put_afterpoint_part(val, base, fl, f_putchar);
}