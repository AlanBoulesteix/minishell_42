/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:19:10 by marvin            #+#    #+#             */
/*   Updated: 2023/05/22 18:23:54 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FD_H
# define PRINTF_FD_H

# include <stdarg.h>

# define CONVERSION_NUMBER 9
# define PRINTF_BUFFER_SIZE 512

int		printf_fd(int fd, const char *format, ...);

typedef struct s_display_buffer {
	char	buffer[PRINTF_BUFFER_SIZE];
	int		offset;
	int		total_length;
}	t_display_buffer;

void	ft_write_buf(int fd, t_display_buffer *buf, char const *str, int len);

typedef void	(*t_fun_conv)(va_list *, t_display_buffer *buf, int fd);

void	ft_char_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_string_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_pointer_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_decimal_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_integer_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_unsigned_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_lower_hexa_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_upper_hexa_conv(va_list *args, t_display_buffer *buf, int fd);
void	ft_percent_conv(va_list *args, t_display_buffer *buf, int fd);

char	*ft_itoa(int n);
char	*ft_itoa_unsigned(unsigned int n);
void	ft_long_to_hexa(unsigned long long nbr, char *output, int i);
char	*ft_itoa_hexa(unsigned int n, int lower);

#endif
