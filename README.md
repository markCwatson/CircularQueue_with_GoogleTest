<h1>Unit Testing Circular Queue (cqueue) with Google Test</h1>

<h2>Setup</h2>
The <a href="https://github.com/google/googletest">Google Test</a> framework is being used to test cqueue. I built and ran the project in Visual Studio Code. Builds/links successfully using the following toolchains:

<br>

```
GCC 11.2.0 x86_64-w64-mingw32
GCC 12.2.0 x86_64-w64-mingw32
```

<br>

Install chocolatey (a package manager for Windows) and mingw (a compiler toolchain). You will also need to install cmake (a build system manager) which includes ctest (a framework for uniesting supported by cmake). Be sure to add `<your cmake install dir>\CMake\bin` to the PATH variable.

```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

choco install mingw
choco install cmake --pre
```

<br>
To clone this repo and bring in googletest as a sbmodule (required), use

```
git clone --recurse-submodules https://github.com/markCwatson/CircularQueue_with_GoogleTest.git
```

<br>

<h2>Example</h2>
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

<h3>Running example.exe: (1):</h3>

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

<h3>Running example.exe: (2):</h3>

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
