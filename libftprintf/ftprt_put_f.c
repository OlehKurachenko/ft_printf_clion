#include "ft_printf.h"

static const long long		e_type_deft_precision = 6;
static const long double	e_type_base = 10l;

static size_t 				count_length(t_printff *const fl, long double val)
{
	size_t	res;
	size_t	i_res;

	if (val != val || val == flt_pos_inf || val == flt_neg_inf)
		return (0);
	fl->flags[6] = (unsigned char)(val < 0);
	val = (val < 0) ? -val : val;
	res = 1;
	if (fl->precision == -1)
		fl->precision = e_type_deft_precision;
	if (val < 0 || fl->flags[3] || fl->flags[5])
		++res;
	if (fl->precision || fl->flags[0])
		++res;
	val /= e_type_base;
	i_res = 0;
	if (val == val && val != flt_neg_inf && val != flt_pos_inf)
		while (val >= e_type_base)
		{
			val /= e_type_base;
			++i_res;
		}
	res += (fl->flags[4]) ? i_res + (i_res - 1) / 3 : i_res;
	return (res + fl->precision);
}

void						ftprt_put_f(t_printff *fl, va_list *arg,
	int *nptr, t_putchar f_putchar)
{
	const long double	val = ftprt_va_get_fvalue(fl, arg);
	const size_t 		len = count_length(fl, val);

	if (ftprt_handle_nans(fl, val, nptr, f_putchar))
		return ;
	if (fl->flags[6])
		f_putchar('-');
	else
		if (fl->flags[3] || fl->flags[5])
			f_putchar((char)((fl->flags[3]) ? ' ' : '+'));
	if (len < fl->width && (!fl->flags[2]))
		ftprt_putnchar((char)((fl->flags[1]) ? '0' : ' '),
					   fl->width - len, f_putchar);
	// TODO write
	// TODO remember about apo
	//ftprt_put_float_base(n_form, e_type_base, fl, f_putchar);
	if (len < fl->width && fl->flags[2])
		ftprt_putnchar(' ', fl->width - len, f_putchar);
	;
	*nptr += ft_max_size_t(fl->width, len);
}