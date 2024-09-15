#include "../parsing.h"

size_t	ft_strllcpy(char *dst, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (!dst || !src)
	{
		return (0);
	}
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

char	*ft_strchr(char const *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set, char const *set1)
{
	size_t	start;
	size_t	end;
	char	*dup;

	if (!s1 || !set || !set1)
		return (NULL);
	start = 0;
	if (!s1[start])
	{
		dup = ft_strdup("");
		return (dup);
	}
	while (s1[start] && (ft_strchr(set, s1[start]) != NULL || ft_strchr(set1, s1[start]) != NULL))
		start++;
	end = ft_strlen(s1);
	while (end > start && (ft_strchr(set, s1[end]) != NULL || ft_strchr(set1, s1[end]) != NULL))
		end--;
	dup = (char *)malloc(end - start + 2);
	if (dup == NULL)
		return (NULL);
	ft_strllcpy(dup, s1 + start, end - start + 2);
	return (dup);
}
