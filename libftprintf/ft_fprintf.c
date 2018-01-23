#include "ft_printf.h"
#include "ftprt_buffered_putchar_fd.h"

int					ft_fprintf(const int fd, const char *format, ...)
{
	va_list                     vl;
	int                         res;

	ftprt_buffer_set_fd(fd);
	va_start(vl, format);
	if (ordered_chech(format))
		res = ft_va_printf_ordered(format, &vl, &ftprt_buffered_putchar_fd);
	else
		res = ft_va_printf(format, &vl, &ftprt_buffered_putchar_fd);
	va_end(vl);
	ftprt_buffer_flush_fd();
	return (res);
}