/* 
 * Gems.h
 *
 * Definição de estrutura que modela uma célula da Matriz
 */

#ifndef GEMS_H
#define GEMS_H

typedef struct {

    SDL_Rect celula;    // Define um retângulo que será uma célula da Matriz
    SDL_Rect *clip;     // Parte da imagem que sera mostrada na célula
    int elemento;       // Código da joia

} Gems;

#endif // GEMS_H
