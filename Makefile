# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angela <angela@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 17:53:05 by angela            #+#    #+#              #
#    Updated: 2024/02/11 17:53:06 by angela           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


##-----ALIAS-----##

NAME = philo
SRC_DIR = src
OBJ_DIR = .objs

SRC		=	$(SRC_DIR)/ft_actions.c \
			$(SRC_DIR)/ft_errors.c \
			$(SRC_DIR)/ft_forks.c \
			$(SRC_DIR)/ft_philos.c \
			$(SRC_DIR)/ft_threads.c \
			$(SRC_DIR)/ft_time.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/ft_utils.c \
			$(SRC_DIR)/ft_routine.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC = gcc
HEAD = -I./include
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread
LFLAGS = -pthread
RM = /bin/rm -rf

NUM_FILES := $(words $(SRC))
CURRENT_FILE := 0
PERCENTAGE := 0

##-----RULES-----##

all:						$(NAME)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) $(HEAD) $(CFLAGS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@
		@$(eval CURRENT_FILE := $(shell echo $$(($(CURRENT_FILE) + 1))))
		@$(eval TMP := $(shell echo $$(($(CURRENT_FILE) * 100 / $(NUM_FILES)))))
		@$(eval PERCENTAGE := $(TMP))
		@printf "\r$$(tput setaf 2)[OK]$$(tput sgr0)    $$(tput setaf 44)Compiling    $$(tput sgr0)		["
		@printf "%-10s" "$$(for ((i=0; i < $(PERCENTAGE) / 10; i++)); do printf '#'; done)"
		@if [ $(CURRENT_FILE) -eq $(NUM_FILES) ]; then \
			printf "] $$(tput setaf 2)    $$(tput sgr0)  [100%%]\n"; \
		else \
			printf "] $$(echo $(CURRENT_FILE)/$(NUM_FILES) | awk '{printf "%-5s", $$0}') "; \
			printf "[%3d%%]\r" $(PERCENTAGE); \
		fi


clean:
		@$(RM) $(OBJ_DIR)
		@echo "$$(tput setaf 2)[OK]$$(tput sgr0)	$$(tput setaf 44)Removing objects$$(tput sgr0)"

fclean: clean
		@$(RM) $(NAME)
		@echo "$$(tput setaf 2)[OK]$$(tput sgr0)	$$(tput setaf 44)Removing program$$(tput sgr0)"

re: fclean all

.PHONY: all clean fclean re
