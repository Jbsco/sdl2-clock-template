#pragma once

class Clock{
    SDL_Window *win;
    SDL_bool loopStop;
    SDL_Thread *renderLoop;
    protected:
        int width,height;
        SDL_Renderer *renderer;
    public:
        Clock(string name,int newWidth=320,int newHeight=320){
            win=NULL;
            renderer=NULL;
            width=newWidth;
            height=newHeight;
            loopStop=SDL_FALSE;
            SDL_Init(SDL_INIT_VIDEO);
            win=SDL_CreateWindow(name.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                width,
                height,
                0);
            renderer=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
        }
        void doLoop(){
            renderLoop=SDL_CreateThread(Clock::renderThread,"RenderThread",(void*)this);
            while(!loopStop){
                SDL_Event event;
                while(SDL_PollEvent(&event)){
                    switch(event.type){
                        case SDL_QUIT:
                            loopStop=SDL_TRUE;
                            break;
                    }
                }
            }
        }
        static uint64_t GetTimeStamp(){ // get microseconds
            struct timeval tv;
            gettimeofday(&tv,NULL);
            return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
        }
        static int renderThread(void*clockPtr){
            Clock *clock=(Clock*)clockPtr;
            //int millis=SDL_GetTicks();
            uint64_t micros=GetTimeStamp(); // try microseconds
            while(!clock->loopStop){
                /*unsigned millisDt=SDL_GetTicks()-millis;
                if(millisDt>1){
                    clock->loop(millisDt);
                    millis=SDL_GetTicks();
                }*/
                uint64_t microsDt=GetTimeStamp()-micros;
                if(microsDt>(uint64_t)1000000./60.){
                    clock->loop(microsDt);
                    micros=GetTimeStamp();
                }
            }
            return 0;
        }
        virtual void loop(int micros)=0;
        ~Clock(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(win);
            SDL_Quit();
        }
};