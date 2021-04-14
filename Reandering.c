//
// Created by nathan on 4/13/2021.
//
#include "GameCore.h"
#include "Reandering.h"
#include <string.h>
/*void fixPath(char *path){
    char *find = strstr(path,"\\");
    while (find){
        *find='\';
        find = strstr(path,"\\");
    }

}*/
void renderMapBox(SDL_Renderer *rend,MapTile map[mapsize][mapsize],SDL_Rect boxin){
    int x=boxin.w/32,y=boxin.h/32;
    for (int i = 0; i < y ; ++i) {
        for (int j = 0; j < x; ++j) {
           // if(*(trace)) {
//                SDL_Rect tmp = (*trace)->data.tile
                map[i][j].tileRect.h=32;
                map[i][j].tileRect.w=32;
                map[i][j].tileRect.x=boxin.x+(j*32);
                map[i][j].tileRect.y=boxin.y+(i*32);
                SDL_RenderDrawRect(rend, &map[i][j].tileRect);
           // }
        }
    }

}
void renderTiles(SDL_Renderer *rend,MapTile tiles[100]){
    for (int i = 0; tiles[i].tileTexture!=NULL; ++i) {
        SDL_Rect tmp=tiles[i].tileRect;
        tmp.x=tmp.x-1;
        tmp.y=tmp.y-1;
        tmp.w=tmp.w+2;
        tmp.h=tmp.h+2;
        SDL_RenderDrawRect(rend,&tmp);
        SDL_RenderCopy(rend,tiles[i].tileTexture,NULL,&tiles[i].tileRect);
    }

}
void renderTextureinput(SDL_Renderer *rend,MapTile tiles[100], char *name,int *cur){
    name[strlen(name)-1]=0;
    tiles[*cur].tileRect.h=32;
    tiles[*cur].tileRect.w=32;
    tiles[*cur].tileRect.x=((24+((*cur)%4))*32)+(5*((*cur)%4));
    tiles[*cur].tileRect.y=((1+((*cur)/4))*32)+(5*((*cur)/4));
    SDL_RenderDrawRect(rend, &tiles[*cur].tileRect);
    SDL_Surface *s = IMG_Load(name);
    tiles[*cur].tileTexture=SDL_CreateTextureFromSurface(rend,s);
    (*cur)++;
    SDL_FreeSurface(s);
    memset(name,0, sizeof(500));
}
void renderConsole( SDL_Renderer *rend,TTF_Font *font, SDL_Color color,char command[]){
    char buffer[150];
    SDL_Surface * surface;
    SDL_Texture * texture;
    strcat(buffer,"command>");
    strcat(buffer,command);
    strcat(buffer,"_");
    surface = TTF_RenderText_Solid(font, buffer, color);
    texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);


    SDL_Rect dstrect = { 0, 0,strlen(buffer)*10 ,20 };
    SDL_RenderCopy(rend,texture,NULL,&dstrect);
    SDL_DestroyTexture(texture);
}