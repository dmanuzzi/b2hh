#export ROOT_INCLUDE_PATH=$PWD/Reco/inc/:$ROOT_INCLUDE_PATH
#export LD_LIBRARY_PATH=$PWD/Reco/lib:$LD_LIBRARY_PATH
CXX=$(shell root-config --cxx)
INCLUDE=$(shell root-config --incdir)
INCLUDE+= -I${PWD} 
LIBS=$(shell root-config --glibs)
CXXFLAGS+=$(shell root-config --cflags)
#CXXFLAGS+= -fsanitize=address -fno-omit-frame-pointer 
#LIBS+= -Wl

all:

%: %.C
	${CXX} -Ofast -Wall ${CXXFLAGS} -I${INCLUDE} ${LIBS} ${ROOFITLIBS} -o ./$@ $@.C



