echo Setting Up Dependencies
brew install gcc
brew install cmake
export CXX=g++-6

mkdir -p Library Include Dependencies
cd Dependencies
git clone https://github.com/jbeder/yaml-cpp
cd yaml-cpp
mkdir Build && cd Build
cmake ../
make
cp libyaml-cpp.a ../../../Library/
cd ../
cp include/. ../../Include
cd ../..