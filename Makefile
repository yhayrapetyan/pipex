SRC =			get_descriptor.c \
                in_processes.c \
                out_process.c \
                pipex_bonus.c \
                here_dock.c

HELPERS_SRC = 	ft_strjoin.c \
				ft_strstr.c \
				ft_error.c \
				ft_strncmp.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strlen.c \
				ft_strndup.c \
				free_split.c \
				execute.c \
				is_quote.c \
				clean_and_exit.c \
				get_built_in_args.c \
				clean_vars.c \
				ft_split.c\
				ft_strcmp.c

PARSING_SRC =	get_quotes_content.c \
				get_joined_name.c \
                get_args.c \
                get_bin_path.c \
                get_path.c \
                get_command_with_options.c \
                init_vars.c \
                quotes_parse.c \
                remove_back_slash.c \
                simple_parse.c

GNL_SRC =		get_next_line_utils.c \
				get_next_line.c

VALIDATION_SRC = 	check_command_access.c

HEADERS = 	pipex_utils.h \
			pipex.h

SRC_DIR = ./src/main/
HELPERS_DIR = ./src/helpers/
VALIDATION_DIR = ./src/validation/
PARSING_DIR = ./src/parsing/
GNL_DIR = ./src/get_next_line/
INC = ./includes/

HEADERS := $(addprefix $(INC), $(HEADERS))
SRC := $(addprefix $(SRC_DIR), $(SRC))
VALIDATION_SRC := $(addprefix $(VALIDATION_DIR), $(VALIDATION_SRC))
HELPERS_SRC := $(addprefix $(HELPERS_DIR), $(HELPERS_SRC))
PARSING_SRC := $(addprefix $(PARSING_DIR), $(PARSING_SRC))
GNL_SRC := $(addprefix $(GNL_DIR), $(GNL_SRC))
OBJS = $(SRC:.c=.o)

SRC += $(VALIDATION_SRC)
SRC += $(HELPERS_SRC)
SRC += $(PARSING_SRC)
SRC += $(GNL_SRC)

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
RM = rm -f

BLUE   = \033[0;34m
GREEN    = \033[0;32m
RED = \033[0;31m
YELLOW  = \033[0;33m
NO_COLOR    = \033[m


SRC := $(shell printf "$(SRC)" | tr '\r' '\n')
SRC_COUNT_TOT := $(words $(SRC))
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

all: print_info $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@printf "%b" "$(BLUE)\n$@ $(GREEN)[✓]\n"

$(OBJS): $(HEADERS) Makefile

sanitize: $(OBJS)
	@cc $(OBJS) -fsanitize=address  -o $(NAME)

.c.o:
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@printf "\r%18s\r$(YELLOW)[ %d/%d (%d%%) ]$(NO_COLOR)" "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) -I $(INC) -c  $< -o $(<:.c=.o)

clean: print_name
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

re: fclean all
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

print_info: print_name
	@printf "%b" "$(BLUE)Compiler: $(GREEN)$(CC)\n"
	@printf "%b" "$(BLUE)Name: $(GREEN)$(NAME)\n"
	@printf "%b" "$(BLUE)C Flags: $(GREEN)$(CFLAGS)\n"
	@printf "%b" "$(BLUE)Src Count: $(GREEN)$(SRC_COUNT_TOT)$(NO_COLOR)\n"


print_name:
	@printf "%b" "$(BLUE)"
	@echo "     ____     ______   ____      _____      __   __      "
	@echo "    /\  _\`\\  /\__  _\ /\  _ \`\\  /\ ____\\   /\ \ /\ \     "
	@echo "    \ \ \L\ \\/_/\ \/ \ \ \L\ \  \\ \\----/   \ \\\/\'/\'    "
	@echo "     \ \ ,__/   \ \ \  \ \ ,__/  \ \===     \\/ > <      "
	@echo "      \ \ \/     \_\ \__\ \ \/    \ \\_____    \/'/\`\\   "
	@echo "       \ \_\     /\_____\\ \_\      \ \\____\\  /\_\\  \_\ "
	@echo "        \/_/     \/_____/ \/_/      \/___ /  \/_/ \/_/ "
	@echo "\n"

.PHONY: all clean fclean re sanitize print_name print_info
