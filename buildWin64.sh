x86_64-w64-mingw32-g++ -std=c++17 -O2 -Wall -Wextra -static -static-libgcc -static-libstdc++ \
    -o CircuitBorn.exe *.cpp \
    -I../Deps/raylibWin64/include \
    -L../Deps/raylibWin64/lib \
    -lraylib -lopengl32 -lgdi32 -lwinmm -ld3d9
