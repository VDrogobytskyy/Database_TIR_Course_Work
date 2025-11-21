CXX = g++

CXXFLAGS = -std=c++17 \
    -I/usr/local/mysql-connector-c++-9.5.0/include \
    -I/usr/local/mysql-connector-c++-9.5.0/include/jdbc \
	-I./libs

LDFLAGS = -L/Applications/MySQLWorkbench.app/Contents/Frameworks \
    -lmysqlcppconn

TARGET = app

SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) -L/Applications/MySQLWorkbench.app/Contents/Frameworks -lmysqlcppconn -Wl,-rpath,/Applications/MySQLWorkbench.app/Contents/Frameworks -o $(TARGET)

clean:
	rm -f $(TARGET)
