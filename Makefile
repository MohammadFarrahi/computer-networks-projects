CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
HANDLER_DIR = CommandHandler
CFLAGS = -std=c++11  -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/UserInfo.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/ServerConfig.o \
	$(BUILD_DIR)/UserConfig.o \
	$(BUILD_DIR)/Logger.o \
	$(BUILD_DIR)/Utilities.o \
	$(BUILD_DIR)/UserManager.o \
	$(BUILD_DIR)/CwdHandler.o \

CommandHandlerSensitivityList = \
	$(SRC_DIR)/CommandHandler.cpp \
	$(INCLUDE_DIR)/CommandHandler.hpp \

ServerConfigSensitivityList = \
	$(SRC_DIR)/ServerConfig.cpp \
	$(INCLUDE_DIR)/ServerConfig.hpp \

UserConfigSensitivityList = \
	$(SRC_DIR)/UserConfig.cpp \
	$(INCLUDE_DIR)/UserConfig.hpp \

UserInfoSensitivityList = \
	$(SRC_DIR)/UserInfo.cpp \
	$(INCLUDE_DIR)/UserInfo.hpp \

UserSensitivityList = \
	$(SRC_DIR)/User.cpp \
	$(INCLUDE_DIR)/User.hpp \

LoggerSensitivityList = \
	$(SRC_DIR)/Logger.cpp \
	$(INCLUDE_DIR)/Logger.hpp \

UtilitiesSensitivityList = \
	$(SRC_DIR)/Utilities.cpp \
	$(INCLUDE_DIR)/Utilities.hpp \

UserManagerSensitivityList = \
	$(SRC_DIR)/UserManager.cpp \
	$(INCLUDE_DIR)/UserManager.hpp \

CwdHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/CwdHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/CwdHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

ServerSensitivityList = \
	$(SRC_DIR)/Server.cpp \
	$(INCLUDE_DIR)/Server.hpp \

ClientSensitivityList = \
	$(SRC_DIR)/Client.cpp \
	$(INCLUDE_DIR)/Client.hpp \

all: $(BUILD_DIR) Server.out Client.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

Server.out: $(BUILD_DIR)/Server.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Server.out $(BUILD_DIR)/Server.o $(OBJECTS)

Client.out: $(BUILD_DIR)/Client.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Client.out $(BUILD_DIR)/Client.o $(OBJECTS)

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/ServerConfig.o: $(ServerConfigSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ServerConfig.cpp -o $(BUILD_DIR)/ServerConfig.o

$(BUILD_DIR)/UserConfig.o: $(UserConfigSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UserConfig.cpp -o $(BUILD_DIR)/UserConfig.o

$(BUILD_DIR)/User.o: $(UserSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UserInfo.o: $(UserInfoSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UserInfo.cpp -o $(BUILD_DIR)/UserInfo.o

$(BUILD_DIR)/Logger.o: $(LoggerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Logger.cpp -o $(BUILD_DIR)/Logger.o

$(BUILD_DIR)/Utilities.o: $(UtilitiesSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Utilities.cpp -o $(BUILD_DIR)/Utilities.o

$(BUILD_DIR)/UserManager.o: $(UserManagerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UserManager.cpp -o $(BUILD_DIR)/UserManager.o

$(BUILD_DIR)/CwdHandler.o: $(CwdHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/CwdHandler.cpp -o $(BUILD_DIR)/CwdHandler.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out