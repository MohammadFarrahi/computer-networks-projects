CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11  -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/Network.o \
	$(BUILD_DIR)/Util.o \
	$(BUILD_DIR)/Node.o

CommandHandlerSensitivityList = \
	$(SRC_DIR)/CommandHandler.cpp \
	$(INCLUDE_DIR)/CommandHandler.hpp

NetworkSensitivityList = \
	$(SRC_DIR)/Network.cpp \
	$(INCLUDE_DIR)/Network.hpp \
	$(INCLUDE_DIR)/Util.hpp \
	

UtilSensitivityList = \
	$(SRC_DIR)/Util.cpp \
	$(INCLUDE_DIR)/Util.hpp 

NodeSensitivityList = \
	$(SRC_DIR)/Node.cpp \
	$(INCLUDE_DIR)/Node.hpp 

mainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/CommandHandler.hpp

all: $(BUILD_DIR) network.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

network.out: $(BUILD_DIR)/main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o network.out $(BUILD_DIR)/main.o $(OBJECTS)

$(BUILD_DIR)/main.o: $(mainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/Util.o: $(UtilSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Util.cpp -o $(BUILD_DIR)/Util.o

$(BUILD_DIR)/Network.o: $(NetworkSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Network.cpp -o $(BUILD_DIR)/Network.o

$(BUILD_DIR)/Node.o: $(NodeSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Node.cpp -o $(BUILD_DIR)/Node.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out