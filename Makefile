NAME = libftprintf.a

CC_FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

SRCS =	ft_printf.c				\
		ft_vformatf.c			\
		ft_formatf.c			\
		struct_functions.c		\
		ft_check_all.c			\
		ft_formating.c			\
		ft_gets_s_c_p.c			\
		ft_gets_i_d.c			\
		ft_gets_u_x.c			\
		flags_formating.c		\
		flags_formating2.c		\
		ft_check_errors.c		\
		flags_pointer.c		


OBJS = $(SRCS:.c=.o)
	

all: $(NAME)
	make clean

$(NAME): $(OBJS) $(LIBFT) 
	cp libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

$(LIBFT):
	make -C ./libft


$(OBJS):
	gcc $(CC_FLAGS) -I./headers -c $(addprefix ./files/,$(SRCS))


clean: 
	rm -f $(OBJS) $(LIBFT_OBJS)
	make clean -C ./libft

fclean: clean 
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

bonus: all

gdb:
	gcc -g3 -I ./headers main.c $(addprefix ./files/,$(SRCS)) -L ./libft -lft 

git: 
	git add .
	git commit -m final
	git push

update: 
	git pull
#valgrind --show-leak-kinds=all --track-origins=yes  --leak-check=full  
.PHONY: all clean fclean re bonus gdb
