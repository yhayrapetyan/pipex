SRC =	pipex.c

HEADERS = 	pipex.h

SRC_DIR = ./src/
INC = ./includes/

HEADERS := $(addprefix $(INC), $(HEADERS))
SRC := $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRC:.c=.o)

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
	@$(RM) $(OBJS)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

re: fclean all
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

print_info: print_name
	@printf "%b" "$(BLUE)Compiler: $(GREEN)$(CC)\n"
	@printf "%b" "$(BLUE)Name: $(GREEN)$(NAME)\n"
	@printf "%b" "$(BLUE)Uname: $(GREEN)$(UNAME)\n"
	@printf "%b" "$(BLUE)C Flags: $(GREEN)$(CFLAGS)\n"
	@printf "%b" "$(BLUE)Lib Flags: $(GREEN)$(LIB_FLAGS)\n"
	@printf "%b" "$(BLUE)Src Count: $(GREEN)$(SRC_COUNT_TOT)\n"


print_name:
	@printf "%b" "$(BLUE)"
	@echo "     ____     ______   ____      ____       __   __      "
	@echo "    /\  _\`\\  /\__  _\ /\  _ \`\\  /\ ___\\    /\ \ /\ \     "
	@echo "    \ \ \L\ \\/_/\ \/ \ \ \L\ \  \\ \\___/_   \ \\\/\'/\'    "
	@echo "     \ \ ,__/   \ \ \  \ \ ,__/  \ \____/   \\/ > <      "
	@echo "      \ \ \/     \_\ \__\ \ \/    \ \\_____    \/'/\`\\   "
	@echo "       \ \_\     /\_____\\ \_\      \ \\____\\  /\_\\  \_\ "
	@echo "        \/_/     \/_____/ \/_/      \/___ /  \/_/ \/_/ "
	@echo ""

.PHONY: all clean fclean re sanitize bonus print_name print_info
