echo Compiling Source/Target.cpp  from  Build/Objects/Target.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Target.cpp.o Source/Target.cpp
echo Compiling Source/Project.cpp  from  Build/Objects/Project.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Project.cpp.o Source/Project.cpp
echo Compiling Source/Main.cpp  from  Build/Objects/Main.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Main.cpp.o Source/Main.cpp
echo Compiling Source/Execute.cpp  from  Build/Objects/Execute.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Execute.cpp.o Source/Execute.cpp
echo Compiling Source/Platform.cpp  from  Build/Objects/Platform.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Platform.cpp.o Source/Platform.cpp
echo Compiling Source/Configuration.cpp  from  Build/Objects/Configuration.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Configuration.cpp.o Source/Configuration.cpp
echo Compiling Source/Command.cpp  from  Build/Objects/Command.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Command.cpp.o Source/Command.cpp
echo Compiling Source/Task.cpp  from  Build/Objects/Task.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Task.cpp.o Source/Task.cpp
echo Compiling Source/Parse.cpp  from  Build/Objects/Parse.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Parse.cpp.o Source/Parse.cpp
echo Compiling Source/Tool.cpp  from  Build/Objects/Tool.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Tool.cpp.o Source/Tool.cpp
echo Compiling Source/Util.cpp  from  Build/Objects/Util.cpp.o
mkdir -p Build/Objects
g++-6 -Wall -Wextra -IInclude -std=c++14 -g -DDEBUG -c -o Build/Objects/Util.cpp.o Source/Util.cpp
echo Linking Build/yabs
mkdir -p Build
g++-6 -LLibrary -o Build/yabs Build/Objects/Execute.cpp.o Build/Objects/Task.cpp.o Build/Objects/Configuration.cpp.o Build/Objects/Command.cpp.o Build/Objects/Util.cpp.o Build/Objects/Main.cpp.o Build/Objects/Platform.cpp.o Build/Objects/Project.cpp.o Build/Objects/Parse.cpp.o Build/Objects/Target.cpp.o Build/Objects/Tool.cpp.o -lstdc++fs -lyaml-cpp
