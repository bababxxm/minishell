#include "minishell.h"

static bool	is_export(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 6))
		return (true);
	return (false);
}

int	errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb)
{
	char	*msg;
	bool	export;

	export = is_export(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd)
	{
		msg = safe_strjoin(msg, cmd);
		msg = safe_strjoin(msg, ": ");
	}
	if (detail)
	{
		if (export)
			msg = safe_strjoin(msg, "`");
		msg = safe_strjoin(msg, detail);
		if (export)
			msg = safe_strjoin(msg, "'");
		msg = safe_strjoin(msg, ": ");
	}
	if (err_msg)
		msg = safe_strjoin(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err_nb);
}
