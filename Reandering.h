//
// Created by nathan on 4/13/2021.
//

#ifndef CGAME_DEVTOOLS_REANDERING_H
#define CGAME_DEVTOOLS_REANDERING_H

#endif //CGAME_DEVTOOLS_REANDERING_H
void renderMapBox(SDL_Renderer *rend,MapTile map[mapsize][mapsize],SDL_Rect boxin);
void renderTextureinput(SDL_Renderer *rend,MapTile tiles[100], char *name,int *cur);
void renderConsole( SDL_Renderer *rend,TTF_Font *font, SDL_Color color,char command[]);
void renderTiles(SDL_Renderer *rend,MapTile tiles[100]);