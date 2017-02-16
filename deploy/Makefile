CC = g++

CFLAGS = -O3 -Wall -std=c++11

INCLUDES = -Iinclude/driver/data_link \
-Iinclude/driver/gimbal \
-Iinclude/driver/heartbeat \
-Iinclude/driver/imu \
-Iinclude/driver/message \
-Iinclude/driver/message_container \
-Iinclude/driver/network \
-Iinclude/driver/pwmio \
-Iinclude/driver/servo \
-Iinclude/driver/thread \
-Iinclude/etc \
-Iinclude/threads \
-I3rd_party/Navio/include \
-I3rd_party/onboardSDK/include

LFLAGS = -L3rd_party/Navio/lib \
-L3rd_party/onboardSDK/lib

LIBS = -lNavio \
-lOnboardSDK \
-lpthread -lrt -lpigpio -lwiringPi 

SRCS = source/driver/data_link/DataConverter.cpp source/driver/data_link/XtendDataLink.cpp \
source/driver/gimbal/SKnightGimbal.cpp \
source/driver/imu/A3HardDriver.cpp source/driver/imu/IMUA3.cpp \
source/driver/message/Message.cpp source/driver/message/MessageFactory.cpp source/driver/message/StdMessage.cpp \
source/driver/network/Network.cpp source/driver/network/Socket.cpp \
source/driver/pwmio/NavioPWMIO.cpp \
source/driver/servo/A3Servo.cpp \
source/driver/thread/Thread.cpp \
source/etc/API.cpp source/etc/Channel.cpp \
source/threads/ClientThread.cpp source/threads/GimbalThread.cpp source/threads/HeartbeatThread.cpp \
source/threads/IMUThread.cpp source/threads/RcThread.cpp source/threads/ServerThread.cpp \
source/threads/ServoThread.cpp \
source/main.cpp

OBJS = $(SRCS:.cpp=.o)

BIN_DIR = ./bin

MAIN = flight

all: $(MAIN)
	@echo Flight system has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<	-o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/$(MAIN)