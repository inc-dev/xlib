@Echo Off
rem for /d /r  %%d in (.~h) do (del "%%d")
for /D /R  %%i in (*.*) do del "%%i\*.~*"
for /D /R  %%i in (*.*) do del "%%i\*.obj"