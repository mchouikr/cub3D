/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:54:36 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/13 13:07:53 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_tokens(char const *s, char delim)
{
	size_t	tokens;
	int		inside_token;

	if (!s)
		return (0);
	tokens = 0;
	inside_token = 1;
	while (*s)
	{
		inside_token = 0;
		while (*s != delim && *s)
		{
			if (!inside_token)
			{
				tokens++;
				inside_token = 1;
			}
			s++;
		}
		while (*s == delim && *s)
			s++;
	}
	return (tokens);
}

static int	safe_malloc(char **array, int position, size_t buffer)
{
	int	i;

	i = 0;
	array[position] = malloc(buffer * sizeof(char));
	if (array[position] == NULL)
	{
		while (i < position)
		{
			free(array[i]);
			i++;
		}
		free(array);
		return (0);
	}
	return (1);
}

static int	fill(char **array, char const *s, char delim)
{
	size_t	len;
	int		start;

	start = 0;
	while (*s)
	{
		len = 0;
		while (*s == delim && *s)
			s++;
		while (*s != delim && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (!safe_malloc(array, start, len + 1))
				return (0);
			ft_strlcpy(array[start], s - len, len + 1);
			start++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**split_arr;

	if (!s || !c)
		return (NULL);
	tokens = count_tokens(s, c);
	if (tokens < 1)
		return (NULL);
	split_arr = malloc((tokens + 1) * sizeof(char *));
	if (!split_arr)
		return (NULL);
	split_arr[tokens] = NULL;
	if (!fill(split_arr, s, c))
		return (NULL);
	return (split_arr);
}

// Count tokens and add to counter to correctly point **array
//Malloc and free after token have been put in the token vector (array)
//So iterating over so each copy is destroyed before the next after
//Filling each token at array[position]
// Split and allocate the amount of token in *s into the token_v

/*
static	int	ft_count_word(char const *s, char c)
{
	int	flag;
	int	count;

	count = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (count);
}

static	char	*write_words(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static void	*ft_free(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static void	variables(size_t *i, int *j, int *word_start)
{
	*i = 0;
	*j = 0;
	*word_start = -1;
}

char	**ft_split(char const *s, char c)
{
	char	**word_array;
	size_t	i;
	int		j;
	int		word_start;

	variables(&i, &j, &word_start);
	word_array = ft_calloc((ft_count_word(s, c) + 1), sizeof(char *));
	if (!word_array)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && word_start < 0)
			word_start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && word_start >= 0)
		{
			word_array[j] = write_words(s, word_start, i);
			if (!word_array[j])
				return (ft_free(word_array, j));
			word_start = -1;
			j++;
		}
		i++;
	}
	return (word_array);
}

//Rewrite using memchr or strchr to move word pointer.
// And or count token amount


Something like "i = ft_memchr(blabla)
				flag = 0
					then flag = 1
				reset reloop memchr etc.
*/
