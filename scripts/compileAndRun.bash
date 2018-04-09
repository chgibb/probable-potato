printf "Running $1.cpp\n"
bash scripts/compileTest.bash tests/$1.cpp
bash scripts/runTest.bash tests/$1.cpp