CFLAGS = -std=c++17 -O2 -Wall -Wextra
GLEW_LIBS=$(shell pkg-config glew --libs)
GLFW_LIBS=$(shell pkg-config glfw3 --libs)

TARGET=cg


$(TARGET): main.o
	g++ $(CFLAGS) -o $@ $< $(GLEW_LIBS) $(GLFW_LIBS)

%.o: %.cpp
	g++ $(CFLAGS) -c $<


.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
