# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 11:33:27 by jrobert           #+#    #+#              #
#    Updated: 2021/07/08 11:54:41 by jrobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_S		= 	server.c
CLIENT_S		=	client.c
SERVER_O		= 	$(SERVER_S:%.c=%.o)
CLIENT_O		= 	$(CLIENT_S:%.c=%.o)
SERVER			=	server
CLIENT			=	client
LIBPATH 		= 	-L libft
LIB     		= 	-lft
CFLAGS			= 	-Wall -Wextra -Werror -I libft/includes
S_LDFLAGS 		= 	$(LIBPATH) $(LIB) -o $(SERVER)
C_LDFLAGS 		= 	$(LIBPATH) $(LIB) -o $(CLIENT)

all    			:	$(SERVER) $(CLIENT)
	
$(SERVER)		:	$(SERVER_O)
					$(MAKE) -C ./libft/
					gcc $(SERVER_O) $(S_LDFLAGS) 

$(CLIENT)		:	$(CLIENT_O)
					$(MAKE) -C ./libft/
					gcc $(CLIENT_O) $(C_LDFLAGS) 

clean 			:	
					rm -f $(SERVER_O) $(CLIENT_O)
					$(MAKE) clean -C ./libft/

fclean 			:	clean
					rm -f $(SERVER) $(CLIENT)
					$(MAKE) fclean -C ./libft/
					
re				:	fclean all

.PHONY			: 	all clean fclean re


