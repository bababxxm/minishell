#ifndef BUILTIN_H
# define BUILTIN_H

typedef enum e_builtin_type
{
	CD,
	ENV,
	PWD,
	ECHO,
	UNSET,
	EXPORT
}	t_builtin_type;

#endif