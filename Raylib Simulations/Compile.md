# Pong Web Compilation Guide

Dieses Dokument beschreibt, wie ich C++ mit Raylib für Web compile


## Build Schritte

setup-emsdk

make

### 1. Emscripten Umgebung laden
Vor dem Kompilieren müssen die Umgebungsvariablen in der aktuellen Terminal-Sitzung geladen werden:

  setup-emsdk(in meinen Umgebungsvariablen, zshrc gespeichert)

Mein Makefile ausführen:
  
  make

also relativ simpel. Das ist im Makefile:
  ```CC = em++
  CFLAGS = -Os -Wall -DPLATFORM_WEB
  LDFLAGS = -s USE_GLFW=3 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 --shell-file /home/noam/raylib/src/minshell.html
  INCLUDES = -I/home/noam/raylib/src
  LIBS = /home/noam/raylib/src/libraylib.a

  all:
    $(CC) -o index.html Pong.cpp $(LIBS) $(INCLUDES) $(CFLAGS) $(LDFLAGS)
  ```

## Spielen
  python -m http.server 8080 und dann http://localhost:8080
