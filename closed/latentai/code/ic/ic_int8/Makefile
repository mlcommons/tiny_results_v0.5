RUNTIME_DIR=$(shell pwd)
TVM_ROOT=/home/pi/tvm
DMLC_CORE=${TVM_ROOT}/3rdparty/dmlc-core

BINDIR=./bin

# Try to set compiler for x86 (docker) or cross-compile for ARM (NXP/RaspBerry Pi)
CXX_x86=g++
CXX_arm=/usr/bin/aarch64-linux-gnu-g++-8

SRCS += main.cpp

OBJS += \
$(patsubst %.cc,%.o,$(SRCS))

RUNTIME_CFLAGS = -std=c++14 -O2 -fPIC \
				 -I${TVM_ROOT}/include \
				 -I${DMLC_CORE}/include \
				 -I${TVM_ROOT}/3rdparty/dlpack/include \
				 -I$(RUNTIME_DIR)/

PKG_LDFLAGS = -L${RUNTIME_DIR}/bin -ldl -pthread \

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

all: exp

exp: 
	mkdir -p $(BINDIR)
	cp ic_int8.so $(BINDIR)
	cd $(BINDIR)
	$(CXX_arm) -c $(RUNTIME_CFLAGS) -o $(BINDIR)/tvm_runtime_pack.o runtime/tvm_runtime_pack.cc
	$(CXX_arm) -c $(RUNTIME_CFLAGS) -o $(BINDIR)/ic_helper.o ic/ic_helper.cpp
	$(CXX_arm) -c $(RUNTIME_CFLAGS) -o $(BINDIR)/runtime.o runtime/runtime.cpp $(PKG_LDFLAGS)
	$(CXX_arm) -c $(RUNTIME_CFLAGS) -o $(BINDIR)/submitter_implemented.o submitter_implemented.cpp $(PKG_LDFLAGS)
	$(CXX_arm) -c $(RUNTIME_CFLAGS) -o $(BINDIR)/internally_implemented.o api/internally_implemented.cpp

	$(CXX_arm) $(RUNTIME_CFLAGS) -o $(BINDIR)/main main.cpp $(BINDIR)/tvm_runtime_pack.o $(BINDIR)/submitter_implemented.o $(BINDIR)/internally_implemented.o $(BINDIR)/ic_helper.o $(BINDIR)/runtime.o $(PKG_LDFLAGS)

clean: 
		rm -rf bin
