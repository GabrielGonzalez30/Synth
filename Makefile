SYNTH   =   synthlan
CC      =   g++
CFLAGS  =  -Ilib/STK/src 
CFLAGS  += -Ilib/lexertk
CFLAGS  +=  -framework CoreAudio -framework CoreFoundation
CFLAGS  += -std=c++14
DEFS    =  -DHAVE_GETTIMEOFDAY -D__MACOSX_CORE__
DEFS    += -D__LITTLE_ENDIAN__
LIBS    =  -L./lib/STK/src -lstk

SRCFOLDER = Synth/src
OBJFOLDER = obj
BINFOLDER = bin

STRUCTURE := $(shell find $(SRCFOLDER) -type d) 

CODEFILES := $(addsuffix /*,$(STRUCTURE))
CODEFILES := $(wildcard $(CODEFILES))

SRCFILES := $(filter %.cpp,$(CODEFILES))
HDRFILES := $(filter %.h,$(CODEFILES))
OBJFILES := $(subst $(SRCFOLDER),$(OBJFOLDER),$(SRCFILES:%.cpp=%.o))

compile: $(OBJFILES)
	$(CC) $(OBJFILES) -o $(BINFOLDER)/$(SYNTH) $(LIBS) $(CFLAGS)

$(OBJFOLDER)/%.o: $(addprefix $(SRCFOLDER)/,%.cpp %.h) makefolders
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFS) $(LIBS)

makefolders:
	if [ ! -d "./$(OBJFOLDER)" ]; then \
		mkdir $(OBJFOLDER); \
		mkdir $(OBJFOLDER)/lexer; \
		mkdir $(OBJFOLDER)/streams; \
	fi

clean:
	-rm -r $(OBJFOLDER)