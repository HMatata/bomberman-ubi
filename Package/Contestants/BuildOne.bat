@echo off
IF "%~1"=="" GOTO error

echo Building %~n1...

@echo on
rmdir /s /q "Player"
rmdir /s /q "Lib"
rmdir /s /q "tmp"
rmdir /s /q "Bin"

mkdir "Player"
mkdir "Player\Player"
mkdir "Lib"
mkdir "Lib\Release"

copy /Y "../Player/Player\*.sln" "Player"
copy /Y "../Player/Player\*.bat" "Player"
copy /Y "../Player/Player\Player\*.h" "Player\Player"
copy /Y "../Player/Player\Player\*.vcproj" "Player\Player"
copy /Y "../Player/Lib/Release\*.lib" "Lib/Release"

copy /Y %1 "Player\Player\main.cpp"

cd "Player"
call Build.bat
cd ..

move /Y "Bin\Player.exe" "Exe\%~n1.exe"
move /Y "Bin\Player.pdb" "Exe\%~n1.pdb"

rmdir /s /q "Player"
rmdir /s /q "Lib"
rmdir /s /q "tmp"
rmdir /s /q "Bin"

@echo off
echo Finished building %~n1!

GOTO end

:error
echo Error!!!
pause

:end