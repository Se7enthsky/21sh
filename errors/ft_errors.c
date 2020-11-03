#include "errors.h"

void		ft_errors(void)
{
	static char *errors[] = {
		"Undefined error: 0",
		"No such file or directory",
		"Too many arguments",
		"Permission denied",
		"Not a directory",
		NULL,
	};
	if (g_exit_code > 0 && g_exit_code <= 4)
		ft_putendl_fd(errors[g_exit_code], 2);
}