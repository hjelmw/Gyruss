# Gyruss
Gyruss is an arcade game by Konami from the 1980s. This is my implementation of the game in C++ and SDL2 . The game was built using an _Entity-component-design_ pattern.

The engine, `AvancezLib`, was built as part of the course _TDA572 - Game Engine Architecture_ at Chalmers University of Technology and features:

* Sprite rendering and rotation
* Audio playback
* Basic collision detection using the AABB test

You can read a report where I explain more in detail how I implemented the engine and game [here](https://www.overleaf.com/read/dpkcwzbxrjnj)

## Gameplay description (short)
* Shoot aliens 
* Don't get hit by the aliens
* The aliens get more aggresive every level
* Powerups give life and makes your shots pierce aliens
* Aliens 👽

## Gameplay description (longer)
The enemies are spaceships which the player must destroy to progress to the next level. The aliens appear near the middle of the screen and move in swirling patterns before landing in the middle and start to shoot at the player. The player has 4 lives and gains invulnerability for a small time if hit directly by an alien or anything from its arsenal. On each level the aliens increase in number and get more aggresive. There are also powerups that spawn during gameplay. Picking one up grants the player one life, invulnerability for a short time and causes their shots to pierce aliens.

## Setup
Runnable .zip on [gdrive](https://drive.google.com/open?id=1VLEKw-lZ-Q14GqypU09ddqyNVLIMZehg)

If you instead want to build the game using this repo directly, please see this [link](https://www.wikihow.com/Set-Up-SDL-with-Visual-Studio) first. Afterwards create the folder `./Debug` in the source directory and place the DLLs for `SDL,SDL_ttf,SDL_image,SDL_mixer` in there. Make sure VS configuration is set to `x86` and compile!

## Pictures!
PNG             |  GIF
:-------------------------:|:-------------------------:
<img src="https://github.com/hjelmw/TDA572.Gyruss/blob/master/img/Gyruss_development.PNG">   |  <img src="https://github.com/hjelmw/TDA572.Gyruss/blob/master/img/Gyruss%20-%20Gameplay.gif">


## Credits
See [CREDITS.txt](https://github.com/hjelmw/TDA572.Gyruss/blob/master/CREDITS.txt)
