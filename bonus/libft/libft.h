/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:10:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/20 15:49:31 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dynamic_array
{
	char	**arr;
	size_t	capacity;
	size_t	size;
}	t_dynamic_array;

typedef struct s_ht_item
{
	char	*key;
	char	*value;
}	t_ht_item;

typedef struct s_hash_table
{
	size_t		capacity;
	size_t		size;
	t_ht_item	*items;
}	t_hash_table;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_iswhitespace(char c);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char *nptr);
int				ft_atoi_base(char *str, char *base);
int				safe_atoi(const char *nptr, int *num);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *s, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*strjoin_and_free_s1(char *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_isincharset(char c, const char *charset);
char			**ft_split(char const *s, char c);
void			*ft_free_split(char **strs);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
int				ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *newlst);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *newlst);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst,
					void *(*f)(void *), void (*del)(void *));
char			*get_next_line(int fd);
int				ft_printf(const char *print, ...);
int				ft_dprintf(int fd, const char *print, ...);
int				ft_dputuint(int fd, unsigned int n);
int				ft_dputnbrcount(int fd, int n);
int				ft_dprintunsignedint(int fd, unsigned int n);
int				ft_dprintchar(int fd, char c);
int				ft_dprintstr(int fd, char *str);
int				ft_dprintvoidptr(int fd, uintptr_t ptr);
int				ft_dputulonglonghex(int fd, uintptr_t n);
int				ft_dputhexmaj(int fd, unsigned int n);
void			*ft_realloc(void *ptr, size_t old_size, size_t size);
int				ptr_array_len(char **ptr_array);
t_dynamic_array	init_dynamic_array(size_t size);
int				push_array(t_dynamic_array *darray, char *elem);
void			swap_int(int *a, int *b);
void			ft_quicksort(int *arr, int low, int high);
char			*ft_strndup(const char *s, size_t n);

void			free_1(void *arg1);
void			free_2(void *arg1, void *arg2);
void			free_3(void *arg1, void *arg2, void *arg3);
void			free_4(void *arg1, void *arg2, void *arg3, void *arg4);
void			*free_1_return_null(void *arg1);
void			*free_2_return_null(void *arg1, void *arg2);
void			*free_3_return_null(void *arg1, void *arg2, void *arg3);
void			*free_4_return_null(void *arg1, void *arg2, void *arg3,
					void *arg4);
int				free_1_return_0(void *arg1);
int				free_2_return_0(void *arg1, void *arg2);
int				free_3_return_0(void *arg1, void *arg2, void *arg3);
int				free_4_return_0(void *arg1, void *arg2, void *arg3, void *arg4);
int				free_1_return_1(void *arg1);
int				free_2_return_1(void *arg1, void *arg2);
int				free_3_return_1(void *arg1, void *arg2, void *arg3);
int				free_4_return_1(void *arg1, void *arg2, void *arg3, void *arg4);

typedef enum e_hash_mode
{
	MODE_REMOVE,
	MODE_DELETE
}	t_hash_mode;

int				table_insert(t_hash_table *table, char *key, char *value);
int				table_resize(t_hash_table *table);
void			table_delete_item(t_hash_table *table, int index);
void			table_delete_table(t_hash_table *table);
char			*table_search(t_hash_table *table, const char *key);
t_hash_table	*table_alloc(int capacity);
void			print_hash_table(t_hash_table *table);
int				table_hash_function(const char *key, const int len_table);
int				power(int nb, int exponent);
void			*table_delete_return_null(t_hash_table *table);
void			table_remove_item(t_hash_table *table, char *key,
					t_hash_mode mode, int index);
void			*table_delete_return_null(t_hash_table *table);

char			*ft_str_triple_join(char const *s1,
					char const *s2, char const *s3);

int				ft_strchr_index(const char *s, int c);
int				ft_strchr_last_index(const char *s, int c);

int				safe_atof(const char *s, float *f);
float			ft_atof(const char *s);

char			**split_better(char const *s, char c);

#endif
