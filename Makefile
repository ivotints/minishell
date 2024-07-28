# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 16:23:26 by ivotints          #+#    #+#              #
#    Updated: 2024/07/28 22:32:36 by ivotints         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror
LDLIBS	= -lreadline -lft
LDFLAGS	= -L./libft
OBJ_DIR	= obj
OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	= 00main.c 01init_minienv.c 02minishell.c 03signal_handler.c \
		04prompt_input.c 05free_minienv.c 06trim_spaces.c 07input_error.c \
		08redirect_error.c 09empty_pipe.c 10heredoc_handler.c 11exec_heredoc.c \
		12read_heredoc.c 13expand_input.c 14has_pipe.c 15one_command.c \
		16handle_redirects.c 17handle_input.c 18handle_output.c \
		19redirect_heredoc.c 20split_av.c 21is_builtin.c 22echo.c 23pwd.c \
		24env.c 25builtin_export.c 26minienv_update.c 27unset.c 28cd.c \
		29builtin_exit.c 30exec_fork_extern.c 31execute_external.c 32getpath.c \
		33minienv_to_envp.c 34split_commands.c 35multiple_commands.c \
		36handle_pipe.c 37handle_child_redir.c 38execute_fork_cmd.c \
		39print_error_msg.c 40wait_for_children.c



LIBFT_A	= ./libft/libft.a
HEADER	= minishell.h

all: $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)
	@echo $(NAME) done

$(LIBFT_A):
	make -C libft

$(OBJ_DIR):
	@mkdir -p $@

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo removed $(OBJ_DIR) folder

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo removed $(NAME)

re: fclean all

.PHONY: all run clean fclean re
