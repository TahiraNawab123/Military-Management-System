all: ./a.out

compRun:
	g++ -std=c++11 main.cpp sensors.cpp intrusion.cpp User.cpp Message.cpp Admin.cpp Officer.cpp Soldier.cpp SecureCommunication.cpp Inventory.cpp Alert.cpp -o r.out


run: clean compRun; ./r.out

clean:
	rm -f *.out
