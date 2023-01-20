/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:07:28 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 17:07:30 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strrchr(char const *s, int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(char const *str);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(char const *s, int c);
size_t	ft_strlcat(char *dest, char const *src, size_t size);
size_t	ft_strlcpy(char *dest, char const *src, size_t size);
size_t	ft_strlen(char const *str);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
char	*ft_strnstr(char const *haystack, char const *needle, size_t n);
char	*ft_strdup(char const *s);
void	*ft_calloc(size_t nmemb, size_t size);
t_list	*ft_lstnew(void *content);
char	**ft_split(char const *str, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int nb);
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstiter(t_list *lst, void (*f) (void *));
void	ft_lstdelone(t_list *lst, void (*del) (void *));
void	ft_lstclear(t_list **lst, void (*del) (void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
