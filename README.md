<h1>Unit Testing Circular Queue (cqueue) with Google Test</h1>

<h2>Setup</h2>

The <a href="https://github.com/google/googletest">Google Test</a> framework is being used to test cqueue. Builds successfully using the following toolchains (on Windows 10):

<br>

```
GCC 11.2.0 x86_64-w64-mingw32
GCC 12.2.0 x86_64-w64-mingw32
```

<br>

Install chocolatey (a package manager for Windows) and mingw (a compiler toolchain). You will also need to install cmake (a build system manager) which includes ctest (a framework for unit testing supported by cmake). Be sure to add `<your cmake install dir>\CMake\bin` to the PATH variable.

<br>

```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

choco install mingw
choco install cmake --pre
```

<br>
To clone this repo and bring in googletest as a sbmodule (required), use

<br>

```
git clone --recurse-submodules https://github.com/markCwatson/CircularQueue_with_GoogleTest.git
```

<br>

<h2>Build and Run Tests (Windows)</h2>

Run the `RunTests.bat` batch script. Note: this script assumes `gcc` and `g++` are installed at `C:\mingw64\bin\`. Your output should look something like what is shown below.

<br>

```
<path>\CircularQueue_with_GoogleTest>rmdir /s /q build
<path>\CircularQueue_with_GoogleTest>rmdir /s /q Testing

<path>\CircularQueue_with_GoogleTest>cmake  --no-warn-unused-cli        -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE                -DCMAKE_BUILD_TYPE:STRING=Debug                 -DCMAKE_C_COMPILER:FILEPATH=C:\mingw64\bin\gcc.exe           -DCMAKE_CXX_COMPILER:FILEPATH=C:\mingw64\bin\g++.exe -DTESTING=TRUE          -S .            -B ./build              -G "MinGW Makefiles"
Not searching for unused variables given on the command line.
-- The C compiler identification is GNU 11.2.0
-- The CXX compiler identification is GNU 11.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/mingw64/bin/gcc.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/mingw64/bin/g++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Python: C:/Python311/python.exe (found version "3.11.0") found components: Interpreter
-- Configuring done
-- Generating done
-- Build files have been written to: <path>/CircularQueue_with_GoogleTest/build

<path>\CircularQueue_with_GoogleTest>cmake  --build ./build             --config Debug           --target all            -j 14
[  8%] Building C object CMakeFiles/CircularQueue_GTest.dir/cqueue.c.obj
[ 16%] Building CXX object googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj
[ 25%] Linking C static library libCircularQueue_GTest.a
[ 25%] Built target CircularQueue_GTest
[ 33%] Linking CXX static library ..\..\lib\libgtest.a
[ 33%] Built target gtest
[ 41%] Building CXX object googletest/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj
[ 50%] Building CXX object googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.obj
[ 58%] Linking CXX static library ..\..\lib\libgtest_main.a
[ 58%] Built target gtest_main
[ 66%] Building CXX object test/CMakeFiles/cqueue_test.dir/cqueue_test.cpp.obj
[ 75%] Linking CXX executable cqueue_test.exe
[ 83%] Linking CXX static library ..\..\lib\libgmock.a
[ 83%] Built target gmock
[ 91%] Building CXX object googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.obj
[100%] Linking CXX static library ..\..\lib\libgmock_main.a
[100%] Built target gmock_main
[100%] Built target cqueue_test

<path>\CircularQueue_with_GoogleTest>ctest  -j 12           -C Debug    --test-dir ./build/test          --extra-verbose                 --progress              --output-on-failure
Internal ctest changing into directory: <path>/CircularQueue_with_GoogleTest/build/test
UpdateCTestConfiguration  from :<path>/CircularQueue_with_GoogleTest/build/test/DartConfiguration.tcl
UpdateCTestConfiguration  from :<path>/CircularQueue_with_GoogleTest/build/test/DartConfiguration.tcl
Test project <path>/CircularQueue_with_GoogleTest/build/test
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: cqueue_test

1: Test command: <path>\CircularQueue_with_GoogleTest\build\test\cqueue_test.exe
1: Working Directory:<path>/CircularQueue_with_GoogleTest/build/test
1: Test timeout computed to be: 10000000
1: Running main() from <path>\CircularQueue_with_GoogleTest\googletest\googletest\src\gtest_main.cc
1: [==========] Running 9 tests from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 9 tests from cqueue_test
1: [ RUN      ] cqueue_test.insert_one_element_and_check_size
1: [       OK ] cqueue_test.insert_one_element_and_check_size (0 ms)
1: [ RUN      ] cqueue_test.insert_one_element_and_peek
1: [       OK ] cqueue_test.insert_one_element_and_peek (0 ms)
1: [ RUN      ] cqueue_test.insert_two_elements_and_peek
1: [       OK ] cqueue_test.insert_two_elements_and_peek (0 ms)
1: [ RUN      ] cqueue_test.insert_two_elements_and_check_size
1: [       OK ] cqueue_test.insert_two_elements_and_check_size (0 ms)
1: [ RUN      ] cqueue_test.overfill_and_check_size
1: [       OK ] cqueue_test.overfill_and_check_size (0 ms)
1: [ RUN      ] cqueue_test.overfill_and_peek
1: [       OK ] cqueue_test.overfill_and_peek (0 ms)
1: [ RUN      ] cqueue_test.overfill_and_dequeue
1: [       OK ] cqueue_test.overfill_and_dequeue (0 ms)
1: [ RUN      ] cqueue_test.insert_after_fill_then_empty
1: [       OK ] cqueue_test.insert_after_fill_then_empty (0 ms)
1: [ RUN      ] cqueue_test.overfill_many_times
1: [       OK ] cqueue_test.overfill_many_times (0 ms)
1: [----------] 9 tests from cqueue_test (0 ms total)
1:
1: [----------] Global test environment tear-down
1: [==========] 9 tests from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 9 tests.
1/1 Test #1: cqueue_test ......................   Passed    0.10 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.10 sec

<path>\CircularQueue_with_GoogleTest>pause
Press any key to continue . . .
```

<br>

<h2>Example: Using the Cqueue</h2>

This is a simple example of initializing and using a circular queue per this cqueue interface. The example includes adding of elements, printing contents, etc.

<br>

```
#include <stdio.h>
#include "cqueue.h"


int main(int argc, int** argv)
{
    char msg;

    cqueue_s myCqueue;

    // The cqueue will contain 5 chars
    cqueue_init(&myCqueue, 5, sizeof(char), NULL);

    while(1)
    {
        printf("Enter a character (or enter 'q' to quit): ");
        scanf("%s", &msg);

        if (msg == 'q')
        {
            break;
        }

        cqueue_enque(&myCqueue, &msg);
    }

    printf("\nThe count is %d.\n", cqueue_get_size(&myCqueue));

    char peek;
    cqueue_peek(&myCqueue, &peek);
    printf("A peek into cqueue reveals \'%c\' at head.\n", peek);

    printf("Here are the contents of the cqueue: ");

    while(!cqueue_is_empty(&myCqueue))
    {
        cqueue_deque(&myCqueue, &msg);
        printf("\'%s\' ", &msg);
    }

    cqueue_close(&myCqueue);

    return 0;
}
```

<br>

The output of this may look something like:

<br>

```
Enter a character (or enter 'q' to quit): 1
Enter a character (or enter 'q' to quit): 2
Enter a character (or enter 'q' to quit): 3
Enter a character (or enter 'q' to quit): q

The count is 3.
A peek into cqueue reveals '1' at head.
Here are the contents of the cqueue: '1' '2' '3'
```

<br>

or if you continue to add elements such that the tail and head collide:

<br>

```
Enter a character (or enter 'q' to quit): 1
Enter a character (or enter 'q' to quit): 2
Enter a character (or enter 'q' to quit): 3
Enter a character (or enter 'q' to quit): 4
Enter a character (or enter 'q' to quit): 5
Enter a character (or enter 'q' to quit): 6
Enter a character (or enter 'q' to quit): q

The count is 5.
A peek into cqueue reveals '2' at head.
Here are the contents of the cqueue: '2' '3' '4' '5' '6'
```
