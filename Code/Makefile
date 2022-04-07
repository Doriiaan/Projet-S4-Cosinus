# Specific part of the Makefile
EXEC=os_program


CC=gcc	# compilateur
CFLAGS=-Werror -Wextra -Wall	# options compilateur
LDFLAGS=	# edition de lien
SRC= $(wildcard *.c)	# fichiers .c
OBJ= $(SRC:.c=.o)	# fichiers .o -> fichiers.c


ifeq ($(DEBUG),yes)	#mode debug=yes
	CFLAGS += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(EXEC)


%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)


$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)


.PHONY: clean mrproper

clean:
	@rm -rf *.o


mrproper: clean
	@rm -rf $(EXEC)

doc: $(DOC)
	@doxygen ../Documentation/dconfig

deliver: mrproper
	cd ../../ ; zip -r Projet-S4-Cosinus.zip Projet-S4-Cosinus
