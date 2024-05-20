#!/bin/bash

pushd ..
Vendor/bin/premake/Linux/premake5 --cc=clang gmake2
popd