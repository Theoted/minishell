/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pat <pat@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:06:25 by rmattheo          #+#    #+#             */
/*   Updated: 2022/04/07 14:09:43 by pat              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft2/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h> 

# define HEREDOC 1
# define INFILE 2

typedef struct s_commands
{
	/* cmd pour l'execve */
	char	**args_vec;
	char	**envp;
	char	*cmd_path;
	/* fd file */
	int		infile;
	int		outfile;
	char	*here_doc;
	int		infile_type;
	/* pipe */
	int		pipe_heredoc1;
	int		pipe_heredoc0;
	int		next_pfd1;
	int		next_pfd0;
	int		prev_pfd1;
	int		prev_pfd0;
	/* pid */
	int		pid;
	int		pid_heredoc;
	/* stop */
	int		stop;
}			t_commands;

typedef struct s_hd_data
{
	int		expend_var;
	int		check;
	char	*tmp;
	char	*tmp1;
	char	*new_buffer;
	char	*here_doc_del;
}				t_hd_data;

typedef struct s_data_p
{
	char		*stdin_arg;
	char    	*path;
	char    	**env_path;
	char		**args;
	char		**env_vars;
	int			pipes_nb;
	int			**pip;
	int			args_create;
	t_commands	*commands;
	t_hd_data	hd_data;
	t_track		*track;
}				t_data_p;

/* ------------------- EXECUTION ------------------- */


void	e_exec(t_data_p *data, t_commands *cmd);
void	close_all_pipe(t_commands *c);
void	open_all_pipe(t_data_p *data, t_commands *c);
void	e_infile_heredoc_cmd_outfile(t_data_p *data, t_commands c);
void	e_infile_heredoc_cmd(t_data_p *data, t_commands c);
void	e_cmd_outfile(t_data_p *data, t_commands c);
void	e_cmd_cmd(t_data_p *data, t_commands c);
void	e_heredoc_pipe(t_data_p *data, t_commands *c, int i);
void	e_heredoc(t_data_p *data, t_commands c);
void	close_all_file(t_commands *c);


/* ------------------- PARSING ------------------- */
	// Bin Path
int		find_env_path(char **envp, t_data_p *data);
int		ft_access(char *arg);
char	*expend_env_var(t_data_p *data, char **envp, char *var);

	// Lexer
int		lexer(char *arg, t_data_p *data);
int		pipe_check(char *arg, int i);
int		synthax_checker(char *arg);
int		split_args(char *arg, t_data_p *data);
int		create_arg(char *str, int i, t_data_p *data, int bad_pipe);
int		count_pipes(char *str);
int		pipe_synthax(char *str, t_data_p data);

	// Here_doc
int		check_heredoc(char *arg, t_data_p *data, int idx);
int		get_heredoc_del(char *arg, int i, t_data_p *data);
int		ft_here_doc(t_data_p *data, int idx);
int		here_doc_write(t_data_p *data, char *buffer, int idx);
char	*expend_var_in_buffer(char *buffer, char **expended_vars, t_data_p *data);
int		format_del(char *del, t_data_p *data);
void	fill_vars_tab(t_data_p *data, char **var, char *buffer, int *idx, int *k);
char	*get_expend_var(t_data_p *data, char *buffer);
	// Here_doc utils
int		nb_of_env_vars(char *buffer);
char	*check_bsn_buffer(t_data_p *data, char *new_buffer);
int		check_var(char *var);
char	*trim_last_bsn(t_data_p *data, char *here_doc_content);
int		check_del(char *del);
	// Clear here_doc
char	*clear_here_doc(t_data_p *data, char *arg);


	// Utils
int 	state_checker(char *str, int start, int len);

	// Expend variables
int		check_arg_vars(char *arg, t_data_p *data);

#endif
