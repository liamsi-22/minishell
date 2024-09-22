#include "../parsing.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((*s1 == *s2) && *s1 && *s2)
	{
		s1++;
		s2++;
		i++;
	}
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}