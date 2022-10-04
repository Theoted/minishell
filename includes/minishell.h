/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:24:25 by tdeville          #+#    #+#             */
/*   Updated: 2022/10/04 14:20:10 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft2/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>


# define INFILE 1
# define OUTFILE 2
# define OUTFILE_HB 3

# define HEREDOC_TYPE 2
# define INFILE_TYPE 1

typedef struct s_commands t_commands;
typedef struct s_data_p t_data_p;
typedef struct s_hd_data t_hd_data;
typedef struct s_files t_files;
typedef struct s_envp t_envp;
typedef struct s_echo t_echo;
typedef struct s_echo_2 t_echo_2;
typedef struct s_echo_env t_echo_env;
typedef	struct s_export	t_export;

// Structure qui permet le parsing des variables d'environnements
struct s_echo_env
{
	char	*new;
	char	*tmp;
	char	quote;
};

// Structure qui permet l'execution de echo
struct s_echo_2
{
	int		bn;
	char	*new;
	int		av_len;
	int		check;
};

// Structure qui permet le parsing des arguments de echo
struct s_echo
{
	char	*new;
	char	*arg;
	char	quote;
	int		idx;
};

struct s_export
{
	char	*name;
	char	*content;
	int		equal;
};

struct s_envp
{
	char			*name;
	char			*content;
	int				equal;
	struct	s_envp	*next;
};

// Type: 1 = < , 2 = > , 3 = >>
struct s_files
{
	char	*file;
	int		type;
	int		stop;
};

/* la variable last_in_type dans la structure commande
représente pour chaque commande le dernier type 
de redirection sur l'entrée si il y en a une.
	0 = aucune
	1 = infile
	2 = here_doc
*/
struct s_commands
{
	/* cmd pour l'execve */
	char	**args_vec;
	char	**envp;
	char	*cmd_path;
	int		echo_arg_nb;
	/* fd file && pipe*/
	int		fd_in;
	int		fd_out;
	int		pfd[2];
	char	*here_doc;
	int		pipehd[2];
	int		infile;
	int		outfile;
	int		last_in_type;
	t_files	*files;
	/* pid */
	int		pid;
	int		pid_heredoc;
	/* stop */
	int		stop;
};

struct s_hd_data
{
	int		i;
	int		j;
	int		k;
	int		expend_var;
	int		check;
	char	**expended_vars;
	char	*tmp;
	char	*tmp1;
	char	*new_buffer;
	char	*here_doc_del;
	int		hd_pipe[2];
};

struct s_data_p
{
	char		*stdin_arg;
	char    	*path;
	char    	**env_path;
	char		**args;
	char		**env_vars;
	int			pipes_nb;
	int			args_create;
	char		*cmd_slash;
	int			exp_equal;
	
	t_envp		*envp;
	t_commands	*commands;
	t_hd_data	hd_data;
	t_track		*track;
};

/* ------------------- EXECUTION ------------------- */

void	e_execve(t_data_p *d, t_commands *c, int idx);
int		open_infile(t_commands *c, char *infile);
int		open_outfile(t_commands *c, char *outfile);
int		open_outfile_hb(t_commands *c, char *outfile_hb);
void	e_heredoc(t_commands *c);
int		open_files(t_commands *c);
int		e_child(t_data_p *d, t_commands *c, int idx);
void	e_exec(t_data_p *d, t_commands *c);
int		main (int argc, char **argv, char **envp);
void	check_path(t_data_p *d, t_commands *c);
void	dup_fd_in_pipe(t_commands *c, int i);
void	action(int sig);
void	sig_int(int sig);
void	sig_child(void);
void	sig_parent(void);
void	sig_handler_parent(int sig);
void	sig_handler_parent_hd(int sig);
void	sig_handler_child(int sig);
static int	ft_strcmp(char *arg, char *built);
int		execve_error(char *arg);

//		Replace line
void	rl_replace_line (const char *text, int clear_undo);

/* ------------------- PARSING ------------------- */
	// Bin Path
int 	find_env_path(t_envp *envp, t_data_p *data);
char	*expend_env_var(t_data_p *data, t_envp *envp, char *var);

	// Lexer
int		lexer(char *arg, t_data_p *data);
int		pipe_check(char *arg, int i);
int		split_args(char *arg, t_data_p *data);
int		create_arg(char *str, int i, t_data_p *data, int bad_pipe);
int		count_pipes(char *str);

	// Synthax_checker
int		synthax_checker(char *arg);
int		pipe_synthax(char *str, t_data_p data);
int		check_space(char *arg);
int		check_heredoc2(char *arg, int i);

	// Get cmd
int		get_cmd_in_arg(char *arg, t_data_p *data, int idx);
char 	*skip_in_out_hd(char *arg, t_data_p *data);
void	skip_in_hd(char *arg, int *i);
void	skip_out(char *arg, int *i);
void	skip_spaces(char *arg, int *i);
char	*get_cmd(char *arg, int i, t_data_p *data);
char	*remove_quotes(t_data_p *data, char *arg);

	// Here_doc
int		check_heredoc(char *arg, t_data_p *data, int idx);
int		get_heredoc_del(char *arg, int i, t_data_p *data);
int		ft_here_doc(t_data_p *data, int idx);
int		here_doc_write(t_data_p *data, char *buffer, int idx);
char	*expend_var_in_buffer(char *buffer, char **expended_vars, t_data_p *data);
int		format_del(char *del, t_data_p *data);
void	fill_vars_tab(t_data_p *data, char **var, char *buffer, t_hd_data *hdd);
char	*get_expend_var(t_data_p *data, char *buffer);
	
	// Here_doc utils
int		nb_of_env_vars(char *buffer);
char	*check_bsn_buffer(t_data_p *data, char *new_buffer);
int		check_var(char *var);
char	*trim_last_bsn(t_data_p *data, char *here_doc_content);
int		check_del(char *del);
int		check_solo_var(char *buffer);
int		set_id_after_env(char *buffer, int i);
char	*get_pipe_content(int fd, t_data_p *data);
int		hd_loop(t_data_p *data, int idx, int del_len);
char	**convert_envp(t_data_p *data, t_envp *envp);

	// Utils
int 	state_checker(char *str, int start, int len);
int 	last_in_redir(char *arg);
int 	get_in_out_files(char *arg, t_data_p *data, int idx);
int 	in_out_len(char *arg);
int 	get_file(char *arg, int *start, int *type);
int 	idx_after_hd(char *arg, int *start);
void 	fill_envp_cmd(t_data_p *data);
int		find_char(char *arg, char c);
int		strncmp_ncs(char *s1, char *s2);
char	*find_node_content(char *name, t_envp *envp);
int		double_arr_len(char **arg);
int		echo_arg_nb(char **args);
void	get_old_pwd_print(int x);
void    remove_quote_init(t_echo *data, char *arg);

	// Expend variables
int		check_arg_vars(char *arg, t_data_p *data);

	// Init
void	env_lstadd_back(t_data_p *data, t_envp **alst, t_envp *new);
t_envp	*env_lstnew(t_data_p *data, char *name, char *content, int equal);
void	get_in_out_init(int *i, int *j, int *in_type);

/* ------------------- BUILT-INS ------------------- */
		// UNSET
void	init_our_envp(t_data_p *data);
void    delete_env_node(t_envp **env_lst, char *name);
void	print_env_list(t_envp *env_list);
int		b_unset(t_data_p *data, int cmd_id);

		// EXPORT
int		b_export(t_data_p *data, int idx);
		// EXPORT 2
void	print_export(t_data_p *data, t_envp *envp, int idx);
void	env_lst_addfront(t_envp **alst, t_envp *new);
void	env_lst_change_content(t_envp *node, char *content);
t_envp	*check_if_exist(t_envp *alst, char *name);
int		export_error_arg(char *arg);


		// EXIT
int		b_exit(t_data_p *d, int idx);
int		exit_error_avlen(void);

		// CD
int		b_cd(t_data_p *data, int idx);

		// ECHO
void	b_echo(t_data_p *data, int idx);
int		expend_echo_env_vars(t_data_p *data, char **arg);
char    *get_echo_env_var(t_data_p *data, char *arg);
char	*echo_parse_bs(char *arg, t_data_p *data);
char	*echo_trim_bs(char *arg, int *i, t_data_p *data);
char	*check_exit_status(t_data_p *data, char *arg, int i);

		// ECHO UTILS
int		word_end_id(char *arg, int i);
int		next_quote_id(char *arg, char quote, int i, t_echo *e_d);
int		arg_vec_len(t_data_p *data, int idx);
int		check_n(char *arg, int i);
void	echo_env_var_doll2(t_data_p *data, t_echo_env *e_d, int *i, int j);
int		check_num(char *arg, int i);

		//Built-ins utils
int		strncmp_len(char *s1, char *s2);
void 	print_env_list(t_envp *env_list);
int		arg_vec_len(t_data_p *data, int idx);
void	ft_exec_built_fork(t_data_p *d, t_commands *c, int idx);
int		ft_exec_built_nofork(t_data_p *d, t_commands *c, int idx);

#endif
