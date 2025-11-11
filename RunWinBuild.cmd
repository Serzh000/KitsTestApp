mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
cd ..
copy document.txt .\build\bin\
copy kit.txt .\build\bin\