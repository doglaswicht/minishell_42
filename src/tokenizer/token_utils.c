#include "tokenizer.h"  // Para os protótipos das funções que você está implementando
#include <stdlib.h>     // Para malloc


int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

#include <stdlib.h>

t_token	*new_token(const char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = (char *)value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*temp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
