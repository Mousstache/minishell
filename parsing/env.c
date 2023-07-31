/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:17:26 by motroian          #+#    #+#             */
/*   Updated: 2023/07/31 22:27:50 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_between_quotes(char *str, char c)
{
    int i;

    i = 0;
    while(str[i] && str[i] != c)
        i++;
    return (i);
}

char    *ft_strjoin_quote(char *s1, char *s2, char c)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    str = malloc(sizeof(char) * (ft_strlen(s1) + count_between_quotes(s2, c) + 1));
    if (!str)
        return (NULL);
    while(s1 && s1[i])
    {
        str[i] = s1[i];
        i++;
    }    
    while(j < count_between_quotes(s2, c))
    {
        str[i + j] = s2[j];
        j++;
    }    
    str[i + j] = 0;
    if (s1)
        free(s1);
    // printf("str == %s", str);
    return (str);
}

int    export_error(char *str, char *msg)
{
    int i;
    int j;

    i = 0;
    j = 0;
    ft_putchar_fd('"', 2);
    while (str[i] && str[i] != ' ' && str[i] != '|')
        ft_putchar_fd(str[i++], 2);
    ft_putchar_fd('"', 2); 
    ft_putchar_fd(' ', 2);
    while(msg[j])
        ft_putchar_fd(msg[j++], 2);
    ft_putchar_fd('\n', 2);
    return(i);
}

char* get_value_var(t_env *env, int i) // recupere la valeur d'une variable existante
{
    int j;
    int k;
    char *str;

    j = 0;
    k = 0;
    while(is_alpha(env->env_copy[i][j]) || env->env_copy[i][j] == '_')
        j++;
    if (env->env_copy[i][j] != '=')
        return (NULL);
    else
    {
        j++;
        if (!env->env_copy[i][j])
            return (NULL);
        while(env->env_copy[i][j + k])
            k++;
        str = malloc(sizeof(char) * (k + 2));
        // env->in_var = ft_strjoin(env->in_var, envint ft_strlen(char *str);->env_copy[i] + j);
        k = 0;
        while(env->env_copy[i][j])
        {
            str[k] = env->env_copy[i][j];
            j++;
            k++;
        }
        str[k] = 0;
    }
    return (str);
}

int check_var_exist(char **env, char *variable)
{
    int i;

    i = 0;
    if (count_var_len(variable) < 1)
        return (-1);
    while(env[i])
    {
        if (strncmp(env[i], variable, count_var_len(variable)) == 0)
            return (i);
        i++;
    }
    return (-1);
}

// char *ft_strdup(char *str)
// {
//     int i;
//     char *tab;

//     i = 0;
//     tab = malloc(sizeof(char) * (ft_strlen(str) + 1));
//     if (!tab)
//         return (NULL);
//     while(str[i])
//     {
//         tab[i] = str[i];
//         i++;
//     }
//     tab[i] = 0;
//     return (tab);
// }

char **add_variable(t_env *env)
{
    int i;
    int j;
    int k;
    char **tab;

    i = 0;
    j = 0;
    k = -1;
    if (!env->var_name)
        return(env->env_copy);
    if (check_var_exist(env->env_copy, env->var_name) > -1)
    {
        tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 1));
        k = check_var_exist(env->env_copy, env->var_name);
    }
    else
        tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 2));
    printf("value == %s\n", env->var_value);
    printf("name == %s\n", env->var_name);
    printf("k == %d\n", k);
    printf("first == %s", env->env_copy[0]);
    while (env->env_copy[i])
    {
        // if (strncmp(env->env_copy[i], env->var_name, count_var_len(env->var_name)))
        // {
        //     tab[j] = ft_strjoin(env->var_name, env->var_value);
        //     printf("lolololo=%s\n", tab[j]);
        //     printf("k == %d\n", count_var_len(env->var_name));
        // }    
        if (k == i)
        {
            tab[j] = ft_strjoin(env->var_name, env->var_value);
            //printf("lolololo=%s\n", tab[j]);
            printf("lenn == %d\n", count_var_len(env->var_name));
        } 
        else
        {
            tab[j] = ft_strdup(env->env_copy[i]);
            // printf("lalalala=%s\n", tab[j]);
        }    
        i++;
        j++;
    }
    if (k == -1)
    {
        tab[j] = ft_strjoin(env->var_name, env->var_value);
        printf("last maillon = %s pos == %d\n", tab[j], j);
        printf("nb maillon = %d\n", count_string(env->env_copy));
        j++;
    }
    tab[j] = NULL;
    free_all(env->env_copy);
    // free(env->var_name);
    //free(env->var_value);
    return (tab);
}


char *ft_strjoin_alphanum(char *s1, char *s2)
{
    int i;
    int j;
    char *res;

    i = 0;
    j = 0;
    res = malloc(sizeof(char) * (ft_strlen(s1) + count_var_len(s2) + 1));
    if (!res)
        return (NULL);
    while(s1 && s1[i])
    {
        res[i] = s1[i];
        // printf("popo\n");
        i++;
    }
    while(j < count_var_len(s2))
    {
        res[i + j] = s2[j];
        j++;
    }    
    if (s1)
        free(s1);
    res[i + j] = 0;
    return (res);
}

int len_before_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '$' && str[i] != '"')
        i++;
    return (i);
}

int char_var_correct(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (!is_alphanum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

char *ft_expand(char *str, t_env *env)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            j = check_var_exist(env->env_copy, str + i);
            if (j >= 0)
                new = ft_strjoin(new, get_value_var(env, j));
            i += count_var_len(str + i);
            printf("%d\n", j);
        }
        else
        {
            new = ft_strjoin_quote(new, str + i, '$');
            if (!new)
                return (NULL);
            i += count_between_quotes(str + i, '$');
        }
    }
    return (new);
}

int add_var_value(t_env *env, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    printf("var_name= %s\n", env->var_name);
    printf("c == %c\n", str[i]);
    if (!char_var_correct(env->var_name))
    {
        export_error(env->var_name, "identfiant non valide");
        free(env->var_name);
        return(0);
    }
    while (str[i] && str[i] != ' ')
    {
        if (str[i] == '"')
        {
            i++;
            while (str[i] != '"')
            {
                if (str[i] == '$')
                {
                    i++;
                    j = check_var_exist(env->env_copy, str + i);
                    if (j >= 0)
                        env->var_name = ft_strjoin(env->var_value, get_value_var(env, j));
                    i += count_var_len(str + i);
                }
                if (str[i] != '"' && (count_between_quotes(str + i, '"') < count_between_quotes(str + i, '$')))
                {
                    env->var_value = ft_strjoin_quote(env->var_value, str + i, '"');
                    i += count_between_quotes(str + i, '"');
                }
                else
                {
                    env->var_value = ft_strjoin_quote(env->var_value, str + i, '$');
                    i += count_between_quotes(str + i, '$');
                }
            }
        }
        else if (str[i] == 39)
        {
            env->var_value = malloc(sizeof(char) * count_between_quotes(str + i, 39) + 1);
            printf("papapapapapapaaaaaaaaaa\n");
            while(i < count_between_quotes(str + i, 39))
            {
                env->var_value[i] = str[i];
                i++;
            }
            env->var_value = 0;
            return (i);
        }
        else 
        {
            if (str[i] == '$')
            {
                printf("rentre dedans\n");
                i++;
                j = check_var_exist(env->env_copy, str + i);
                if (j >= 0)
                    env->var_value = ft_strjoin(env->var_value, get_value_var(env, j));
                i += count_var_len(str + i);
                j = 0;
            }
            if (str[i] != ' ' && (count_between_quotes(str + i, '$') < count_between_quotes(str + i, ' ')))
            {
                printf("poupoupidou\n");
                env->var_value = ft_strjoin_quote(env->var_value, str + i, '$');
                i += count_between_quotes(str + i, '$');
                printf("pidou = %c\n", str[i]);
            }
            else if (str[i] != ' ')
            {
                env->var_value = ft_strjoin_quote(env->var_value, str + i, ' ');
                i += count_between_quotes(str + i, ' ');
            }
        }
    }
    env->env_copy = add_variable(env);
    return (i);
}


int is_not_var_char(char c)
{
    if (!is_alphanum(c) && c != '$' && c != '=' 
        && c != '|' && c != ' ' 
        && c != '"' && c != 39)
        return (1);
    return (0);
}

int add_var_name(t_env *env, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(str[i] != '=' && str[i] != '|')
    {
        if (is_alphanum(str[i]) || str[i] == '_')
        {
            // printf("%c\n", str[i]);
            printf("%s\n", ft_strjoin_alphanum(env->var_name, str + i));
            env->var_name = ft_strjoin_alphanum(env->var_name, str + i);
            i += count_var_len(str + i);
            // printf("char  ==%c\n", 39);

        }
        if (str[i] == 39) 
        {
            i++;
            env->var_name = ft_strjoin_quote(env->var_name, str + i, 39);
            // printf("%d\n", count_between_quotes(str + i, 39));
            i += (count_between_quotes(str + i, 39) + 1);
            // printf("cacaaboudin = %c\n", str[i]);
            // printf("%s\n", env->var_name);

        }
        if (str[i] == '"')
        {
            while (str[i] != '"')
            {
                if (str[i] == '$')
                {
                    i++;
                    j = check_var_exist(env->env_copy, str + i);
                    if (j >= 0)
                        env->var_name = ft_strjoin(env->var_name, get_value_var(env, j));
                    i += count_var_len(str + i);
                }
                if (is_alphanum(str[i]) || str[i] == '_')
                {
                    env->var_name = ft_strjoin_alphanum(env->var_name, str + i);
                    i += count_var_len(str + i);
                }
                if (!is_alphanum(str[i]) && str[i] != '$' && str[i] != '=' && str[i] != '|')
                {
                    i += export_error(str, "identifiant non valable");
                    free(env->var_name);
                    env->var_name = NULL;
                    return (i);
                }
            }    
        }
        if (str[i] == '$')
        {
            i++;
            j = check_var_exist(env->env_copy, str + i);
            if (j >= 0)
                env->var_name = ft_strjoin(env->var_name, get_value_var(env, j));
            i += count_var_len(str + i);
            j = 0;
        }
        if (!is_alphanum(str[i]) && str[i] != '$' && str[i] != '=' && str[i] != '|')
        {
            export_error(str, "identifiant non valable");
            free(env->var_name);
            env->var_name = NULL;
            // printf("trotro %s\n", env->var_name);
            return (i);
        }    
    }
    if (!char_var_correct(env->var_name))
    {
        export_error(env->var_name, "identfiant non valide");
        free(env->var_name);
        return(i);
    }
    else if (str[i] == '=' )
        i += add_var_value(env, str + i);
    return (i);
}

// void    ft_export(t_env *env, char *str)
// {
//     int i;

//     i = 0;
//     while(str[i] && str[i] != '|')
//     {
//         while (is_space(str[i]))
//             i++;
//         if (str[i] && str[i] != '|')
//             i += add_var_name(str + i, env);
//     }
// }

// int count_between_quotes(char *str, char c)
// {
//     int i;

//     i = 0;
//     while(str[i] && str[i] != c)
//         i++;
//     return (i);
// }

char **create_env(char **env)
{
    int i;
    char **str;
    
    i = 0;
    str = calloc(sizeof(char *), (count_string(env) + 1));
    if (!str)
        return(NULL);
    while (env[i])
    {
        str[i] = ft_strdup(env[i]); 
        i++;
    }
    return (str);
}

// int main(int argc, char **argv, char **env)
// {
//     // char **env2 = NULL;
//     // // print_double(env);
//     // env2 = create_env(env);
//     // print_double(env2);
//     // printf("nombre tab = %d\n", count_string(env2));
//     // printf("-----------------------------------------------------");
//     // printf("-----------------------------------------------------");
//     // printf("-----------------------------------------------------");
//     // env2 = ft_unset(env2, "lol");
//     // printf("nombre tab = %d\n", count_string(env2));
//     // print_double(env2);
//     // free_all(env2);

//     t_env envv;

//     // envv = malloc(sizeof(t_env));
//     // printf("reponse = %s\n", argv[1]);
//     envv.var_name = NULL;
//     envv.var_value = NULL;
//     envv.env_copy = create_env(env);
//     // add_var_name(&envv, "salut$VTE_VERSION='$VTE_VERSION$USER$caca'");
//     // add_var_name(&envv, "lol=$PWD");
//     // envv.env_copy = add_variable(&envv);
//     // print_double(envv.env_copy);
//     // free_all(envv.env_copy);
//     // free(envv.var_name);
//     printf("res == %s\n", ft_expand("lscolors = $LSCOLORS none = $'salut' system = $SYSTEMD_EXEC_PID none = $caca", &envv));
// }
