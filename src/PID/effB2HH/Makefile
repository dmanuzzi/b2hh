CXX=$(shell root-config --cxx)
INCLUDE=$(shell root-config --incdir)
INCLUDE+= -I${PWD} -I${B2HH_SRC}/Lib/ -I${B2HH_CONFIG}/ -I${B2HH_SRC}/Tools/
INCLUDE+=-I/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/sqlite/3110100/x86_64-slc6-gcc49-opt/include/
LIBS=$(shell root-config --glibs)
LIBS+=-I/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/sqlite/3110100/x86_64-slc6-gcc49-opt/lib/
CXXFLAGS=$(shell root-config --cflags)

all: effB2HH

%: %.C
	${CXX} -O2 -Wall ${CXXFLAGS} -I${INCLUDE} ${LIBS} -lTMVA -lsqlite3 -o $@ $@.C


