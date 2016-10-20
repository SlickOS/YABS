# YABS - Yet Another Build System
YABS is an open source build system with an emphasis on easily configurable builds of multiple projects.

## Why Design A New Build System?
YABS is designed from the shortcomings of other  build systems. In the development of Slick OS, a tool was needed that could handle multiple architectures, multiple projects with submodules, and multiple configurations.

Originally, GNU Make was used, and it worked reasonably well until submodules had to be added. By the time the Makefile had support for submodules, it was well over 1000 lines and entirely unmaintainable. It was then that we decided we needed a different build system. 

While going through the configurations of several build systems, we found that although what we wanted was possible using other tools, we wanted something easier to maintain and extend. YABS was thus built.

## So What Does It Look Like?
An incredibly simple build file looks like this:
```yaml
Projects:
  - Name: hello

Targets:
  - Name: Build
    Commands:
      - Shell: gcc -Wall -Wextra -o hello hello.c
  - Name: Clean
    Commands:
      - Shell: rm hello
```

The build file for YABS itself is as follows:
```yaml
Projects:
  - Name: YABS
    Variables:
      - SourceDir: Source/
      - ObjectDir: Build/Objects/
      - Binary: Build/yabs

Configurations:
  - Name: Debug
    Variables:
      - C++Flags: -g -DDEBUG

Targets:
  - Name: Build
    Commands:
      - Tool: C++ Compile($Flags, +Find($SourceDir, *.cpp), $ObjectDir)
      - Tool: C++ Link($LinkFlags, +Find($ObjectDir, *.o), $Libraries, $Binary)

  - Name: Clean
    Commands:
      - Shell: rm -rf $ObjectDir $Binary

  - Name: Rebuild
    Dependencies:
      - Clean
      - Build
```
Although the YABS build file doesn't use all of the features described before (such as multiple architectures and submodules), it does demonstrate its readability.

## So How Do I Use It?
See the [Getting Started](https://github.com/SlickOS/YABS/wiki/Getting-Started) wiki page to get YABS set up and to make your first build script. For more information on the syntax used on top of YAML, see the [Syntax](https://github.com/SlickOS/YABS/wiki/Syntax) wiki page.
