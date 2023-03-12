
default:
	g++ src/*.cpp -o cpp_raytracer.exe -O2 -Wall -Wno-missing-braces -I src/include -L lib -lraylib -lopengl32 -lgdi32 -lwinmm
