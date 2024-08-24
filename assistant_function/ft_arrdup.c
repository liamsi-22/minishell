#include "../parsing.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		*ret;

	ret = malloc(count * size);
	if (!ret)
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}

char	**ft_arrdup(char **arr)
{
	char	**array2;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	array2 = ft_calloc(sizeof(char *), i + 1);
	if (!array2)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		array2[i] = ft_strdup(arr[i]);
		if (array2[i] == NULL)
		{
			free_arr(array2);
			return (array2);
		}
		i++;
	}
	return (array2);
}