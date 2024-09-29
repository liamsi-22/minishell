#include "../parsing.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;

    if (!arr)
        return;
	while (arr[i])
	{
		// printf("__%s__\n", arr[i]);
		// char *s = arr[i + 1];
		free(arr[i]);
		i++;
		// arr[i] = s;
	}
	free(arr);
}

// void free_arr(char **arr)
// {
//     if (!arr) {
//         return;  // If the arr is NULL, there's nothing to free.
//     }
    
//     for (int i = 0; arr[i] != NULL; i++) {
//         free(arr[i]);  // Free each individual string.
//     }
    
//     free(arr);  // Finally, free the arr itself.
// }