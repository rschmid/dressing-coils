ROOTCONFIG	:= root-config
ObjSuf        = o
SrcSuf        = cpp
ExeSuf        =
DllSuf        = so
EVENTLIB      = $(EVENTO)
OutPutOpt     = -o
ROOTLIBS	:= $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS	:= $(shell $(ROOTCONFIG) --glibs)



# Linux
DBGFLAG       = -g
OPTFLAG       = -O2
CXX           = g++
CXXFLAGSDBG   = -g -Wall -fPIC -I$(ROOTSYS)/include -I~/src/include/spirit
CXXFLAGS      = -O2 -Wall -fPIC -I$(ROOTSYS)/include -I~/src/include/spirit
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -Wl,-soname,libEvent.so -shared
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTLIBS) $(ROOTGLIBS) $(SYSLIBS)

default: test

PROGRAMS	= test

TESTO	= test.o

RUNO = Neutron.o Boundary.o Bfield.o Reading.o Scattering.o Run.o runDict.o
RUNH = Neutron.h Boundary.h Bfield.h Vector.h Scattering.h Run.h
RUNDBG = $(RUNO:.o=.dbg)

test: $(TESTO)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

run: 	$(RUNO)
	$(LD) -O2 $^ $(LIBS) -o $@

run_dbg: $(RUNDBG)
	$(LD) -g $^ $(LIBS) -o $@

clean:
	rm -f *.o *.dbg


%.o:: %.C
	$(CXX) $(CXXFLAGS) -Wno-deprecated -c $< -o $@

%.dbg:: %.C
	$(CXX) $(CXXFLAGSDBG) -Wno-deprecated -c $< -o $@


runDict.C: $(RUNH)
	@echo "Generating dictionary $@..."
	@rootcint -f $@ -c $^
