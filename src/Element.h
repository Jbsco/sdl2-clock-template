#pragma once

class Element{
    protected:
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_Rect SrcR,DestR;
        double posX,posY,rotate,rotateFactor;
    public:
        Element(SDL_Renderer *newRenderer,
                string filename,
                double startRotate,
                double newRotateFactor=0,
                double newPosX=0.0,
                double newPosY=0.0){
            renderer=newRenderer;
            image=mm.read(renderer,filename,SrcR);
                DestR=SrcR;
                posX=newPosX;
                posY=newPosY;
                rotateFactor=newRotateFactor;
                rotate=startRotate;
        }
        virtual void handleEvent(SDL_Event &e){}
        virtual void loop(int micros){
            DestR.x=(int)posX;
            DestR.y=(int)posY;
            SDL_Point center={160,160};
            if(rotateFactor>0){
                double dt=((float)micros)/1000000.0;
                if(rotate>180)rotate-=359.999;
                if(rotate<-180)rotate+=359.999;
                rotate+=rotateFactor*dt;
//Try making the second hand tick, but swing in reverse the full-way round the clock face, to reach the next 6° point, for half of the second, and pause the other half
                SDL_RenderCopyEx(renderer,
                    image,
                    &SrcR,
                    &DestR,
                    rotate,
                    &center,
                    SDL_FLIP_NONE);
            }
            else SDL_RenderCopy(renderer,image,&SrcR,&DestR);
        }
        virtual void changeImage(string newFilename){
            image=mm.read(renderer,newFilename,SrcR);
        }
        virtual ~Element(){
            SDL_DestroyTexture(image);
        }
};
