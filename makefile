all: r.out

CXX = g++
CXXFLAGS = -std=c++11 -Iinclude

SRCS = \
	src/app/main.cpp \
	src/core/User.cpp \
	src/core/Admin.cpp \
	src/core/Officer.cpp \
	src/core/Soldier.cpp \
	src/core/Message.cpp \
	src/modules/ids/sensors.cpp \
	src/modules/ids/intrusion.cpp \
	src/modules/inventory/Inventory.cpp \
	src/modules/secure_comm/SecureCommunication.cpp \
	src/modules/alerts/Alert.cpp

r.out: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o r.out

compRun: r.out

run: clean compRun
	./r.out

clean:
	rm -f *.out r.out
