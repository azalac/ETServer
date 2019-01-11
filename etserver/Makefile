
COMMON=$(realpath ../common)

CC=cc

PROJ=common
SRC=src
INC=inc
OBJ=obj
BIN=bin

SRCS=$(shell find $(SRC) -name "*.c" -exec basename {} \;)
OBJS=$(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(SRCS))))
DIRS=$(sort $(SRC) $(INC) $(OBJ) $(BIN))

CFLAGS = -Wall -g $(addprefix -I ,$(INC)) -fPIC
LDFLAGS = $(CFLAGS) -std=c99 -Os
LIBS = 

#don't add common lib if project is common
ifneq '$(PROJ)' 'common'
CFLAGS += -I $(COMMON)/$(INC)
LIBS += -L$(COMMON)/$(BIN) -lcommon 
endif

.PHONY: all clean

all: $(DIRS) $(PROJ)

clean:
	find ./$(OBJ) -iname "*.obj" | xargs -r rm
	find ./ -iname "*~" | xargs -r rm
	rm -f $(BIN)/lib$(PROJ).a

$(DIRS):
	mkdir -p $@

$(PROJ): $(OBJS)
#	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)/$(PROJ) $(LIBS)
#generates a static library from the object files
	ar rcs $(BIN)/lib$(PROJ).a $(OBJS)
  
$(OBJ)/%.obj: $(SRC)/%.c
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


