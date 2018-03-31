# Related directories.
SACHOME  := /opt/sac-101.6
SACHOME2 := /opt/sac

# Compile parameters & dirs.
COMP     := gcc -Wall -Wimplicit -fPIC
INCDIR   := -I. -I/opt/local/include -I$(SACHOME)/include -I$(SACHOME2)/include
LIBDIR   := -L. -L/opt/local/lib -L$(SACHOME)/lib -L$(SACHOME2)/lib
LIBS     := -lASU_tools -lsac -lsacio -lgsl -lgslcblas -lfftw3 -lm

# function files
SRCFILES := $(wildcard *.fun.c)
DEPFILES := $(patsubst %.c, %.d, $(SRCFILES))
OBJS     := $(patsubst %.c, %.o, $(SRCFILES))

# example program files under $(EGDIR)
EGDIR    := ./Examples
EGFILES  := $(wildcard $(EGDIR)/*.c)
EGEXECS  := $(patsubst %.c, %.out, $(EGFILES))
EGDEPS   := $(patsubst %.c, %.d, $(EGFILES))

all: libASU_tools.a $(OBJS)
	@echo > /dev/null

examples: libASU_tools.a $(EGEXECS)
	@echo > /dev/null

# resolve dependencies automatically.
-include $(DEPFILES) $(EGDEPS)

libASU_tools.a: $(OBJS)
	ar cr libASU_tools.a $(OBJS)

%.o: %.c
	$(COMP) -MMD -MP -c $< -o $@ $(INCDIR)

$(EGDIR)/%.out: $(EGDIR)/%.o
	$(COMP) -MMD -MP $< -o $@ $(INCDIR) $(LIBDIR) $(LIBS)

clean:
	rm -f *.d *.o libASU_tools.a $(EGDIR)/*.d $(EGDIR)/*.out $(EGDIR)/*.o
