@echo off
set /P var=" "
mkdir C:\Games\Jinek_Games
mkdir C:\Games\Jinek_Games\Flappy_bird
mkdir C:\Games\Jinek_Games\Flappy_bird\v2_0
copy /Y "%cd%\files\game" C:\Games\Jinek_Games\Flappy_bird\v2_0\Flappy_Bird2.0.exe
copy /Y "%cd%\files\link.lnk" "%appdata%\Microsoft\Windows\Start Menu\Flappy_Bird2.0.lnk"




@pause