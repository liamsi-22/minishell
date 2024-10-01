/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:17 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/10/01 16:57:18 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static size_t    count_words(const char *s, char c)
{
    size_t    counter;

    counter = 0;
    while (*s)
    {
        if (*s != c && (*(s + 1) == '\0' || *(s + 1) == c))
            counter++;
        s++;
    }
    return (counter);
}

static size_t    word_length(const char *s, char c)
{
    size_t    counter;

    counter = 0;
    while (*s != c && *s != '\0')
    {
        counter++;
        s++;
    }
    return (counter);
}

static void    *ft_free(char **s)
{    
    int    i;

    i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
    return (NULL);
}

char    **ft_split(char const *s, char c)
{
    char    **new;
    size_t    i;
    size_t    j;

    if (!s)
        return (NULL);
    new = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while (s[j] && i < count_words(s, c))
    {
        if (s[j] != c)
        {
            new[i] = ft_substr(s, j, word_length(s + j, c));
            if (!new[i++])
                return (ft_free(new));
            j += word_length(s + j, c);
        }
        else
            j++;
    }
    new[i] = NULL;
    return (new);
}
