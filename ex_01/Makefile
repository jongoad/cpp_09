#--------------------------------#
#    Name and file information   #
#--------------------------------#
NAME			:= RPN


CPP_FILES		:= main.cpp RPN.cpp

#---------------------------------------------------------#
#   Directory information and object directory building   #
#---------------------------------------------------------#
INC				:= ./include

SRC_DIR			= ./src
SRCS			= $(addprefix $(SRC_DIR)/, $(CPP_FILES))

OBJ_DIR			= ./obj
OBJS			= $(addprefix $(OBJ_DIR)/, $(CPP_FILES:.cpp=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo Compiling $@
	@$(CC) $(CFLAGS) -o $@ -c $<

#--------------------------------#
#  Compiler settings and flags   #
#--------------------------------#
CC				= c++
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -Wshadow -Wno-shadow -std=c++98 -I./include

#--------------------------------#
#   Makefile rules and targets   #
#--------------------------------#

all:			$(NAME)
				@echo Done.

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:			
				@$(RM) $(OBJ_DIR)
				@echo Clean complete.

fclean:			clean
				@$(RM) $(NAME)
				@echo Full clean complete.

re:				fclean $(NAME)

.PHONY:			all clean fclean re