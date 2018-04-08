cd src
cd PBP

for f in *.cpp
do
    g++ -std=c++17 -c $f -Wall -Werror -I/usr/include/allegro5 -o $f.o
done

cd ../
cd ../