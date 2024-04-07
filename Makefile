SRC =			pipex.c \

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
				clean_vars.c \
				ft_split.c

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


BONUS_SRC =		get_descriptor.c \
                in_processes.c \
                out_process.c \
                pipex_bonus.c \
                here_dock.c

GNL_SRC =		get_next_line_utils.c \
				get_next_line.c

VALIDATION_SRC = 	check_command_access.c

HEADERS = 	pipex.h

SRC_DIR = ./src/
HELPERS_DIR = ./src/helpers/
VALIDATION_DIR = ./src/validation/
PARSING_DIR = ./src/parsing/
BONUS_DIR = ./src/bonus/
GNL_DIR = ./src/get_next_line/
INC = ./includes/

HEADERS := $(addprefix $(INC), $(HEADERS))
SRC := $(addprefix $(SRC_DIR), $(SRC))
VALIDATION_SRC := $(addprefix $(VALIDATION_DIR), $(VALIDATION_SRC))
HELPERS_SRC := $(addprefix $(HELPERS_DIR), $(HELPERS_SRC))
PARSING_SRC := $(addprefix $(PARSING_DIR), $(PARSING_SRC))
BONUS_SRC := $(addprefix $(BONUS_DIR), $(BONUS_SRC))
GNL_SRC := $(addprefix $(GNL_DIR), $(GNL_SRC))
OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)

SRC += $(VALIDATION_SRC)
SRC += $(HELPERS_SRC)
SRC += $(PARSING_SRC)

BONUS_SRC += $(VALIDATION_SRC)
BONUS_SRC += $(HELPERS_SRC)
BONUS_SRC += $(PARSING_SRC)
BONUS_SRC += $(GNL_SRC)

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
BONUS_NAME = pipex_bonus
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

#bonus: delete_old_pipex print_info  $(BONUS_NAME)

delete_old_pipex:
	@$(RM) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@printf "%b" "$(BLUE)\n$@ $(GREEN)[✓]\n"

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) -o $(NAME)
	@printf "%b" "$(BLUE)\n$@ $(GREEN)[✓]\n"

$(OBJS): $(HEADERS) Makefile
$(BONUS_OBJS): $(HEADERS) Makefile

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
	@printf "%b" "$(BLUE)Uname: $(GREEN)$(UNAME)\n"
	@printf "%b" "$(BLUE)C Flags: $(GREEN)$(CFLAGS)\n"
	@printf "%b" "$(BLUE)Lib Flags: $(GREEN)$(LIB_FLAGS)\n"
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

.PHONY: all clean fclean re sanitize bonus print_name print_info
