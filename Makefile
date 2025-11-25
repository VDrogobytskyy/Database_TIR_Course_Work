CXX = g++

CXXFLAGS = -std=c++17 \
    -I/usr/local/mysql-connector-c++-9.5.0/include \
    -I/usr/local/mysql-connector-c++-9.5.0/include/jdbc \
    -I./libs

LDFLAGS = -L/Applications/MySQLWorkbench.app/Contents/Frameworks \
    -lmysqlcppconn \
    -Wl,-rpath,/Applications/MySQLWorkbench.app/Contents/Frameworks

TARGET = app

SRCS = main.cpp DB.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
