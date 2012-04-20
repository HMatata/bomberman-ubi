path=C:\Windows\Microsoft.NET\Framework\v3.5\;%path%

msbuild /t:Clean /p:Configuration=Release Player.sln
msbuild /t:Build /p:Configuration=Release Player.sln

