bin=cryctl
version=1.0
distname=$(bin)-$(version)

CXXFLAGS += -Wall

cryctl_src=src/Charmap.cpp src/Crc16.cpp src/Lcd.cpp src/cry.cpp
cryctl_obj=$(cryctl_src:.cpp=.o)

all: $(bin)

cryctl: $(cryctl_obj)
	$(CXX) $(CXXFLAGS) $(cryctl_obj) -o $@

depend:
	makedepend -Y $(cryctl_src)

clean:
	rm -f $(cryctl_obj)
	rm -f $(bin)

# DO NOT DELETE

src/Charmap.o: src/Charmap.h
src/Crc16.o: src/Crc16.h src/Command.h
src/Lcd.o: src/Lcd.h src/Crc16.h src/Command.h
src/cry.o: src/Lcd.h
