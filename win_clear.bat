forfiles /p .\lib /m *.a /c "cmd /c del /q /f @path"
forfiles /p .\lib /m *.dll /c "cmd /c del /q /f @path"
forfiles /p .\lib /m lib*.so* /c "cmd /c del /q /f @path"
forfiles /p .\bin /m SHttpServer* /c "cmd /c del /q /f @path"
forfiles /p .\src /s /m *.o /c "cmd /c del /q /f @path"
forfiles /p .\src /s /m moc_* /c "cmd /c del /q /f @path"
forfiles /p .\src /s /m ui_*.h /c "cmd /c del /q /f @path"
forfiles /p .\src /s /m Makefile* /c "cmd /c del /q /f @path"
forfiles /p .\src /s /m Http.pro.user* /c "cmd /c del /q /f @path"