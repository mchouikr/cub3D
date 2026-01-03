/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:02:58 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/14 11:31:49 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *str);
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_putstr(char const *str);
void				ft_putnbr_fd(int n, int fd);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strdup(const char *str);
char				*ft_strrchr(const char *str, int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strnstr(const char *str, const char *search,
						size_t len);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t nelem, size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_putendl_fd(char *s, int fd);
char				*ft_itoa(int nb);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*ft_itoa_base(int nb, int base);
int					ft_int_len_base(long int nb, int base);
void				ft_putnbr_base_fd(uintptr_t n, int fd, int base);
int					ft_printf(const char *format, ...);
int					ft_putchar_fd_c(char c, int fd, int *count);
int					ft_putstr_fd_c(const char *s, int fd, int *count);
int					ft_putnbr_printf_u(unsigned long nb, int base, int *count);
int					ft_putnbr_printf(long nb, int uppercase, int base,
						int *count);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *str);
int					ft_strchr_int(char *str, char c);
char				*get_next_line(int fd);
int					ft_isspace(char c);
long				ft_atol(const char *str);

// ft_fprintf
int					ft_print_digit_fd(int fd, long n, int base);
int					ft_print_un_digit_fd(int fd, unsigned long n);
int					ft_print_maj_digit_fd(int fd, long n, int base);
int					ft_print_char_fd(int fd, int c);
int					ft_print_str_fd(int fd, char *str);
int					ft_ptr_len(uintptr_t num);
int					ft_print_addr_fd(int fd, unsigned long long ptr);
int					print_format_fd(int fd, char specifier, va_list ap);
int					ft_fprintf(int fd, const char *format, ...);

#endif
