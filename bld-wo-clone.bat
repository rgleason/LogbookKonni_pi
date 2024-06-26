REM As described in
REM https://github.com/Rasbats/managed_plugins/wiki/Local-Build

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
set WXWIN=C:\Users\fcgle\source\wxWidgets
set wxWidgets_ROOT_DIR=%WXWIN%
set wxWidgets_LIB_DIR=%WXWIN%\lib\vc_dll
SET PATH=%PATH%;%WXWIN%;%wxWidgets_LIB_DIR%;C:\Program Files (x86)\Poedit\Gettexttools\bin;
set PATH=C:\Program Files\Cmake\bin;%PATH%

REM Example Only. Change shipdriver_pi to match the repo being used.
REM cd shipdriver_pi

mkdir  build
cd build
cmake -T v141_xp ..
cmake -G "Visual Studio 15 2017" --config RelWithDebInfo  ..  
cmake --build . --target tarball --config RelWithDebInfo >output.txt

cmd /k
