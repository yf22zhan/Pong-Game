# Pong-Game

This is my very first SFML game that I built with the help of the tutorial http://www.gamefromscratch.com/page/Game-From-Scratch-CPP-Edition.aspx#CPlusPlus

Some key ideas from the tutorial are: 
  - ServiceLocator Design Pattern,  
  - Caching Audio Resources
  - State Driven Game Design
  - Game Object Manager
  
My own flare to it:
  - Game Start Countdown
  - Score Counter
  - Modified Paddle AI
  
Also because I used SFML 2.0 while the tutorial used 1.6, Some keywords and local code structure might be different but the idea is basically the same.

***Game Screenshots***

<br>
<img width="700" height="550" src="https://github.com/yf22zhan/Pong-Game/blob/master/screenshots/splash-screen.PNG" />
<br>
<br>
<img width="700" height="550" src="https://github.com/yf22zhan/Pong-Game/blob/master/screenshots/menu.PNG" />
<br>
<br>
<img width="700" height="550" src="https://github.com/yf22zhan/Pong-Game/blob/master/screenshots/game-start.PNG" />
<br>

***Visual Studio Project Dependencies Setup***

Project Properties -> C/C++ -> Additional Include Directories -> $(ProjectDir)/include

Project Properties -> Linker -> Additional Library Directories -> $(ProjectDir)/lib

Project Properties -> Linker -> Input -> Additional Dependencies -> sfml-network-d.lib;sfml-audio-d.lib;sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)
