SYNTH   =   synthlan
CC      =   g++
CFLAGS  =  -Ilib/STK/src 
CFLAGS  += -Ilib/lexertk
CFLAGS  +=  -framework CoreAudio -framework CoreFoundation
CFLAGS  += -std=c++14 -Wall
DEFS    =  -DHAVE_GETTIMEOFDAY -D__MACOSX_CORE__
DEFS    += -D__LITTLE_ENDIAN__
LIBS    =  -L./lib/STK/src -lstk

SRCFOLDER = Synth/src
OBJFOLDER = Synth/obj

STRUCTURE := $(shell find $(SRCFOLDER) -type d) 

CODEFILES := $(addsuffix /*,$(STRUCTURE))
CODEFILES := $(wildcard $(CODEFILES))

SRCFILES := $(filter %.cpp,$(CODEFILES))
HDRFILES := $(filter %.h,$(CODEFILES))
OBJFILES := $(subst $(SRCFOLDER),$(OBJFOLDER),$(SRCFILES:%.cpp=%.o))

compile: $(OBJFILES)
	$(CC) $(OBJFILES) -o $(SYNTH) $(LIBS) $(CFLAGS)

$(OBJFOLDER)/%.o: $(addprefix $(SRCFOLDER)/,%.cpp %.h) makefolders
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFS) $(LIBS)

makefolders:
	mkdir $(OBJFOLDER)
	mkdir $(OBJFOLDER)/lexer
	mkdir $(OBJFOLDER)/streams

clean:
	-rm -r $(OBJFOLDER)