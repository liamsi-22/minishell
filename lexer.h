# ifndef LEXER_H
# define LEXER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char    	*str;
	t_tokens        token;
	int		i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;


#endif
