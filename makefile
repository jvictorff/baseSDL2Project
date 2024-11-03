PROJECT_NAME = BaseSDLProject
SOURCE = .\files\main.cpp

# Diretório de inclusão das bibliotecas
INCLUDE = -I C:\C++projects\Libs\SDL2\x86_64-w64-mingw32\include\

# Diretório das bibliotecas
LIBRARY = -L C:\C++projects\Libs\SDL2\x86_64-w64-mingw32\lib\
           -L C:\C++projects\Libs\SDL2_image\x86_64-w64-mingw32\lib\
           -L C:\C++projects\Libs\SDL2_mixer\x86_64-w64-mingw32\lib\
           -L C:\C++projects\Libs\SDL2_ttf\x86_64-w64-mingw32\lib\
           -L C:\C++projects\Libs\SDL2_net\x86_64-w64-mingw32\lib\
           -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

OUTPUT = $(PROJECT_NAME).exe

all:
	g++ $(SOURCE) $(INCLUDE) $(LIBRARY) -o $(OUTPUT)

clean:
	del $(OUTPUT)
