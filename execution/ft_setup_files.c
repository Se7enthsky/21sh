#include "../includes/main.h"

static void ft_create_files(t_tokens *token_lst)
{
	int token_id;
	char *filename;
	int fd;

	while (token_lst)
	{
		token_id = token_lst->token_id;
		if (token_id == GREAT || token_id == DGREAT ||
			token_id == FD_GREAT || token_id == FD_FILE)
		{
			if (token_id == FD_GREAT)
				filename = token_lst->next->value;
			else
				filename = ft_strdup((token_lst->value) + 2);
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
			close(fd);
		}
		token_lst = token_lst->next;
	}
}

void setup_files(t_ast *root)
{
	int token_id;

	if (root == NULL)
		return;
	setup_files(root->left);
	token_id = root->token->token_id;
	if (token_id == OR || token_id == AND || token_id == SEMI)
		return;
	if (token_id == SIMPLE_COMMAND)
	{
		if (root->token->pipe_after || root->token->pipe_before)
			ft_create_files(root->token->command_tokens);
	}
	setup_files(root->right);
}
