CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -I./libs
LDFLAGS = -L/opt/homebrew/Cellar/mysql-connector-c++/9.5.0/lib -lmysqlcppconnx
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