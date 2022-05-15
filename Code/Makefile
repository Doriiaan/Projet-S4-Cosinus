# Specific part of the Makefile
EXEC=os_program


CC=gcc	# compilateur
CFLAGS=-Werror -Wextra -Wall	# options compilateur
LDFLAGS=	# edition de lien

SRC = $(filter-out Installeur.c, $(wildcard *.c)) #fichier.c except Installeur.c
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

install:
	@$(CC) Couche1.c Couche2.c Couche3.c Couche4.c Installeur.c sha256_utils.c sha256.c time_stamp.c term_canon.c affichage_logo.c -o install $(LDFLAGS) $(CFLAGS)
	@mv install ..

mrproper: clean
	@rm -rf $(EXEC)
	@rm -rf ../install

doc: $(DOC)
	@doxygen ../Documentation/dconfig

deliver: mrproper
	cd ../../ ; zip -r Projet-S4-Cosinus.zip Projet-S4-Cosinus
