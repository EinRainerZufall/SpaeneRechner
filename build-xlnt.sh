#!/bin/bash
set -ex 

# Released xlnt version 1.5.0 does not build on macOS
git clone https://github.com/tfussell/xlnt.git
cd xlnt/third-party && git clone https://git.codesynthesis.com/libstudxml/libstudxml.git
cd ..
cmake -DCMAKE_BUILD_TYPE=Release . && cmake --build .
