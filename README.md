# What is it?
This library generate some kind of cave map from continous 2D noise function (perlin, simplex, etc.).

# Preparation
```bash
git clone https://github.com/omgbebebe/libcavegen.git cavegen
cd cavegen
git submodule update --init --recursive
```

# Build
```bash
mkdir build && cd build
cmake ../
make
```

# Tests
```
make test
```

# Example application
```
# in build directory
./example1
```
