/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelen <bbelen@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:12:57 by bbelen            #+#    #+#             */
/*   Updated: 2021/01/16 13:57:35 by bbelen           ###   ########.fr       */
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
# include <sys/wait.h>

typedef struct			s_command
{
	char				*name;
	char				**args;
	char				**file;
	struct s_command	*next;
	char				**arrows;
	char				pipe_sc;
}						t_command;

typedef struct			s_struct
{
	char				**env;
	char				**export;
	char				*error;
	char				**tokens;
	t_command			*command;
	t_command			*curr_command;
	t_command			**command_array;
	char				**betweens;
	char				***arr;
	int					*arr_int;
}						t_struct;

int			g_signal;
int			g_flag;
char		*g_shell_line;
char		*g_error;

/*
** -------------inits-----------------
*/

void					init_conf(t_struct *conf);
t_command				*init_command(t_struct *conf);
void					init_command_array(t_struct *conf, int pipes);
void					init_betweens(t_struct *conf);

/*
** -------------main----------------
*/

void					read_shell_line(t_struct *conf);
int						gnl_shell(int fd, char **line, t_struct *conf);

/*
** -------------utils---------------
*/

int						ft_arrlen(char **arr);
char					**ft_array_realloc(char **src, char *line);
void					ft_array_free(char **arr);
int						is_in(char *str, char c);

/*
** -------------parser---------------
*/

char					**parser_env(char **env);
void					parser_line(char **line, t_struct *conf);
char					**split_tokens(char const *s);
void					split_line(char **line, t_struct *conf);
void					analyze_tokens(t_struct *conf, char **tokens);

/*
** -------------checks---------------
*/

void					checking_line(char *line, t_struct *conf);
void					check_after_vertline(char *line, t_struct *conf);
void					check_streams(char *line, t_struct *conf);
void					check_double_stream(char *line, t_struct *conf);
void					check_for_pc_vertline(char *line, t_struct *conf);
void					check_quotes(char *line, t_struct *conf);

/*
** -------parser to command----------
*/

int						create_command(char **tokens, t_struct *conf);
char					*delete_quotes(char *token);
int						is_command_end(char *token);
int						if_command_name(char *token, char *path);
char					*edit_arg(char *token, t_struct *conf);
void					ft_comadd_back(t_command **lst, t_command *new);
int						if_internal(char *name);
char					*edit_arg_main(char *token, char **env);
char					*find_env_var(char *token, int *i, int *j);
char					*quotes(char *token, int *i, int *j, char **env);
char					*get_env_var(char *arg, char **env);
char					*edit_arg_2(char *token, char **env, int flag);
char					*add_char(char *old, char c);
void					fill_arg(t_command *com, char *token, t_struct *conf);
int						fill_pipe_sc(t_command *com, char *token,
								t_struct *conf, int i);
int						fill_arrows(t_command *com, char **tokens);
void					fill_com_name(t_command *com, char *token,
								int *flag_name);

/*
** -------------commsnds-------------
*/

void					command_main(t_struct *conf);
void					command_hub(t_command *com, t_struct *conf);
void					pwd_command(t_command *com, t_struct *conf);
void					echo_command(t_command *com, t_struct *conf);
void					env_command(t_command *com, char **env, t_struct *conf);
void					unset_command(t_command *com, t_struct *conf);
void					export_command(t_command *com, t_struct *conf);
void					export_command_2(t_struct *conf, t_command *com, int i);
int						check_arg(char **args);
char					**add_arg_new(char **env, char *value);
char					**change_exist_arg(char **env, char *value);
int						check_arg_env(char **env, char *value);
void					exit_command(t_struct *conf);
int						cd_command(t_command *com, t_struct *conf);
void					outsource(t_command *com, t_struct *conf);
char					*outsource_relative(char *path, t_struct *conf);
t_command				*pipes_command(t_struct *conf, t_command *com);
char					**outsouce_arr(t_command *com, t_struct *conf);
void					do_pipes(t_struct *conf, int pipes);
void					next_pipe(t_struct *conf, int *fd, int pipe_from,
							int i);

/*
** -------------output----------------
*/

void					write_command(t_command *com, char *response,
							t_struct *conf);
void					output_error(char *str, t_struct *conf);
void					error_quit(char *str, t_struct *conf);
void					simple_quit();
void					error_code(char	*com, int code, t_struct *conf);
int						get_fd(t_command *com, t_struct *conf);

/*
** -------------signals---------------
*/

void					work_signals(int sgnl);

/*
** -------------free------------------
*/

void					clear_tokens(t_struct *conf);
void					clear_conf(t_struct *conf);
void					clear_env_export(char **arr);
void					clear_command(t_command *coms);
void					clear_command_array(t_struct *conf, int pipes);

/*
** --------------forkszhopa-----------
*/

void					do_forks(t_command *com, char **args, int flag,
							t_struct *conf);
void					do_fork(t_command *com, char **args, t_struct *conf);
void					redirect_fork(char *file, char *sym, char **args);
void					arrow_to(int fd, char **args, pid_t curr_pid,
							int *p_fd);
void					arrow_from(int fd, char **args, pid_t curr_pid,
							int *p_fd);
void					redirect_pipefork(t_struct *conf, int fid, char **args,
							t_command *command_array);

#endif
