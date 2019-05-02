SYNTH   =   synth
CC      =   clang++
CFLAGS  =  -Ilib/STK/src 
CFLAGS  += -Ilib/lexertk
CFLAGS  += -std=c++14
DEFS    =  -DHAVE_GETTIMEOFDAY -D__MACOSX_CORE__
DEFS    += -D__LITTLE_ENDIAN__
LIBS    =  -lstk

SRCFOLDER = Synth/src
OBJFOLDER = Synth/obj

STRUCTURE := $(shell find $(SRCFOLDER) -type d) 

CODEFILES := $(addsuffix /*,$(STRUCTURE))
CODEFILES := $(wildcard $(CODEFILES))



SRCFILES := $(filter %.cpp,$(CODEFILES))
HDRFILES := $(filter %.h,$(CODEFILES))
OBJFILES := $(subst $(SRCFOLDER),$(OBJFOLDER),$(SRCFILES:%.cpp=%.o))

compile: $(OBJFILES)

$(OBJFOLDER)/%.o: $(addprefix $(SRCFOLDER)/,%.cpp %.h)
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFS) $(LIBS)



