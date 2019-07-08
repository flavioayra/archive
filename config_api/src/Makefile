
# $Id: Makefile,v 1.4 2002/03/24 04:54:44 flv Exp $
#
# Copyright (C) 2001, 2002 Flavio de Ayra Mendes <h4@locked.org>
#

CC	= cc
AR	= ar -rc
RM	= rm -f 


OBJECT 	= config_api.o find.o utils.o
LIB	= libconfig_api.a

CFLAGS	= -O2 -Wall #-ggdb -g3

.SUFIXES: .c
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJECT)
	$(AR) $(LIB) $(OBJECT)

clean: 
	$(RM) $(OBJECT) $(LIB) 
