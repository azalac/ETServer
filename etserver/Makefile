
COMMON=$(realpath ../common)

CC=gcc

PROJ=etserver
SRC=src
INC=inc
OBJ=obj
BIN=bin

EXTENSIONS := c s

DIRS=$(sort $(SRC) $(INC) $(OBJ) $(BIN))

SRCS=$(shell find $(SRC) -name "*.[$(EXTENSIONS)]")

OBJ_EXT=o

OBJS=$(patsubst $(SRC)/%,$(OBJ)/%,$(SRCS))

$(eval $(foreach ext,$(EXTENSIONS),OBJS=$(patsubst %.$(ext),%.$(OBJ_EXT),$(OBJS))))

CFLAGS = -Wall -g $(addprefix -I ,$(INC))
LDFLAGS = $(CFLAGS) -std=c99 -Os
LIBS = 

#don't add common lib if project is common, or if common doesn't exist
ifneq (,$(wildcard $(COMMON)))
ifneq '$(PROJ)' 'common'
CFLAGS += -I $(COMMON)/inc
LIBS += -L$(COMMON)/bin -lcommon  -lpthread
endif
endif

.PHONY: all clean

all: $(DIRS) $(PROJ)

clean:
	find ./$(OBJ) -iname "*.obj" | xargs -r rm
	find ./ -iname "*~" | xargs -r rm
	rm -f $(BIN)/$(PROJ)

$(DIRS):
	mkdir -p $@

$(PROJ): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)/$(PROJ) $(LIBS)
  
$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

#Params:
#	name:	The filename
#	folder: The folder to put it in
#Adds a file to the project directory, with some bash magic to automatically add
#	file headers and other stuff 
add%: %
#resolve the full file path
	$(eval fpath=$(shell readlink -m ./$^/$(name)))
#resolve the file extension & copy the template file
	$(eval ext=$(shell echo $(name) | grep --color=none -oP "(?<=\\.)\\w+"))
	cp ../default_$(ext) $(fpath)
#replace certain statements in the file (mainly used in the header comment)
	sed -i "s|{DATE\}|`date +%d-%m-%Y`|g" "$(fpath)"
	sed -i "s|{PROJ\}|$(PROJ)|g" "$(fpath)"
	sed -i "s|{FILE\}|`echo $(name) | xargs`|g" "$(fpath)"
	sed -i "s|{GUARD\}|`echo $(name) | tr [a-z./] [A-Z__]`|g" "$(fpath)"


