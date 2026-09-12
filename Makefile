# Compiler configuration
CXX ?= g++
CPPFLAGS := -Iinclude -Isrc/client -Isrc/server -Isrc/shared \
	-I"C:/Users/79820/Documents/enet/include"
CXXFLAGS ?= -std=c++17 -Wall -Wextra
LDFLAGS = -Llib -L"C:/Users/79820/Documents/enet"
LDLIBS ?= -lraylib -lenet

ifeq ($(OS),Windows_NT)
	LDLIBS += -lgdi32 -lwinmm -lws2_32
	RM = cmd /C del /f /q
else
	LDLIBS += -lX11 -lGL -lm -lpthread
	RM = rm -f
endif

CLIENT_SRCS := $(wildcard src/client/*.cc) src/shared/serialization.cc src/shared/deserialization.cc
SERVER_SRCS := $(wildcard src/server/*.cc) src/shared/serialization.cc src/shared/deserialization.cc
CLIENT_OBJ := $(CLIENT_SRCS:.cc=.o)
SERVER_OBJ := $(SERVER_SRCS:.cc=.o)

.PHONY: all client server clean

all: client server

client: client.exe

server: server.exe

client.exe: $(CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $(CLIENT_OBJ) $(LDFLAGS) $(LDLIBS)

server.exe: $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $(SERVER_OBJ) $(LDFLAGS) $(LDLIBS)

src/client/%.o: src/client/%.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

src/server/%.o: src/server/%.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

src/shared/%.o: src/shared/%.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) client.exe server.exe $(CLIENT_OBJ) $(SERVER_OBJ)