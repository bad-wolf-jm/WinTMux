echo off
"%MSBUILD_VCVARSALL_BAT%"  x64 && cmake --build ./Build --target clean