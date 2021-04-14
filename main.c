#include <stdio.h>
#include "GameCore.h"
#include "Reandering.h"

char *getnext(char command[500]){
    char *out=NULL;
    int size=strlen(command);
    if(strlen(command)!=0) {
        out=(char *)malloc(500);
        memset(out, 0, sizeof(500));
        int i =0;
        for (; command[i] != '\n' && command[i] != ' '; ++i) {
            sprintf(out, "%s%c", out, command[i]);
            command[i] = 0;
        }
        command[i]=0;
        char *tmp=(char *)malloc(500);
        memcpy(tmp,command+(i+1),(size-i));
        memset(command,0, sizeof(500));
        strcpy(command,tmp);
    }
    return out;
}
int binSearchTiles(MapTile list[100], int size,int x,int y){
    int y_lim=size/4;
    int looking=y_lim/2;
    int y_lock=-1;
    int find=-1;
    while (y_lock == -1) {
        if (y >= list[(looking * 4)].tileRect.y && y <= list[(looking * 4)].tileRect.y + 32) {
            y_lock = (looking * 4);
        } else {
            if (y >= list[(looking * 4)].tileRect.y) {
                looking = looking + ((y_lim - looking) / 2);
            } else {
                y_lim = looking;
                looking = y_lim / 2;
            }
        }
    }
    looking=y_lock+2;
    while (find==-1) {
        if(looking/4>y_lock||(looking/4)<y_lock||looking<0){
            return -1;
        }
        if(x >= list[looking].tileRect.x && x <= list[looking].tileRect.x+32){
            find=looking;
        } else{
            if(x >= list[looking].tileRect.x && list[looking].tileRect.x!=0 && looking==2)
                looking++;
            else
                looking--;

        }
    }
    return find;
}
int main(int argc, char **argv) {
    char command[500];
    memset(command,0, sizeof(command));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *win = SDL_CreateWindow("CGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ((mapsize+7) * 32),
                                       ((mapsize+2) * 32), SDL_WINDOW_OPENGL);
    if (!win) {
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    if (!rend) {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 2;
    }

    TTF_Font * font = TTF_OpenFont("clacon.ttf", 20);
    SDL_Color color = { 255,255,255 };
    SDL_Event event;int running=1;
    MapTile map[mapsize][mapsize];
    MapTile tiles[100];
    int cur=0,selected=-1;
    while (running)
    {
        SDL_RenderClear(rend);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if(event.type==SDL_KEYDOWN){
                if(event.key.keysym.scancode==SDL_SCANCODE_BACKSPACE){
                    command[strlen(command)-1]=0;
                } else if(event.key.keysym.scancode==SDL_SCANCODE_RETURN){
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Run");
                    strcat(command,"\n");
                    char *tmp=getnext(command);
                    while (tmp){
                        if(strcmp(tmp,"load")==0){
                            renderTextureinput(rend,tiles,command,&cur);
                        }
                        tmp=getnext(command);
                    }
                }
            }
            if(event.type==SDL_TEXTINPUT){
                strcat(command,event.text.text);
                //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"command:%s",command);

            }
            if(event.type==SDL_DROPFILE){
                char *path= event.drop.file;
                memset(command ,0 , sizeof(command));
                strcat(command,path);
                strcat(command,"\n");
                renderTextureinput(rend,tiles,command,&cur);
                SDL_RaiseWindow(win);
            }
            if(event.type==SDL_MOUSEBUTTONUP){
                if(cur>0) {
                    if ((event.button.x >= (24 * 32) && event.button.x <= (28 * 32) + 15) && ((event.button.y <= (1 + cur / 4) * 32)+32 && event.button.y >= 32)) {
                        selected=binSearchTiles(tiles,cur,event.button.x,event.button.y);
                    }
                }
            }

        }
        SDL_Rect box;
        box.x=32;
        box.y=32;
        box.h=(mapsize*32);
        box.w=(mapsize*32);
        SDL_SetRenderDrawColor(rend,000,255,0,0);
        SDL_RenderDrawRect(rend,&box);
        SDL_SetRenderDrawColor(rend,255,0,0,0);
        renderMapBox(rend,map,box);
        renderConsole(rend,font,color,command);
        renderTiles(rend,tiles);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderPresent(rend);
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
