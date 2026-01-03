# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 19:19:07 by edelplan          #+#    #+#              #
#    Updated: 2024/10/18 15:16:57 by edelplan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS_DIR = srcs
INCLUDE_DIR = include
SRCS = $(SRCS_DIR)/ft_atoi.c $(SRCS_DIR)/ft_bzero.c $(SRCS_DIR)/ft_calloc.c $(SRCS_DIR)/ft_int_len_base.c \
	$(SRCS_DIR)/ft_isalnum.c $(SRCS_DIR)/ft_isalpha.c $(SRCS_DIR)/ft_isascii.c $(SRCS_DIR)/ft_isdigit.c \
	$(SRCS_DIR)/ft_isprint.c $(SRCS_DIR)/ft_itoa_base.c $(SRCS_DIR)/ft_itoa.c $(SRCS_DIR)/ft_lstadd_back.c \
	$(SRCS_DIR)/ft_lstadd_front.c $(SRCS_DIR)/ft_lstclear.c $(SRCS_DIR)/ft_lstdelone.c $(SRCS_DIR)/ft_lstiter.c \
	$(SRCS_DIR)/ft_lstlast.c $(SRCS_DIR)/ft_lstmap.c $(SRCS_DIR)/ft_lstnew.c $(SRCS_DIR)/ft_lstsize.c $(SRCS_DIR)/ft_memchr.c \
	$(SRCS_DIR)/ft_memcmp.c $(SRCS_DIR)/ft_memcpy.c $(SRCS_DIR)/ft_memmove.c $(SRCS_DIR)/ft_memset.c $(SRCS_DIR)/ft_printf.c \
	$(SRCS_DIR)/ft_printf_utils.c $(SRCS_DIR)/ft_putchar_fd.c $(SRCS_DIR)/ft_putendl_fd.c $(SRCS_DIR)/ft_putnbr_base_fd.c \
	$(SRCS_DIR)/ft_putnbr_fd.c $(SRCS_DIR)/ft_putstr_fd.c $(SRCS_DIR)/ft_split.c $(SRCS_DIR)/ft_strchr.c $(SRCS_DIR)/ft_strdup.c \
	$(SRCS_DIR)/ft_striteri.c $(SRCS_DIR)/ft_strjoin.c $(SRCS_DIR)/ft_strlcat.c $(SRCS_DIR)/ft_strlcpy.c $(SRCS_DIR)/ft_strlen.c \
	$(SRCS_DIR)/ft_strmapi.c $(SRCS_DIR)/ft_strncmp.c $(SRCS_DIR)/ft_strnstr.c $(SRCS_DIR)/ft_strrchr.c $(SRCS_DIR)/ft_strtrim.c \
	$(SRCS_DIR)/ft_substr.c $(SRCS_DIR)/ft_tolower.c $(SRCS_DIR)/ft_toupper.c $(SRCS_DIR)/get_next_line.c $(SRCS_DIR)/ft_isspace.c $(SRCS_DIR)/ft_strcmp.c \
	$(SRCS_DIR)/ft_fprintf.c $(SRCS_DIR)/ft_fprintf_utils.c $(SRCS_DIR)/ft_fprintf_utils_2.c $(SRCS_DIR)/ft_atol.c

OBJS = ${SRCS:.c=.o}
RM = rm -f
AR = ar -rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I${INCLUDE_DIR}
WHITE = \033[0;37m
GREEN = \033[0;32m
CYAN = \033[0;36m

.c.o:
	@echo -n "${WHITE}Compiling $< : "
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	@echo "${GREEN}Done!"

${NAME}: ${OBJS}
	@echo -n "${WHITE}Archiving the library : "
	@${AR} ${NAME} ${OBJS}
	@echo "${GREEN}Done!"
	@echo "📚📚📚 LIBFT COMPILED! 📚📚📚"

all: ${NAME}

clean:
	@echo -n "${WHITE}Cleaning libft objects files : "
	@sleep 0.1
	@${RM} ${OBJS}
	@echo "${GREEN}Done!"

fclean: clean
	@echo -n "${WHITE}Cleaning archive $< : "
	@sleep 0.1
	@${RM} ${NAME}
	@echo "${GREEN}Done!"


re: fclean all

.PHONY: all clean fclean re

##INCLUDE = -I . si #include <libft.h> et pas #include "libft.h"
