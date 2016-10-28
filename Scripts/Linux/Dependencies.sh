echo Setting Up Dependencies
mkdir -p Library Include Dependencies
cd Dependencies
git clone https://github.com/jbeder/yaml-cpp
cd yaml-cpp
mkdir -p Build/Objects/contrib

INCLUDES="-iquote src -iquote include"
FLAGS="-O2 -Wall -Wextra -pedantic -Wno-long-long -std=c++11"
OBJECTS=""

echo Compiling src/binary.cpp  to  Build/Objects/binary.cpp.o
OBJECTS+="Build/Objects/binary.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/binary.cpp.o -c src/binary.cpp
echo Compiling src/convert.cpp  to  Build/Objects/convert.cpp.o
OBJECTS+="Build/Objects/convert.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/convert.cpp.o -c src/convert.cpp
echo Compiling src/directives.cpp  to  Build/Objects/directives.cpp.o
OBJECTS+="Build/Objects/directives.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/directives.cpp.o -c src/directives.cpp
echo Compiling src/emit.cpp  to  Build/Objects/emit.cpp.o
OBJECTS+="Build/Objects/emit.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/emit.cpp.o -c src/emit.cpp
echo Compiling src/emitfromevents.cpp  to  Build/Objects/emitfromevents.cpp.o
OBJECTS+="Build/Objects/emitfromevents.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/emitfromevents.cpp.o -c src/emitfromevents.cpp
echo Compiling src/emitter.cpp  to  Build/Objects/emitter.cpp.o
OBJECTS+="Build/Objects/emitter.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/emitter.cpp.o -c src/emitter.cpp
echo Compiling src/emitterstate.cpp  to  Build/Objects/emitterstate.cpp.o
OBJECTS+="Build/Objects/emitterstate.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/emitterstate.cpp.o -c src/emitterstate.cpp
echo Compiling src/emitterutils.cpp  to  Build/Objects/emitterutils.cpp.o
OBJECTS+="Build/Objects/emitterutils.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/emitterutils.cpp.o -c src/emitterutils.cpp
echo Compiling src/exp.cpp  to  Build/Objects/exp.cpp.o
OBJECTS+="Build/Objects/exp.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/exp.cpp.o -c src/exp.cpp
echo Compiling src/memory.cpp  to  Build/Objects/memory.cpp.o
OBJECTS+="Build/Objects/memory.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/memory.cpp.o -c src/memory.cpp
echo Compiling src/node.cpp  to  Build/Objects/node.cpp.o
OBJECTS+="Build/Objects/node.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/node.cpp.o -c src/node.cpp
echo Compiling src/node_data.cpp  to  Build/Objects/node_data.cpp.o
OBJECTS+="Build/Objects/node_data.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/node_data.cpp.o -c src/node_data.cpp
echo Compiling src/nodebuilder.cpp  to  Build/Objects/nodebuilder.cpp.o
OBJECTS+="Build/Objects/nodebuilder.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/nodebuilder.cpp.o -c src/nodebuilder.cpp
echo Compiling src/nodeevents.cpp  to  Build/Objects/nodeevents.cpp.o
OBJECTS+="Build/Objects/nodeevents.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/nodeevents.cpp.o -c src/nodeevents.cpp
echo Compiling src/null.cpp  to  Build/Objects/null.cpp.o
OBJECTS+="Build/Objects/null.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/null.cpp.o -c src/null.cpp
echo Compiling src/ostream_wrapper.cpp  to  Build/Objects/ostream_wrapper.cpp.o
OBJECTS+="Build/Objects/ostream_wrapper.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/ostream_wrapper.cpp.o -c src/ostream_wrapper.cpp
echo Compiling src/parse.cpp  to  Build/Objects/parse.cpp.o
OBJECTS+="Build/Objects/parse.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/parse.cpp.o -c src/parse.cpp
echo Compiling src/parser.cpp  to  Build/Objects/parser.cpp.o
OBJECTS+="Build/Objects/parser.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/parser.cpp.o -c src/parser.cpp
echo Compiling src/regex_yaml.cpp  to  Build/Objects/regex_yaml.cpp.o
OBJECTS+="Build/Objects/regex_yaml.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/regex_yaml.cpp.o -c src/regex_yaml.cpp
echo Compiling src/scanner.cpp  to  Build/Objects/scanner.cpp.o
OBJECTS+="Build/Objects/scanner.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/scanner.cpp.o -c src/scanner.cpp
echo Compiling src/scanscalar.cpp  to  Build/Objects/scanscalar.cpp.o
OBJECTS+="Build/Objects/scanscalar.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/scanscalar.cpp.o -c src/scanscalar.cpp
echo Compiling src/scantag.cpp  to  Build/Objects/scantag.cpp.o
OBJECTS+="Build/Objects/scantag.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/scantag.cpp.o -c src/scantag.cpp
echo Compiling src/scantoken.cpp  to  Build/Objects/scantoken.cpp.o
OBJECTS+="Build/Objects/scantoken.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/scantoken.cpp.o -c src/scantoken.cpp
echo Compiling src/simplekey.cpp  to  Build/Objects/simplekey.cpp.o
OBJECTS+="Build/Objects/simplekey.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/simplekey.cpp.o -c src/simplekey.cpp
echo Compiling src/singledocparser.cpp  to  Build/Objects/singledocparser.cpp.o
OBJECTS+="Build/Objects/singledocparser.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/singledocparser.cpp.o -c src/singledocparser.cpp
echo Compiling src/stream.cpp  to  Build/Objects/stream.cpp.o
OBJECTS+="Build/Objects/stream.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/stream.cpp.o -c src/stream.cpp
echo Compiling src/tag.cpp  to  Build/Objects/tag.cpp.o
OBJECTS+="Build/Objects/tag.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/tag.cpp.o -c src/tag.cpp
echo Compiling src/contrib/graphbuilder.cpp  to  Build/Objects/contrib/graphbuilder.cpp.o
OBJECTS+="Build/Objects/contrib/graphbuilder.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/contrib/graphbuilder.cpp.o -c src/contrib/graphbuilder.cpp
echo Compiling src/contrib/graphbuilderadapter.cpp  to  Build/Objects/contrib/graphbuilderadapter.cpp.o
OBJECTS+="Build/Objects/contrib/graphbuilderadapter.cpp.o "
g++ $INCLUDES $FLAGS -o Build/Objects/contrib/graphbuilderadapter.cpp.o -c src/contrib/graphbuilderadapter.cpp
echo Compiling src/binary.cpp  to  Build/Objects/binary.cpp.o

echo Linking Build/yaml-cpp.a
ar qc Build/libyaml-cpp.a $OBJECTS
ranlib Build/libyaml-cpp.a

cp Build/libyaml-cpp.a ../../Library/libyaml-cpp.a
cp -a include/. ../../Include/
cd ../../