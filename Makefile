
PROJS = $(shell cat projs.cfg)

cdir = $(shell basename `pwd`)

DEF_MAKEFILE = .default.Makefile

define parse_file
sed -i "s|{DATE}|`date +%d-%m-%Y`|g" $(1);
sed -i "s|{PROJ}|$(proj)|g" $(1);
sed -i "s|{FILE}|$(1)|g" $(1);
endef

ifeq ($(DEBUG),true)
	debug="debug=-D DEBUG"
endif

.PHONY: all $(PROJS) run clean

#makes all projects, and prefixes their make output with [project_name]:(space)
all:
	$(foreach proj, $(PROJS), make $(proj) $(debug) 2>&1 | xargs --delimiter='\n' -L 1 echo "[$(proj)]: $1";)

$(PROJS):
	cd $@; $(MAKE) all

clean:
	find ./ -name '*~' -exec rm {} \;
	$(foreach proj, $(PROJS), cd $(proj); make clean; cd ..;)

CLR/%: %
	cd $^; make clean

#Params:
#	regex:	The regex to find
find:
	@$(foreach file, $(shell find . -type f), grep -E -H -n "$(regex)" $(file); true;)

zip: clean
	cd .. ; tar -cvf $(cdir).tar $(cdir)/*

#Params:
#	proj:	The project name
update_makefile: $(proj)/Makefile
	cp $(DEF_MAKEFILE) $(proj)/Makefile
	$(call parse_file, $(proj)/Makefile)

#Params:
#	name:	The project name
addproj:
	mkdir -p $(name)
	sed -i~ '$ s|$$| $(name)|' projs.cfg
	mkdir -p $(addprefix $(name)/, src inc obj bin)
	cp $(DEF_MAKEFILE) $(name)/Makefile
	$(call parse_file, $(name)/Makefile)
