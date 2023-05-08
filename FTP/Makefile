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
	$(BUILD_DIR)/ICommand.o \
	$(BUILD_DIR)/LoginRequiredHandler.o \
	$(BUILD_DIR)/UsernameHandler.o \
	$(BUILD_DIR)/PasswordHandler.o \
	$(BUILD_DIR)/PwdHandler.o \
	$(BUILD_DIR)/MkdHandler.o \
	$(BUILD_DIR)/DeleHandler.o \
	$(BUILD_DIR)/LsHandler.o \
	$(BUILD_DIR)/CwdHandler.o \
	$(BUILD_DIR)/RenameHandler.o \
	$(BUILD_DIR)/RetrHandler.o \
	$(BUILD_DIR)/HelpHandler.o \
	$(BUILD_DIR)/QuitHandler.o \
	$(BUILD_DIR)/Constants.o \

CommandHandlerSensitivityList = \
	$(SRC_DIR)/CommandHandler.cpp \
	$(INCLUDE_DIR)/CommandHandler.hpp \
	$(INCLUDE_DIR)/Constants.hpp \

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
	$(INCLUDE_DIR)/Constants.hpp \

LoggerSensitivityList = \
	$(SRC_DIR)/Logger.cpp \
	$(INCLUDE_DIR)/Logger.hpp \

UtilitiesSensitivityList = \
	$(SRC_DIR)/Utilities.cpp \
	$(INCLUDE_DIR)/Utilities.hpp \

UserManagerSensitivityList = \
	$(SRC_DIR)/UserManager.cpp \
	$(INCLUDE_DIR)/UserManager.hpp \
	$(INCLUDE_DIR)/Constants.hpp \

ICommandSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/ICommand.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \
	$(INCLUDE_DIR)/Constants.hpp \

ConstantsSensitivityList = \
	$(SRC_DIR)/Constants.cpp \
	$(INCLUDE_DIR)/Constants.hpp \

LoginRequiredHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/LoginRequiredHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/LoginRequiredHandler.hpp \

UsernameHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/UsernameHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/UsernameHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

PasswordHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/PasswordHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/PasswordHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

PwdHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/PwdHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/PwdHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

MkdHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/MkdHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/MkdHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

DeleHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/DeleHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/DeleHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

LsHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/LsHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/LsHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

CwdHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/CwdHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/CwdHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \
	
RenameHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/RenameHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/RenameHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

RetrHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/RetrHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/RetrHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

HelpHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/HelpHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/HelpHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

QuitHandlerSensitivityList = \
	$(SRC_DIR)/$(HANDLER_DIR)/QuitHandler.cpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/QuitHandler.hpp \
	$(INCLUDE_DIR)/$(HANDLER_DIR)/ICommand.hpp \

ServerSensitivityList = \
	$(SRC_DIR)/Server.cpp \
	$(INCLUDE_DIR)/Server.hpp \
	$(INCLUDE_DIR)/Constants.hpp \

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

$(BUILD_DIR)/ICommand.o: $(ICommandSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/ICommand.cpp -o $(BUILD_DIR)/ICommand.o

$(BUILD_DIR)/LoginRequiredHandler.o: $(LoginRequiredHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/LoginRequiredHandler.cpp -o $(BUILD_DIR)/LoginRequiredHandler.o

$(BUILD_DIR)/UsernameHandler.o: $(UsernameHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/UsernameHandler.cpp -o $(BUILD_DIR)/UsernameHandler.o

$(BUILD_DIR)/PasswordHandler.o: $(PasswordHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/PasswordHandler.cpp -o $(BUILD_DIR)/PasswordHandler.o

$(BUILD_DIR)/PwdHandler.o: $(PwdHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/PwdHandler.cpp -o $(BUILD_DIR)/PwdHandler.o

$(BUILD_DIR)/MkdHandler.o: $(MkdHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/MkdHandler.cpp -o $(BUILD_DIR)/MkdHandler.o

$(BUILD_DIR)/DeleHandler.o: $(DeleHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/DeleHandler.cpp -o $(BUILD_DIR)/DeleHandler.o

$(BUILD_DIR)/LsHandler.o: $(LsHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/LsHandler.cpp -o $(BUILD_DIR)/LsHandler.o

$(BUILD_DIR)/CwdHandler.o: $(CwdHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/CwdHandler.cpp -o $(BUILD_DIR)/CwdHandler.o

$(BUILD_DIR)/RenameHandler.o: $(RenameHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/RenameHandler.cpp -o $(BUILD_DIR)/RenameHandler.o

$(BUILD_DIR)/RetrHandler.o: $(RetrHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/RetrHandler.cpp -o $(BUILD_DIR)/RetrHandler.o

$(BUILD_DIR)/HelpHandler.o: $(HelpHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/HelpHandler.cpp -o $(BUILD_DIR)/HelpHandler.o

$(BUILD_DIR)/QuitHandler.o: $(QuitHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(HANDLER_DIR)/QuitHandler.cpp -o $(BUILD_DIR)/QuitHandler.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/Constants.o: $(ConstantsSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Constants.cpp -o $(BUILD_DIR)/Constants.o

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out