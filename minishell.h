/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:12:57 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/12 01:41:32 by bbelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include "libft/libft.h"
# include <signal.h>

typedef struct			s_command
{
	char				*name;
	char				**args;
	char				*file_in;
	char				*file_out;
	struct s_command	*next;
	char				**spaces; //нужно для echo пока что
	char				pipe_sc;
}						t_command;

typedef struct			s_struct
{
	char				**env; //массив переменных окружения
	char				**export;
	char				*shell_line; //изначальная строка, которую считали
	int					signal;
	char				*error;
	t_list				*tokens;
	t_command			*command; //текущая команда
	t_command			**command_array; //массив команд (на случай пайплайна) 
}						t_struct;

/*-------------inits-----------------*/

void		init_conf(t_struct *conf);
t_command	*init_command();

/*-------------main----------------*/

void		shell_line(t_struct *conf);

/*-------------utils---------------*/

int			ft_arrlen(char **arr);
char		**ft_array_realloc(char **src, char *line);
void		ft_array_free(char **arr);

/*-------------parser---------------*/

char		**parser_env(char **env);
int			parser_line(char *line, t_struct *conf);
char		**split_tokens(char const *s);
void		analyze_tokens(char **tokens, t_struct *conf);

/*-------------checks---------------*/

void		checking_line(char *line, t_struct *conf);
void  	  check_after_vertline(char *line, t_struct *conf);
void 		check_streams(char *line, t_struct *conf);
void 		check_double_stream(char *line, t_struct *conf);
void 		check_for_pc_vertline(char *line, t_struct *conf);
void		check_quotes(char *line, t_struct *conf);

/*-------parser to command----------*/

void		*delete_quotes(t_list *token, t_struct *conf);
void		replace_env_var(char *arg, t_struct *conf, char **env);

/*-------------commsnds-------------*/

void		pwd_command(t_command *com);
void		echo_command(t_command *command);
void		env_command(t_command *com, char **env);
void		unset_command(t_command *com, t_struct *conf);
void    	export_command(t_command *com, t_struct *conf);
void		export_command_2(t_struct *conf, t_command *com, int i);
int			check_arg(char **args);
char		**add_arg_new(char **env, char *value);
char		**change_exist_arg(char **env, char *value);
int			check_arg_env(char **env, char *value);
void    	exit_command(t_struct *conf);

/*-------------output----------------*/

void		write_command(t_command *command, char *response);
void		output_error(char *str, t_struct *conf);
void		error_quit(char *str, t_struct *conf);

/*-------------signals---------------*/

void		work_signals(int sgnl);

/*-------------free------------------*/

void		clear_tokens(t_struct *conf);
void		clear_conf(t_struct *conf);
void		clear_env_export(char **arr);
void		clear_command(t_command **coms);

#endif
