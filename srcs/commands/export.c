#include "../../minishell.h"

int			check_arg(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '=')
			return (1);
		i++;
	}
	return (0);
}

void		export_command_2(t_struct *conf, t_command *com, int i)
{
	int		j;

	j = 0;
	while (com->args[i][j] && com->args[i][j] != '=')
		j++;
	if (com->args[i][j] != '\0')
	{
		if (export_check_args(conf->env, com->args[i]) == 1)
			conf->env = export_change_env(conf->env, com->args[i]);
		else
			conf->env = export_add_args(conf->env, com->args[i]);
	}
	else
		conf->export = ft_array_realloc(conf->export, com->args[i]);
}

void    export_command(t_command *com, t_struct *conf)
{
	int	i;

	i = 0;
	if (com->args[0] == NULL)
	{
		env_command(com, conf->env);
		while (conf->export[i] != NULL)
		{
			ft_putstr_fd(conf->export[i], 1);
			ft_putstr_fd("=' '\n", 1);
			i++;
		}
	}
	else if ((check_arg(com->args)) == 1)
		error_quit(com->name, conf);
	i = 0;
	while (com->args[i])
		export_command_2(conf, com, i++);
}