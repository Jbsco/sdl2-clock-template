# UNAME := $(shell uname)

ifeq ($(OS),Windows_NT) 
	WINLOC=$(GAMELOC)
	SDLCFLAGS=`sdl2-config --cflags`
	SDLLIBS=`sdl2-config --libs` -lSDL2_mixer -lSDL2_ttf -lSDL2_image -mconsole
endif

ifeq ($(OS),Linux)
	SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
	SDLLIBS=-lSDL2
endif

SRCDIR=src
SRCS=$(SRCDIR)/clock.cpp $(SRCDIR)/Exception.cpp
HEADERS=$(SRCDIR)/Clock.h $(SRCDIR)/Element.h $(SRCDIR)/ElementEx.h \
$(SRCDIR)/Exception.h $(SRCDIR)/MediaManager.h $(SRCDIR)/TextureInfo.h
EXE=$(BUILDDIR)/clock.exe
SCRIPTS=clock.sh clock.bat

MEDIADIR=img
MEDIA=$(MEDIADIR)/background.bmp

BUILDDIR=build
BUILDFILES=Makefile

$(EXE): $(SRCS) $(HEADERS)
	g++ -g -Wall $(SDLCFLAGS) -o $@ $(SRCS) $(SDLLIBS)

clock.zip: $(SRCS) $(HEADERS) $(MEDIA) $(BUILDFILES) $(SCRIPTS)
	zip clock.zip $+

Deploy.zip: $(MEDIA) $(EXE) $(SCRIPTS)
	zip Deploy.zip $+

run: ${EXE}
	./${EXE}

clean: 
	rm $(EXE)

cleanAll: 
	rm $(BUILDDIR)/*

all: $(EXE) clock.zip clock.zip 
