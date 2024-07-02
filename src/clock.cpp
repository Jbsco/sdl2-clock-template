#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <sys/time.h>
#include <SDL.h>     
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Exception.h"
#include "TextureInfo.h"
#include "MediaManager.h"
#include "Clock.h"
#include "Element.h"
#include "ElementEx.h"

using namespace std;

class runClock:public Clock{
    vector<Element *>elements;
    Element *background,*hours,*minutes,*seconds,*milliseconds;
    public:
        runClock(string time):Clock("clock",320,320){
            int second=stod(time.substr(17,2));
            double minute=stod(time.substr(14,2))+(second/60.);
            double hour=(stoi(time.substr(11,2))%12)+(minute/60.);
            second*=6.;
            minute*=6.;
            hour*=30.;
            // rotation factor is in degrees per second
            background=new Element(renderer,"img/background.bmp",0);
            hours=new Element(renderer,"img/hours.bmp",hour,(1./240.));
            minutes=new Element(renderer,"img/minutes.bmp",minute,.1);
            seconds=new ElementEx(renderer,"img/seconds.bmp",second,720.);
            //milliseconds=new Element(renderer,"img/milliseconds.bmp",0,360.);
            elements.push_back(background);
            elements.push_back(hours);
            elements.push_back(minutes);
            elements.push_back(seconds);
            //elements.push_back(milliseconds);
        }
        void loop(int micros){
            SDL_RenderClear(renderer);
            for(auto q:elements)q->loop(micros);
            SDL_RenderPresent(renderer);
        }
        ~runClock(){
            for(auto p:elements)delete p;
        }
};

int main(int argc,char *argv[]){
   time_t t;
   struct tm * tt;
   time (&t);
   tt = localtime(&t);
   string time=asctime(tt);
   // cout << time.substr(11,2) << ':' << time.substr(14,2) << ':' << time.substr(17,2) << endl;
    try{
        runClock c(time);
        c.doLoop();
    }catch(Exception e){
        cerr << e;
    }
    return 0;
}