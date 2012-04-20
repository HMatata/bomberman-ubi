rmdir /s /q "Exe"
mkdir "Exe"

for %%f in (Src\*.cpp) do call BuildOne %%f 


