g++ -std=c++17 -c $1 -Wall -Werror -I/usr/include/allegro5 -o $1.o

g++ -o $1.out  $1.o -L/usr/lib $(find src/PBP/ -type f -iname *.o -print) -lallegro -lallegro_main -lallegro_image
