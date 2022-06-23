CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
HANDLER_DIR = CommandHandler
CFLAGS = -std=c++11  -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/ClientReceiver.o \
	$(BUILD_DIR)/Segment.o \

ClientReceiverSensitivities = \
	$(SRC_DIR)/ClientReceiver.cpp \
	$(INCLUDE_DIR)/ClientReceiver.hpp \
	$(INCLUDE_DIR)/Segment.hpp \

ReceiverSensitivities = \
	$(SRC_DIR)/Receiver.cpp \
	$(INCLUDE_DIR)/Receiver.hpp \
	$(INCLUDE_DIR)/Segment.hpp \

SenderSensitivities = \
	$(SRC_DIR)/Sender.cpp \
	$(INCLUDE_DIR)/Sender.hpp \
	$(INCLUDE_DIR)/Segment.hpp \

SegmentSensitivities = \
	$(SRC_DIR)/Segment.cpp \
	$(INCLUDE_DIR)/Segment.hpp \

all: $(BUILD_DIR) Sender.out $(BUILD_DIR)/Receiver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

Sender.out: $(BUILD_DIR)/Sender.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Sender.out $(BUILD_DIR)/Sender.o $(OBJECTS)

$(BUILD_DIR)/Receiver.out: $(BUILD_DIR)/Receiver.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/Receiver.out $(BUILD_DIR)/Receiver.o $(OBJECTS)

$(BUILD_DIR)/Segment.o: $(SegmentSensitivities)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Segment.cpp -o $(BUILD_DIR)/Segment.o

$(BUILD_DIR)/ClientReceiver.o: $(ClientReceiverSensitivities)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ClientReceiver.cpp -o $(BUILD_DIR)/ClientReceiver.o

$(BUILD_DIR)/Sender.o: $(SenderSensitivities)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Sender.cpp -o $(BUILD_DIR)/Sender.o

$(BUILD_DIR)/Receiver.o: $(ReceiverSensitivities)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Receiver.cpp -o $(BUILD_DIR)/Receiver.o


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out