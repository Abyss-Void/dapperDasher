#include "raylib.h"

int main()
{
    //window dimensions
    const int Window_width{1200}; //x axis
    const int Window_height{600}; //y axis
    //Intialize Window
    InitWindow(Window_width, Window_height, "Dapper Dasher!!");

    //accelaration due to gravity (pixels/second)/second
    const int gravity{1'200};

    //hazard variables
    Texture2D hazard = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle hazardRec{0.0, 0.0, hazard.width/8, hazard.height/8};
    Vector2 hazardPos{Window_width, Window_height - hazardRec.height};

    //hazard velocity on x in pixel/s
    int hazardVel{-600};


    //scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = Window_width/2 - scarfyRec.width/2;
    scarfyPos.y = Window_height - scarfyRec.height;

    //animation fram
    int frame{};
    //time before we update animation frame
    const float updateTime{1.0/12.0};
    //time for which animation has been running
    float runningTime{};

    //check if the rectangle is in air
    bool isInAir{};
    //Jump velocity in pixels/second
    const int jumpVal{-600};

    int velocity{0};

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        //delta Time (time since last frame)
        const float dT{GetFrameTime()};

        //apply gravity while doing ground check
        if(scarfyPos.y >= Window_height - scarfyRec.height)
        {   
            //here scarfy is on ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //here scarfy is in air
            velocity += gravity * dT;
            isInAir = true;
        }
        //jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVal;
        }

        //Update Scarfy
        hazardPos.x += hazardVel * dT;

        //Update Scarfy Y per frame
        scarfyPos.y += velocity * dT;

         //updating running time 
        runningTime += dT;
        if(runningTime >= updateTime)
        {
            runningTime = 0.0;
            //update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if(frame>5)
            {
                frame = 0;
            }
        }

        //Draw Hazard
        DrawTextureRec(hazard, hazardRec, hazardPos, WHITE);
        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec,scarfyPos, WHITE);
    
        EndDrawing();

    }
    
    UnloadTexture(scarfy);
    UnloadTexture(hazard);
    CloseWindow();

}