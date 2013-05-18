TOPDIR = .

CC=gcc
CXX=g++

PWD = $(shell pwd)

BASEPWD = $(shell basename $(shell pwd))

AGENTVERSION = ${BASEPWD}
VERNAME = ${BASEPWD}

OWNER = BIUK
ARCHIVEDIR = ../Archive

include $(TOPDIR)/Makefile.common

LDFLAGS += -L$(LIBDIR) -l$(MAINLIB)
LIBS += $(foreach DEPLIB,$(DEPLIBS),-l$(DEPLIB))
MAINLIB = Main

BINS = Recovery
DEPS = $(foreach DEPLIB,$(DEPLIBS),$(LIBDIR)/lib$(DEPLIB).a)

clean tidy::
	rm -f .lib/lib$(MAINLIB).a $(BINS)
	rm -f outs FormEdit
	rm -rf Logfiles
	rm -rf LogFiles/*

all clean tidy::
	@for I in $(DEPLIBS); do $(MAKE) -C $$I $@ || exit 1; done

all:: $(BINS)

$(BINS): Main.cpp .lib/libMain.a
	$(CXX) -o $(BINS) $(CXXFLAGS) $(DEFS) Main.cpp $(LDFLAGS);

static:
	make
	touch Main.cpp
	$(CXX) -o $(BINS) $(CXXSTATICFLAGS) $(DEFS) Main.cpp $(LDFLAGS);
	strip $(BINS)

bz2:
	rm -rf /tmp/$(BASEPWD)
	cp -r $(PWD) /tmp/$(BASEPWD)
	cp -r /tmp/$(BASEPWD) $(PWD)
	rm -rf /tmp/$(BASEPWD)
	make -C ./$(BASEPWD) clean
	-tar -jcf ../$(VERNAME).tar.bz2 $(BASEPWD)/*
	rm -rf /tmp/$(BASEPWD)
	rm -rf $(BASEPWD)

bz2time:
	rm -rf /tmp/$(BASEPWD)
	cp -r $(PWD) /tmp/$(BASEPWD)
	cp -r /tmp/$(BASEPWD) $(PWD)
	rm -rf /tmp/$(BASEPWD)
	make -C ./$(BASEPWD) clean
	@date "+$(AGENTVERSION)%nDate: %Y/%m/%d%nTime: %H:%M:%S%n" > ./$(BASEPWD)/ARCHIVE
	-tar -jcf ../$(VERNAME)-`date +%Y_%m_%d-%H_%M`.tar.bz2 $(BASEPWD)/*
	rm -rf /tmp/$(BASEPWD)
	rm -rf $(BASEPWD)

archive:
	if [ -e COMMENT ] ; then rm -f COMMENT ; fi
	@echo "Dist File :         ~/Archive/$(OWNER)/$(VERNAME)-`date +%Y_%m_%d-%H_%M`.tar.bz2" > COMMENT
	@echo -e -n "Code Description :  " >> COMMENT
	dialog --inputbox "Please enter a description for this release of Mersad source code :" 8 72 "<General Version>" 2>> COMMENT
	@echo -e -n "\nPackage Host Name : " >> COMMENT
	@hostname >> COMMENT
	@echo -e -n "Release Date :      " >> COMMENT
	@date +%Y/%m/%d >> COMMENT
	@echo -e -n "Release Time :      " >> COMMENT
	@date +%H:%M\ \ %Z >> COMMENT
	@echo -e -n "Code Version :      $(AGENTVERSION)\n" >> COMMENT
	@echo -e -n "Code Owner :        $(OWNER)\n" >> COMMENT
	rm -r -f $(ARCHIVEDIR)/$(OWNER)/$(VERNAME)
	cp -r $(PWD) $(ARCHIVEDIR)/$(OWNER)/
	make -C $(ARCHIVEDIR)/$(OWNER)/$(VERNAME) clean
	rm -rf $(ARCHIVEDIR)/$(OWNER)/$(VERNAME)/Scripts
	{ cd $(ARCHIVEDIR)/$(OWNER)/ ; tar -jcf $(ARCHIVEDIR)/$(OWNER)/$(VERNAME)-`date +%Y_%m_%d-%H_%M`.tar.bz2 $(VERNAME) ; cd $(PWD) ; }
	rm -rf $(ARCHIVEDIR)/$(OWNER)/$(VERNAME)

pack: archive
	echo "Package Created !"

version:
	@echo $(AGENTVERSION)

