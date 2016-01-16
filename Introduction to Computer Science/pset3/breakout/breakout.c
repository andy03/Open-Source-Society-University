//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// width and height of the Paddle in pixels

#define paddleWIDTH 60
#define paddleHEIGHT 7

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
int hitsX=0;
int hitsY=0;

int main(int argc, char* argv[])
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    
    
    // velocity
    double velocityX= 1.0 + 2.0* drand48();
    double velocityY= 1.0 + 2.0* drand48();
    updateScoreboard(window,label,points);
    // wait for click before starting
    waitForClick();
    

    if(argc==2 && strcmp(argv[1], "GOD") == 0) 
    {
        while (lives > 0 && bricks > 0)
    {
    
        updateScoreboard(window,label,points);
   
    
                 
        // ensure paddle follows top cursor
       double x =getWidth(window)-getWidth(paddle);
       if(getX(ball)<getWidth(window)-getWidth(paddle))
            { x = getX(ball) ;}
        double y = getHeight(window) - 40;
        setLocation(paddle, x, y);
            
        
    
        move(ball, velocityX, velocityY);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityX = -velocityX;
            
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
            
        }
        
        // bounce off top edge of window
        else if (getY(ball) <=0)
        {
            velocityY= -velocityY;
        }
        
        //bounce off bottom edge of window
        else if (getY(ball) + getHeight(ball)>= getHeight(window))
        {
            lives--;
            
            if(lives>0) 
            {
                double x = (getWidth(window) -getWidth(ball))/2 ;
                double y = (getHeight(window) -getHeight(ball)) /2;
                setLocation(ball,x,y);
                waitForClick();
                move(ball, velocityX, velocityY);
            }
        }

        // linger before moving again
        pause(5);
        
       GObject object = detectCollision(window,ball);
      

       if(object!=NULL) 
       {  
            if(object == paddle)
            {   
                if(velocityY>0) velocityY=-velocityY;
                
                if(velocityX>0)
                   {    
                   
                        if(getX(ball) < getX(object) + paddleWIDTH/2) 
                        {
                        velocityX = -velocityX;
                       
                        }
                   }
                else 
                   {
                        if(getX(ball) > getX(object) + paddleWIDTH/2) 
                        {
                        velocityX = -velocityX;
                            
                        }
                        
                   }
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                
                removeGWindow(window,object);
                bricks--;
                points++;

                if(velocityY<0) velocityY = -velocityY;
                else velocityX = -velocityX;
                

                                   
                if (bricks % 10 == 0)
                {
                    velocityY++;
                    velocityX++;
                }
            }                 
       }
       }
    }
    else
    {
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
    
        updateScoreboard(window,label,points);
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                 
                // ensure paddle follows top cursor
               double x =getWidth(window)-getWidth(paddle);
               if(getX(event)<getWidth(window)-getWidth(paddle))
                    { x = getX(event) ;}
                double y = getHeight(window) - 40;
                setLocation(paddle, x, y);
            }
        }
    
        move(ball, velocityX, velocityY);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityX = -velocityX;
            
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
            
        }
        
        // bounce off top edge of window
        else if (getY(ball) <=0)
        {
            velocityY= -velocityY;
        }
        
        //bounce off bottom edge of window
        else if (getY(ball) + getHeight(ball)>= getHeight(window))
        {
            lives--;
            
            if(lives>0) 
            {
                double x = (getWidth(window) -getWidth(ball))/2 ;
                double y = (getHeight(window) -getHeight(ball)) /2;
                setLocation(ball,x,y);
                waitForClick();
                double velocityX= 1.0 + 2.0* drand48();
                double velocityY= 1.0 + 2.0* drand48();
                move(ball, velocityX, velocityY);
            }
        }

        // linger before moving again
        pause(5);
        
       GObject object = detectCollision(window,ball);
      

       if(object!=NULL) 
       {  
            if(object == paddle)
            {   
                if(velocityY>0) velocityY=-velocityY;
                
                if(velocityX>0)
                   {    
                   
                        if(getX(ball) < getX(object) + paddleWIDTH/2) 
                        {
                        velocityX = -velocityX;
                        }
                   }
                else 
                   {
                        if(getX(ball) > getX(object) + paddleWIDTH/2) 
                        {
                        velocityX = -velocityX;
                        }
                   }
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
      
                removeGWindow(window,object);
                bricks--;
                points++;

                
                //bottom
                if(getY(object) + getHeight(object) > getY(ball) && getY(object) +getHeight(object) < getY(ball)+getHeight(ball)) 
                  { 
                    
                     if(velocityY<0) velocityY = -velocityY;                 
                  }
                  //top
                else if(getY(object)  < getY(ball)  + getHeight(ball) && getY(object)  > getY(ball)) 
                  {
                        
                      if(velocityY>0) velocityY = -velocityY;                 
                  } 
                //right
                else if(getX(object) +getWidth(object) < getX(ball) && getX(object) +getWidth(object) > getX(ball)+ getWidth(ball)) 
                  {
                      
                      if(velocityX<0) velocityX = -velocityX;     
                  }
                  //left
                else if(getX(object) < getX(ball) + getWidth(ball) && getX(object)  > getX(ball)) 
                  {
                      
                      if(velocityX>0) velocityX = -velocityX;   
                  }
               
                
            } 
            
       }
       }
            
    }
    

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    char* colors[] = {"RED", "BLUE","GREEN", "ORANGE","YELLOW"};
    int distanceX = 4;
    int distanceY = 50;
    for(int i=0;i<ROWS;i++)
    {
    
        for(int j=0;j<COLS;j++)
            {   
                 
                GRect brick = newGRect(0,0,32,10);
                setColor(brick, colors[i]);
                setFilled(brick, true);
                double x = 0 + distanceX;
                double y = 0 + distanceY;
                setLocation(brick, x ,y );
                add(window, brick);
                distanceX = distanceX + 40;
            }
        distanceY =  distanceY + 15;
        distanceX = 4;
                
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval circle = newGOval(0, 0, 20, 20);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    double x = (getWidth(window) -getWidth(circle))/2 ;
    double y = (getHeight(window) -getHeight(circle)) /2;
    setLocation(circle,x,y);
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(0,0,paddleWIDTH,paddleHEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    double x = (getWidth(window) - getWidth(paddle))/2;
    double y = getHeight(window) -40;
    setLocation(paddle, x ,y );
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        
        return object;
    }

    // no collision
   
    return NULL;
}
