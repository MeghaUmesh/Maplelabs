g++ -std=c++11 -static-libgcc -static-libstdc++  simulator.cpp  main.cpp -o simulator -pthread
echo "compile done..."
./simulator