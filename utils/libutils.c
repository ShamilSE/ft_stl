#include "libutils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *p;

	p = dst;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (p);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned char		*last_d;
	const unsigned char	*last_s;

	d = dst;
	s = src;
	if (!dst && !src)
		return (NULL);
	if (d < s)
		ft_memcpy(dst, src, len);
	else
	{
		last_d = &d[len - 1];
		last_s = &s[len - 1];
		while (len--)
			*last_d-- = *last_s--;
	}
	return (dst);
}
