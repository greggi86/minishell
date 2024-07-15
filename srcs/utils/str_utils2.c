
#include "../../includes/minishell.h"

/*
ft_strncmp():	compares 2 strings up to n chars

Arguments:		const char *s1
				const char *s2

Return:			int 0 if equal. diff when different

How it works:
				1. loop array until n chars and return difference
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*u_s1;
	unsigned char	*u_s2;
	size_t			i;

	u_s1 = (unsigned char *) s1;
	u_s2 = (unsigned char *) s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (u_s1[i] != '\0' && u_s2[i] != '\0' && (i + 1 < n)
		&& u_s1[i] == u_s2[i])
	{
		i++;
	}
	return (u_s1[i] - u_s2[i]);
}

/*
ft_strlcpy():	copies string 

Arguments:	

Return:	

How it works:
				1. 
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while ((dstsize - 1) > i && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}


