This is my own game project using C++ and SDL2 libraries at University of Engineering and Technology, Vietnam National University.


#  * **`Table of Content:`**

* 1.Information
* 2.Idea
* 3.Gameplay
* 4.Milestone
* 5.Credit
* 6.Prerequisites






 **I.Information**
* Name: Trần Hoàng Sơn
* Student ID: 23020699
* Class: K68J
* Email: sorrylight1@gmail.com


**II.Idea**

This is a basic Brick Breaker game.

Your target is to destroy all the brick that appears on the screen.

To make something new and diffirent from the original game, i try to improve the game logic and expression but because the lack of knowledge and time, i could not finish the idea i had.
Im just add some horror elements, what my friend said is "funny and scary" to make my game funnier.

I chose this game because i thought it was simple. But  "it's tricky, right? "



**III.Gameplay**


1.Objective
I create 3 Objs: Paddle, Ball, Brick (which is in Field).
When the game starts, players will see the ball pop up from the center of the paddle. As the ball coming up, it hit some of the Bricks. After being hit, the brick disappears and the ball is reflected from the way it comming. 
If the ball hit the top side or left/right side or paddle, it will reflect too.

Your duty is destroy all the bricks rendered on the Field, while keeping the ball away from the bottom side of the screen. Using the paddle for that.
The paddle may move horizontally and is controlled by your keyboard. Using A D or Left and Right Arrow Button to move the paddle.


> These are screenshots when playing game:
![menu1](https://hackmd.io/_uploads/r1W_3s8b0.jpg)
This is when you open the game

![menu2](https://hackmd.io/_uploads/Hkb_nsLbA.jpg)
Clicked into the Options button

![ingame1](https://hackmd.io/_uploads/Hy-_ni8-C.jpg)
Clicked into the Play button

![endgame](https://hackmd.io/_uploads/H1Zdnj8WA.jpg)
When you let your ball touch the ground



**IV.Milestone**


* 23/2/2024 - 1/3/2024: Install SDL, Have ideas about the game.
* 1/3 - 8/3: Add object, render object to the game.
* 
* 8/3 - 15/3/2024: Learning about the colission logic, adding them into the game.
* 16/3/2024: Have error when commiting the game to github (Update was rejected), try to fix but randomly delete all the commit branch and commit history.
* 20/3/2024: Finish the game with the base logic.
* 24/3/2024: Improve the graphics quality.
* 1/4/2024: Have error with github again, luckily keep the branch remain the same. Start trying to add horror elements.
* 9/4/2024: Try changing some part in Field.h to render the bricks.
* 12/4/2024: Start to code menu
* 13/4/2024: Fixing bug and add more commits.
* 15/4/2024: fixing bug in menu
* 18-24/4: Add level, game, time in the game and an endgamescreen.
* 
* Future: (this was written at 24/4/2024) 
        - Add some levels.
        - Make the game harder: play with 2 balls, time             limit.
        - Restart game into the menu part, not directly             into game part like currently.



**V.Credit**

* I learn most of things here: http://rembound.com/articles/the-breakout-tutorial
and thanks for chat GPT 3.5 (although most of time you make my problem harder to solve).

* I use this set for paddle and bricks: https://opengameart.org/content/breakout-brick-breaker-tile-set-free
and this image for ball: https://www.shutterstock.com/search/sprite-ball
and this for pillar: https://www.realm667.com/en/repository-18489/prop-stop-mainmenu-163-64831/hell-a-magic-mainmenu-168-40302

* Music : https://pixabay.com/vi/sound-effects/search/game
* Menu: https://www.vn.freelancer.com/contest/design-a-main-menu-for-a-horror-game-1493042
* Background: https://wallhere.com/vi/wallpaper/125174

**VI.Prerequisites**
All dependencies (for Windows only)2 are in bin, include, lib folders.

C, C++
SDL2, SDL2 image, SDL2 mixer, SDL2 ttf
