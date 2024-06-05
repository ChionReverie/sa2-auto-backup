cmake --preset wine && \
make --directory=./build -f Makefile && \
cp "./bin/AutoBackup.dll" "./AutoBackup" -f