CC = gcc
RM = rm -rf
CFLAGS = -fsanitize=address -g3
# source global
SRC = src/main.c
# source for parcer
PSRC = parc.c tokenize.c U_tokenize.c U_get_errors.c get_errors.c to_exec.c utils1.c utils2.c utils3.c
# source for execute
ESRC = accessible.c cd.c change_val.c exec_func.c exit_pwd.c exp_env.c export_utils.c export_utils2.c export.c freeing.c  l_l_utils.c heredoc.c pipeline.c unset.c utils1.c utils2.c
# This two line are added just to add the path of our .c files
# u can see that we have exection.c file that u created so instead
# of add to every fil                                                                                                                                                                                                                                                                                              e its pathe /src/exec/exection.c we just shoudl
# to add the file itself and this two lines will add the path so i 
# have my parcing src and u have ur execution src just add ur files in ESRC
# ->
PSRC := $(addprefix src/parc/, $(PSRC))
ESRC := $(addprefix src/exec/, $(ESRC))
#  >-

LIBFT = utils/libft/libft.a

OBJ =  $(PSRC:%c=%o) $(ESRC:%c=%o) $(SRC:%c=%o)

NAME = minishell
 
all: $(LIBFT) $(OBJ) $(NAME)
	
$(LIBFT):
	$(MAKE) -C utils/libft CC=$(CC) -s >/dev/null

$(NAME) :
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)  -o $(NAME) -lreadline

m :
	@echo "removing object files"
	@$(RM) $(OBJ) 
	@$(MAKE) -C utils/libft fclean -s >/dev/null

fclean: m
	@echo "removing executable file"
	@$(RM) $(NAME)

re: fclean all m


#look at readme.md