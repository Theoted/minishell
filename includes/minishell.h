/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:24:25 by tdeville          #+#    #+#             */
/*   Updated: 2022/07/15 13:54:50 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft2/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>


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

struct s_envp
{
	char	*name;
	char	*content;
	struct	s_envp *next;
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
	/* fd file && pipe*/
	int		fd_in;
	int		fd_out;
	int		pfd[2];
	char	*here_doc;
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

// struct s_commands
// {
// 	char	**args_vec;
// 	char	*cmd_path;
// 	char	*here_doc;
// 	int		infile;
// 	int		outfile;
// 	int		infile_type;
// 	int		last_in_type;
// 	t_files	*files;
// };

struct s_hd_data
{
	int		expend_var;
	int		check;
	char	*tmp;
	char	*tmp1;
	char	*new_buffer;
	char	*here_doc_del;
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
	
	t_envp		*envp;
	t_commands	*commands;
	t_hd_data	hd_data;
	t_track		*track;
};

/* ------------------- EXECUTION ------------------- */

void	e_execve(t_commands *c);
int		open_infile(t_commands *c, char *infile);
int		open_outfile(t_commands *c, char *outfile);
int		open_outfile_hb(t_commands *c, char *outfile_hb);
void	e_heredoc(t_commands *c);
int		open_files(t_commands *c);
int		e_child(t_data_p *d, t_commands *c);
void	e_exec(t_data_p *d, t_commands *c);
int		main (int argc, char **argv, char **envp);
void	check_path(t_data_p *d, t_commands *c);

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

	// Get cmd
char 	*get_cmd_in_arg(char *arg, t_data_p *data, int idx);
char 	*skip_in_out_hd(char *arg, t_data_p *data);
void	skip_in_hd(char *arg, int *i);
void	skip_out(char *arg, int *i);
void	skip_spaces(char *arg, int *i);
char	*get_cmd(char *arg, int i, t_data_p *data);

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
int 	last_in_redir(char *arg);
int 	get_in_out_files(char *arg, t_data_p *data, int idx);
int 	count_in_out_files(char *arg);
int 	get_file(char *arg, int *start, int *type);
int 	idx_after_hd(char *arg, int *start);
void 	fill_envp_cmd(t_data_p *data);

	// Expend variables
int		check_arg_vars(char *arg, t_data_p *data);
char	**get_exp_vars_arg(char *arg, t_data_p *data);


	// Built-ins
		// UNSET
void	init_our_envp(t_data_p *data);
void    delete_env_node(t_envp **env_lst, char *name);
void	print_env_list(t_envp *env_list);
void    b_unset(t_data_p *data, int cmd_id);

		// EXPORT
void    b_export(t_data_p *data, int idx);

		// EXIT
int 	b_exit(char *input);

		// CD
int		b_cd(t_data_p *data, int idx);

		//Built-ins init
int		detect_buitins(t_data_p *data);
void    exec_built_ins(t_data_p *data, int idx, char *builtin);
t_envp	*env_lstnew(t_data_p *data, char *name, char *content);

		//Built-ins utils
int		strncmp_len(char *s1, char *s2);
void 	print_env_list(t_envp *env_list);

#endif
