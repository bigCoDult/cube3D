NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
RM = rm -rf
INC = -I.
SRC = \
      ./ft_isdigit.c \
      ./ft_isalpha.c \
      ./ft_isalnum.c \
      ./ft_isprint.c \
      ./ft_isascii.c \
      ./ft_toupper.c \
      ./ft_tolower.c \
      ./ft_strlen.c \
      ./ft_memset.c \
      ./ft_bzero.c \
      ./ft_memcpy.c \
      ./ft_memmove.c \
      ./ft_strlcpy.c \
      ./ft_strlcat.c \
      ./ft_strchr.c \
      ./ft_strrchr.c \
      ./ft_strncmp.c \
      ./ft_memchr.c \
      ./ft_memcmp.c \
      ./ft_strnstr.c \
      ./ft_atoi.c \
      ./ft_calloc.c \
      ./ft_strdup.c \
      ./ft_substr.c \
      ./ft_strjoin.c \
      ./ft_strtrim.c \
      ./ft_split.c \
      ./ft_itoa.c \
      ./ft_strmapi.c \
      ./ft_striteri.c \
      ./ft_putendl_fd.c \
      ./ft_putnbr_fd.c \
      ./ft_lstnew.c \
      ./ft_putchar_fd.c \
      ./ft_putstr_fd.c \
      ./ft_printf.c \
      ./ft_printfutils.c \
      ./ft_lstsize.c \
      ./ft_lstnew.c \
      ./ft_lstadd_front.c \
      ./ft_lstadd_back.c \
      ./ft_lstlast.c \
      ./ft_lstdelone.c \
      ./ft_lstclear.c \
      ./ft_lstiter.c \
      ./ft_lstmap.c \
	  ./template_literal.c \
	  ./file_to_str.c \
	  ./ft_endwith.c \
	  ./is_int_str.c \
      
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
