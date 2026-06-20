CC = em++
CFLAGS = -Os -Wall -DPLATFORM_WEB
LDFLAGS = -s USE_GLFW=3 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 --shell-file /home/noam/raylib/src/minshell.html
INCLUDES = -I/home/noam/raylib/src
LIBS = /home/noam/raylib/src/libraylib.a

all:
	$(CC) -o index.html Pong.cpp $(LIBS) $(INCLUDES) $(CFLAGS) $(LDFLAGS)
