:: Remove folders/files to start fresh
rmdir /s /q build
rmdir /s /q Testing

:: Setup cmake and build source
cmake 	--no-warn-unused-cli ^
	-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE ^
	-DCMAKE_BUILD_TYPE:STRING=Debug ^
	-DCMAKE_C_COMPILER:FILEPATH=C:\mingw64\bin\gcc.exe ^
	-DCMAKE_CXX_COMPILER:FILEPATH=C:\mingw64\bin\g++.exe ^
	-DTESTING=TRUE ^
	-S . ^
	-B ./build ^
	-G "MinGW Makefiles" 

:: Build UnitTesting project
cmake 	--build ./build ^
	--config Debug ^
	--target all ^
	-j 14 

:: Execute tests
ctest 	-j 12 ^
	-C Debug ^
	--test-dir ./build/test ^
	--extra-verbose ^
	--progress ^
	--output-on-failure

pause
:: exit /B 0
