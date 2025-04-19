/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 21:40:36 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    sighandler(int sig, siginfo_t *info, void *ucontext)
// {
//     if (sig == SIGINT)
//     {
//         printf("\n%s$ ", PROMPT);
//     }
// }

char    *parser(char *input, t_shell *shell)
{
    int     i;

    i = -1;
    printf("input: %s\n", input);
    get_tokens(input);
    // while (input[++i])
    // {
    //     ft_lstadd_back(&token, new_token());
    // }
    return (NULL);
}

void    execute(t_cmds *cmds, t_shell *shell)
{

}

void    sigint_handler(int sigint)
{
    
}

void    sigquit_handler(int sigquit)
{
    
}

void    init_shell(char *env[], t_shell *shell)
{    
    // struct sigaction    sa;
    
    shell->cmds = NULL;
    shell->tokens = NULL;
    shell->env = dup_env(env);
    shell->path = search_env("PATH", shell->env);
    shell->user = search_env("USER", shell->env);
    shell->home = search_env("HOME", shell->env);
    shell->oldpwd = search_env("OLDPWD", shell->env);
    shell->pwd = search_env("PWD", shell->env);
    // sa.sa_sigaction = &sighandler;
	// sa.sa_flags = SA_SIGINFO;
	// sigemptyset(&sa.sa_mask);
    // sigaction(SIGINT, &sa, NULL);
    // sigaction(SIGQUIT, &sa, NULL);
    // signal(SIGINT, &sigint_handler);
    // signal(SIGQUIT, &sigquit_handler);
}

void    exit_shell(t_shell *shell)
{
    printf("exit\n");
    rl_clear_history();
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[], char *env[])
{
    t_shell shell;

    init_shell(env, &shell);
    while (true)
    {
        shell.input = readline(PROMPT);
        if (!shell.input)
            exit_shell(&shell);
        parser(shell.input, &shell);
        execute(shell.cmds, &shell);
        add_history(shell.input);
        free(shell.input);
    }
}
