clear
testFolder="./example"
comLoc="./cmake-build-debug"
for file in $testFolder/*.ynex
do
  [ -f $comLoc/Ynex.exe ] && echo "Compiling $file..." && $comLoc/Ynex $file ${file%.ynex}.cpp
  [ $? != 0 ] && echo -e "\e[0;31m[FAILED]\e[0m" || echo -e "\e[0;32m[SUCCESS]\e[0m"
done