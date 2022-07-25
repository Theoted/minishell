/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:29:36 by theodeville       #+#    #+#             */
/*   Updated: 2022/07/25 16:02:50 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    print_export(t_envp *envp)
{
    t_envp *tmp;

    tmp = envp;
    while (tmp)
    {
        printf("declare -x %s", tmp->name);
        if (tmp->content)
            printf("=\"%s\"", tmp->content);
        printf("\n");
        tmp = tmp->next;
    }
}

void    env_lst_addfront(t_envp **alst, t_envp *new)
{
    if (!alst || !new)
        return;
    new->next = *alst;
    *alst = new;
}

void    env_lst_change_content(t_envp *node, char *content)
{
    if (!node)
        return;
    node->content = content;
}

t_envp  *check_if_exist(t_envp *alst, char *name)
{
    while (alst)
    {
        if (!strncmp_len(alst->name, name))
            return (alst);
        alst = alst->next;
    }
    return (NULL);
}

int contains_equal(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

// Creer une variable d'environnement avec un contenu qui pointe sur NULL
int create_var_no_content
    (t_data_p *data, char *arg, char **content, char **name)
{
    *name = gc_strdup(&data->track, arg);
    *content = NULL;
    return (1);
}

int check_arg(t_data_p *data, char *arg, char **content, char **name)
{
    int     i;
    t_envp  *tmp;

    i = 0;
    tmp = data->envp;
    if (arg[0] == '=')
    {
        printf("export: `%s': not a valid identifier\n", arg);
        return (1);
    }
    if (!contains_equal(arg))
    {
        if (!check_if_exist(tmp, arg))
            return (create_var_no_content(data, arg, content, name));
        return (1);
    }
    while (arg[i] && arg[i] != '=')
    {
        printf("test\n");
        if (arg[i] == ' ')
            return (1);
        i++;
    }
    *name = gc_substr(&data->track, arg, 0, i);
    *content = gc_substr(&data->track, arg, i + 1, ft_strlen(arg) - i);
    return (0);
}

int b_export(t_data_p *data, int idx)
{
    int i;
    char *content;
    char *name;
    t_envp *in_list;

    i = 1;
    if (!arg_vec_len(data, idx))
        print_export(data->envp);
    while (data->commands[idx].args_vec[i])
    {
        content = NULL;
        name = NULL;
        in_list = NULL;
        check_arg(data, data->commands[idx].args_vec[i], &content, &name);
        if (name)
        {
            in_list = check_if_exist(data->envp, name);
            if (in_list)
                env_lst_change_content(in_list, content);
            else
                env_lst_addfront(&data->envp, env_lstnew(data, name, content));
        }
        i++;
    }
    return (1);
}
