#----------------------------------------------------------------------
# Makefile
# for sqmml ( C/CPP 混合ソース対応版 )
#
# since 2016/12/01
#
#----------------------------------------
# history
#----------------------------------------
#   v0.01[2016/12/01]  ...  base create. [ boldowa ]
#----------------------------------------------------------------------
#CLANG=1

ifdef CLANG
	CC_PRG= clang
	CXX_PRG= clang++
else
	CC_PRG= gcc
	CXX_PRG= g++
endif

PLATFORM := unix
ifdef WIN32
	BINPREFIX := .exe
	PLATFORM_ := windows
ifdef x64
	PLATFORM := $(addsuffix /x64,$(PLATFORM_))
	PREFIX := x86_64-w64-mingw32-
else
	PLATFORM := $(addsuffix /x86,$(PLATFORM_))
	PREFIX := i686-w64-mingw32-
	LDFLAGS += -m32
endif
endif

#----------------------------------------
# Compile Option
#----------------------------------------
CC		:= $(PREFIX)$(CC_PRG)
CXX		:= $(PREFIX)$(CXX_PRG)

# Include header ... 
#CXXFLAGS	+= -Isrc/DLLcode -Isrc/n2
CXXFLAGS	+= -std=c++11

# precompile header
PRECOMPILE_HEADER := gstdafx.h


#----------------------------------------
# Link Option
#----------------------------------------
LD		= ${CXX}
LDFLAGS		:= --static
#LDFLAGS	+= -Wl,--gc-sections -Wl,--no-define-common -Wl,--discard-all


#----------------------------------------
# Target option
#----------------------------------------
TARGETS = akmml


#--------------------------------------------------
# Main ...
#--------------------------------------------------

.PHONY: all clean 

# compile option & dest dir
buildtype := release
ifeq ($(buildtype),release)
  CXXFLAGS += -O2 -ffast-math
  LDFLAGS  += -s
else ifeq ($(buildtype),debug)
  CXXFLAGS += -O0 -Wall
else
  $(error buildtype is illegal.)
endif
OUTDIR := build/$(buildtype)/$(PLATFORM)


# Compile program
define build-rule
$1_cppsrc := $$(wildcard src/$1/*.cpp)
$1_csrc := $$(wildcard src/$1/*.c)
ifdef PRECOMPILE_HEADER
$1_pch := $$(wildcard src/$1/$$(PRECOMPILE_HEADER))
$1_gch := $$(OUTDIR)/obj/$$($1_pch).gch
endif
-include $$($1_cppsrc:%.cpp=$$(OUTDIR)/obj/%.d)
-include $$($1_csrc:%.c=$$(OUTDIR)/obj/%.d)
$$(OUTDIR)/bin/$1: $$($1_gch) $$($1_cppsrc:%.cpp=$$(OUTDIR)/obj/%.o) $$($1_csrc:%.c=$$(OUTDIR)/obj/%.o)
	@if [ ! -e `dirname $$@` ]; then mkdir -p `dirname $$@`; fi;
	$$(CXX) $$(LDFLAGS) -o $$@$(BINPREFIX) $$(filter %.o,$$^)
src/$1/tags: $$($1_pch) $$($1_cppsrc) $$($1_csrc)
	@if which ctags >/dev/null ; then \
	echo -n "Making tags file ... " ;\
	cd `dirname $$@` ;\
	ctags -R ;\
	echo "done";\
	fi
endef


#----------------------------------------
# build
#----------------------------------------
all: $(foreach i,$(TARGETS),$(OUTDIR)/bin/$i) $(foreach i,$(TARGETS),src/$i/tags)

$(foreach i,$(TARGETS),$(eval $(call build-rule,$i)))

# cpp sources
$(OUTDIR)/obj/%.o:%.cpp Makefile
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

# c sources
$(OUTDIR)/obj/%.o:%.c Makefile
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

# precompile header
$(OUTDIR)/obj/%.h.gch:%.h Makefile
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ $<


#----------------------------------------
# etc...
#----------------------------------------
clean:
	rm -rf ${OUTDIR}
distclean:
	rm -rf build

# debug build
debug:
	make buildtype=debug

