#pragma once 

class MediaManager{
    map<string,TextureInfo>images;
    public:
        SDL_Texture *read(SDL_Renderer *renderer,string filename,SDL_Rect &SrcR){
            if(images.find(filename)==images.end()){
            SDL_Texture *image=NULL;
            SDL_Surface *bitmapSurface=NULL;
            bitmapSurface=SDL_LoadBMP(filename.c_str());
            if(bitmapSurface==NULL)throw Exception("BMP failed to load"+filename);
            SDL_SetColorKey(bitmapSurface,SDL_TRUE,SDL_MapRGB(bitmapSurface->format,0,0,255));
            SrcR.x=0;
            SrcR.y=0;
            SrcR.w=bitmapSurface->w;
            SrcR.h=bitmapSurface->h;
            image=SDL_CreateTextureFromSurface(renderer,bitmapSurface);
            SDL_FreeSurface(bitmapSurface);
            images[filename]=TextureInfo(image,SrcR);
            return image;
        }
        TextureInfo texture=images[filename];
        SrcR=texture.srcRect;
        return texture.texture;
        }
};
MediaManager mm;
