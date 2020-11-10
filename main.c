/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 02:02:23 by mobounya          #+#    #+#             */
/*   Updated: 2020/11/10 14:30:38 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execute.h"
#include <sys/errno.h>
#include <unistd.h>

extern char		**environ;

void    ft_get_cmd(t_tokens *head, char **env);
t_ast   *ft_parse(t_tokens *lst);
int     *ft_trav_exec(t_ast *root, char ***env);
int		ft_arraysize(char **ar);
void    ft_free_ast(t_ast   **root);

/*
 *  Seperators for the full command, coming directly from user input.
 *    Example of full command : "echo "foo" >> bar | pwd ; cat -e << EOF && ls -l dir1 dir2"
 */

static const t_id seperators[] =
{
    {"&&", DGREAT, "Dgreat"}, 
    {"||", OR, "OR"},
    {"|", PIPE, "Pipe"},
    {";", SEMI, "Semi"},
    {NULL, 0, NULL},
};


char    **ft_envinit(void)
{
    char			**new_env;
    size_t			size;
    unsigned int    i;
    g_exit_code = 0;

	i = 0;
    size = ft_arraysize(environ);
    if ((new_env = malloc(sizeof(char *) * size + 1)) == NULL)
        exit(ENOMEM);
    while (i < size)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int     main(void)
{
    t_ast		*root;
    t_tokens	*head;
    char		*cmd;
    int         *and_or;
    char        **env;

    head = NULL;
    env = ft_envinit();
    while (1)
    {
        if ((cmd = ft_readline()))
        {
            printf("Done\n");
            ft_tokenize(&head, cmd, seperators);
            if (head)
            {
                ft_get_cmd(head, env);
                if ((root = ft_parse(head)) == NULL)
                    ft_putendl_fd("21sh: parse error", 2);
                else
                {
                    and_or = ft_trav_exec(root, &env);
                    and_or[0] = -1;
                    and_or[1] = -1;
                }
                ft_free_ast(&root);
                head = NULL;
            }
            ft_memdel((void **)&cmd);
        }
        else
            ft_putchar('\n');
    }
    ft_free_arr(env);
}
