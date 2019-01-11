
PROJ_NAME := ETServer

SRC_DIR := src
INC_DIR := inc
BIN_DIR := bin
OBJ_DIR := obj

CFLAGS= -Wall -std=c11 -I$(INC_DIR)

ifeq '$(findstring ;,$(PATH))' ';'
	detected_OS := Windows
else
	detected_OS := $(shell uname 2>/dev/null || echo Unknown)
	detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
	detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
	detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
endif

ifeq ($(detected_OS),Windows)
	CFLAGS += -D WIN32
endif
ifeq ($(detected_OS),Darwin)	# Mac OS X
	CFLAGS += -D OSX
endif
ifeq ($(detected_OS),Linux)
	CFLAGS   +=   -D LINUX
endif
ifeq ($(detected_OS),GNU)	    # Debian GNU Hurd
	CFLAGS   +=   -D GNU_HURD
endif
ifeq ($(detected_OS),GNU/kFreeBSD)  # Debian kFreeBSD
	CFLAGS   +=   -D GNU_kFreeBSD
endif
ifeq ($(detected_OS),FreeBSD)
	CFLAGS   +=   -D FreeBSD
endif
ifeq ($(detected_OS),NetBSD)
	CFLAGS   +=   -D NetBSD
endif
ifeq ($(detected_OS),DragonFly)
	CFLAGS   +=   -D DragonFly
endif
ifeq ($(detected_OS),Haiku)
	CFLAGS   +=   -D Haiku
endif

.PHONY: all, clean

all: 
	