CXX=$(shell root-config --cxx)
INCLUDE=$(shell root-config --incdir)
INCLUDE+= -I${PWD} -I${B2HH_SRC}/Lib/ -I${B2HH_CONFIG}/ -I${B2HH_SRC}/Tools/
LIBS=$(shell root-config --glibs)
CXXFLAGS=$(shell root-config --cflags)
ROOFITLIBS=-lRooFit -lRooFitCore

# all: provaVin createTemplate createPhysTemplate

%: %.C
	${CXX} -O2 -Wall ${CXXFLAGS} -I${INCLUDE} ${LIBS} ${ROOFITLIBS}  -o $@ $@.C
