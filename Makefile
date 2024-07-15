################################################################################
#                                     CONFIG                                   #
################################################################################

NAME	:= minishell
CC		:= gcc
FLAGS	:= -g -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS		:=	main.c \
				srcs/builtins/env_ops.c \
				srcs/builtins/get_envp.c \
				srcs/builtins/m_builtins.c \
				srcs/builtins/m_cd.c \
				srcs/builtins/m_echo.c \
				srcs/builtins/m_env.c \
				srcs/builtins/m_exit.c \
				srcs/builtins/m_export.c \
				srcs/builtins/m_unset.c \
				srcs/builtins/pwd.c \
				srcs/cleaners/cleaners.c \
				srcs/execution/exec.c \
				srcs/execution/find_exec.c \
				srcs/execution/handle_args.c \
				srcs/lexer/syntax_errors/syntax_error.c \
				srcs/lexer/syntax_errors/unclosed_quotes.c \
				srcs/lexer/lexer.c \
				srcs/lexer/split_tokens.c \
				srcs/lexer/token_types.c \
				srcs/parser/cmds.c \
				srcs/parser/env_expand.c \
				srcs/redirects/heredoc.c \
				srcs/redirects/redirects.c \
				srcs/utils/ft_split.c \
				srcs/utils/print.c \
				srcs/utils/str_utils.c \
				srcs/utils/str_utils2.c \
				srcs/utils/utils.c

OBJS		:= $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN		:= \033[1;36m
RM			:= rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} -lreadline
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o */*/*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

cleanly:	all clean

.PHONY:		all clean fclean re cleanly bonus
