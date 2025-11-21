
CXX = g++
CXXFLAGS = -std=c++17 \
    -I/usr/local/mysql-connector-c++-9.5.0/include \
    -I/usr/local/mysql-connector-c++-9.5.0/include/jdbc

LDFLAGS = -L/usr/local/mysql-connector-c++-9.5.0/lib64 \
    -lmysqlcppconn

TARGET = app
SRC = main.cpp


all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
