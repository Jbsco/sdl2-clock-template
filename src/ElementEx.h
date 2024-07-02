#pragma once

class ElementEx:public Element{
    protected:
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_Rect SrcR,DestR;
        double posX,posY,rotate,rotateTarget,rotateFactor;
        int microCounter;
    public:
        ElementEx(SDL_Renderer *newRenderer,
            string filename,
            double startRotate,
            double newRotateFactor=0,
            double newPosX=0.0,
            double newPosY=0.0):Element(newRenderer,
                filename,
                startRotate,
                newRotateFactor,
                newPosX,
                newPosY){
            renderer=newRenderer;
            image=mm.read(renderer,filename,SrcR);
            DestR=SrcR;
            posX=newPosX;
            posY=newPosY;
            rotateFactor=newRotateFactor;
            rotate=startRotate;
            rotateTarget=rotate+6;
            microCounter=500000;
        }
        virtual void handleEvent(SDL_Event &e){}
        virtual void loop(int micros){
            DestR.x=(int)posX;
            DestR.y=(int)posY;
            SDL_Point center={160,160};
            if(rotateFactor>0){
                double dt=((float)micros)/1000000.0;
                if(rotate<0)rotate+=360;
                microCounter+=micros;
                if(microCounter<500000)rotate-=rotateFactor*dt;
                else if(rotate!=rotateTarget)rotate=rotateTarget;
                else if(microCounter>1000000){
                    microCounter-=1000000;
                    rotateTarget+=6;
                    if(rotateTarget>360)rotateTarget-=360;
                }
                // cout << microCounter << " - " << rotate << endl;
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
        virtual ~ElementEx(){
            SDL_DestroyTexture(image);
        }
};