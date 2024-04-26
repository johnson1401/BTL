This is my game project using C++ and SDL2 libraries at University of Engineering and Technology, Vietnam National University.


#  * **`Table of Content:`**

1. [Information](#iinformation)
2. [Idea](#iiidea)
3. [Gameplay](#iiigameplay)
4. [Milestone](#ivmilestone)
5. [Credit](#vcredit)
6. [Prerequisites](#viprerequisites)






 ## **I.Information**
* Name: Trần Hoàng Sơn
* Student ID: 23020699
* Class: K68J
* Email: sorrylight1@gmail.com


## **II.Idea**

This is a basic Brick Breaker game.

Your target is to destroy all the bricks that appear on the screen.

To make something new and different from the original game, I tried to improve the game's logic and expression but because of my lack of knowledge and time, I could not finish the idea I had.
I'm just adding some horror elements, what my friend said is "funny and scary" to make my game funnier.

I chose this game because I thought it was simple. But  "it's tricky, right? "



## **III.Gameplay**


 
I created 3 Objs: Paddle, Ball, and Brick (which is in Field).
When the game starts, players will see the ball pop up from the center of the paddle. As the ball came up, it hit some of the Bricks. After being hit, the brick disappears and the ball is reflected from the way it coming. 
If the ball hits the top side or left/right side or paddle, it will reflect too.

You must destroy all the bricks rendered on the Field, while keeping the ball away from the bottom side of the screen. Using the paddle for that.
The paddle may move horizontally and is controlled by your keyboard. Use A D or Left and Right Arrow buttons to move the paddle.


> These are screenshots when playing the game:


![menu1](https://github.com/johnson1401/BTL/assets/160694445/01034f6e-b475-44c2-a685-18702fba9873)
This is when you open the game

![menu2](https://github.com/johnson1401/BTL/assets/160694445/72c7a3dd-975c-4ef9-8a02-6065a5f4bd76)
Clicked on the Options button

![ingame1](https://github.com/johnson1401/BTL/assets/160694445/9d0f7f03-b172-4757-969a-48408d9046b7)
Clicked on the Play button

![endgame](https://github.com/johnson1401/BTL/assets/160694445/c4d9756a-d56a-4e83-a3c4-79a6ce3b86d5)
When you let your ball touch the ground



## **IV.Milestone**


* 23/2/2024 - 1/3/2024: Install SDL, Have ideas about the game.
* 1/3 - 8/3: Add object, render object to the game.
* 
* 8/3 - 15/3/2024: Learning about the collision logic, and adding them into the game.
* 16/3/2024: Have an error when committing the game to Git Hub (Update was rejected), try to fix it but randomly delete all the commit branches and commit history.
* 20/3/2024: Finish the game with the base logic.
* 24/3/2024: Improve the graphics quality.
* 1/4/2024: Have an error with GitHub again, luckily the branch remains the same. Start trying to add horror elements.
* 9/4/2024: Try changing some parts in Field.h to render the bricks.
* 12/4/2024: Start to code menu
* 13/4/2024: Fixing bug and add more commits.
* 15/4/2024: fixing bug in menu
* 18-24/4: Add level, game, time in the game, and an endgame screen.
* 
* Future: (this was written on 24/4/2024) 
        - Add some levels.
        - Make the game harder: play with 2 balls, time limit.
        - Restart game into the menu part, not directly into the game part like currently.



## **V.Credit**

* I learn most of things here: http://rembound.com/articles/the-breakout-tutorial
and thanks for chat GPT 3.5 (although most of the time you make my problem harder to solve).

* I use this set for paddle and bricks: https://opengameart.org/content/breakout-brick-breaker-tile-set-free

and this image for the ball: https://www.shutterstock.com/search/sprite-ball

and this for pillar: https://www.realm667.com/en/repository-18489/prop-stop-mainmenu-163-64831/hell-a-magic-mainmenu-168-40302

* Music : https://pixabay.com/vi/sound-effects/search/game
* Menu: https://www.vn.freelancer.com/contest/design-a-main-menu-for-a-horror-game-1493042
* Background: https://wallhere.com/vi/wallpaper/125174

## **VI.Prerequisites**

All dependencies (for Windows only)2 are in bin, include, lib folders.
C, C++ SDL2, SDL2 image, SDL2 mixer, SDL2 ttf.
You may need to install g++ mingw on your computer to run it.

