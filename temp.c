

int		*ft_execute(t_ast *root)
{
	char			**cmd;
	static int		and_or[2] = {-1, -1};
	char			str[3];

	if (root == NULL)
		return (and_or);
	ft_execute(root->left);
	if (root->token->token_id == OR)
		and_or[1] = 1;
	else if (root->token->token_id == AND)
		and_or[0] = 1;
	if (root->token->token_id == SIMPLE_COMMAND)
	{
		if ((and_or[0] == -1 && and_or[1] == -1) || ((and_or[1]  == 1 && g_exit_code != 0) \
			|| (and_or[0] == 1 && g_exit_code == 0)))
		{
			cmd = ft_lsttoa(root->token->command_tokens);
			if (is_builtin(cmd) == 0)
				g_exit_code = 1;
			else
				g_exit_code = 0;
			and_or[0] = -1;
			and_or[1] = -1;
		}
	}
	ft_execute(root->right);
	return (and_or);
}