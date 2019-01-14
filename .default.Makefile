
-include Makefile.cfg

COMMON=$(realpath ../common)

CC=gcc

PROJ={PROJ}
SRC=src
INC=inc
OBJ=obj
BIN=bin

DIRS=$(sort $(SRC) $(INC) $(OBJ) $(BIN))

CFLAGS = -Wall -g $(addprefix -I ,$(INC)) $(INC_CFLAGS)
LDFLAGS = $(CFLAGS) -std=c99 -Os $(INC_LDFLAGS)
LIBS = $(INC_LIB)

EXTENSIONS := c s $(INC_SRC_EXT)

OBJ_EXT=o

#load each src type into a variable called SRCS_[ext name]
$(eval $(foreach ext,$(EXTENSIONS),$(eval \
SRCS_$(ext):=$(shell find $(SRC) -name "*.$(ext)")\
)))

#helper function to convert src/foo.[ext] to obj/foo.o 
define do_obj_path
    $(eval lst=$$($(2)))
    $(eval $(1) := $(patsubst $(SRC)%,$(OBJ)%,$(patsubst %$(3),%$(OBJ_EXT),$(lst))))
endef

#convert each src path into an obj path
$(eval $(foreach ext,$(EXTENSIONS),$(eval \
$(call do_obj_path, OBJS_$(ext),SRCS_$(ext),$(ext)) \
)))

#put all srcs and objs into one variable
$(eval $(foreach ext,$(EXTENSIONS),$(eval SRCS := $(SRCS) $$(SRCS_$(ext)))))
$(eval $(foreach ext,$(EXTENSIONS),$(eval OBJS := $(OBJS) $$(OBJS_$(ext)))))

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
	find ./$(OBJ) -iname "*.$(OBJ_EXT)" | xargs -r rm
	find ./ -iname "*~" | xargs -r rm
	rm -f $(BIN)/$(PROJ)

$(DIRS):
	mkdir -p $@

$(PROJ): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)/$(PROJ) $(LIBS)
  
$(OBJ)/%.$(OBJ_EXT): $(SRC)/%.c
	@mkdir -p $(dir $@)
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
