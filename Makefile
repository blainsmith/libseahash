CC = gcc
CFLAGS = -Wall
NAME = seahash

VERSION := 01

UNAME_S := $(shell uname -s)

SRCDIR := ./src
TSTDIR := ./tests
INCDIR := /usr/local/include

ifeq ($(UNAME_S),Linux)
$(NAME).$(VERSION).so:
	$(CC) -shared -o $(NAME).$(VERSION).so $(SRCDIR)/$(NAME).c $(CFLAGS)
endif
ifeq ($(UNAME_S),Darwin)
$(NAME).$(VERSION).dylib:
	$(CC) -dynamiclib -o $(NAME).$(VERSION).dylib $(SRCDIR)/$(NAME).c $(CFLAGS)
endif

.PHONY: install
install: 
	cp $(SRCDIR)/$(NAME).h $(INCDIR)
ifeq ($(UNAME_S),Linux)
	cp $(NAME).$(VERSION).so $(INCDIR)
endif
ifeq ($(UNAME_S),Darwin)
	cp $(NAME).$(VERSION).dylib $(INCDIR)
endif

uninstall:
	rm -f $(INCDIR)/$(SRCDIR)/$(NAME).h
ifeq ($(UNAME_S),Linux)
	rm -f $(INCDIR)/$(NAME).$(VERSION).so
endif
ifeq ($(UNAME_S),Darwin)
	rm -f $(INCDIR)/$(NAME).$(VERSION).dylib
endif

.PHONY:
test: clean
	$(CC) -o $(TSTDIR)/$(TSTDIR) $(TSTDIR)/$(TSTDIR).c $(SRCDIR)/seahash.c $(TSTDIR)/unity/unity.c $(CFLAGS)
	$(TSTDIR)/$(TSTDIR)
	rm -f $(TSTDIR)/$(TSTDIR)

.PHONY: clean
clean:
	rm -f $(TSTDIR)/$(TSTDIR)
