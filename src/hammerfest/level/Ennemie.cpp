#include "Ennemie.h"

Ennemie::Ennemie(int id, int x, int y, int type) :
Position((x * 20) + 10, (y * 20) + 20), Drawable(), HitBox(), IdElement(id) {
    this->type = type;
    this->id = id;
    this->animIdx = 0;
    switch (type) {
        case cerise:
            animIdxMax = Sprite::Instance().getAnimationSize("cerise_walk");
            break;
        case orange:
            animIdxMax = Sprite::Instance().getAnimationSize("orange_walk");
            break;
        case pomme:
            animIdxMax = Sprite::Instance().getAnimationSize("pomme_walk");
            break;
        case banane:
            animIdxMax = Sprite::Instance().getAnimationSize("banane_walk");
            break;
        case citron:
            animIdxMax = Sprite::Instance().getAnimationSize("citron_walk");
            break;
        case bombinos:
            animIdxMax = Sprite::Instance().getAnimationSize("bombinos_walk");
            break;
        case poire:
            animIdxMax = Sprite::Instance().getAnimationSize("poire_walk");
            break;
        case abricot:
            animIdxMax = Sprite::Instance().getAnimationSize("abricot_walk");
            break;
        case litchi:
            animIdxMax = Sprite::Instance().getAnimationSize("litchi_walk");
            break;
        case fraise:
            animIdxMax = Sprite::Instance().getAnimationSize("fraise_walk");
            break;
        case kiwi:
            animIdxMax = Sprite::Instance().getAnimationSize("kiwi_walk");
            break;
        case pasteque:
            animIdxMax = Sprite::Instance().getAnimationSize("pasteque_walk");
            break;
        case ananas:
            animIdxMax = Sprite::Instance().getAnimationSize("annanas_walk");
            break;
        case blob:
            animIdxMax = Sprite::Instance().getAnimationSize("blob_walk");
            break;
        case framboise:
            animIdxMax = Sprite::Instance().getAnimationSize("framboise_walk");
            break;
        case nainbricot:
            animIdxMax = Sprite::Instance().getAnimationSize("abricot_walk");
            break;
    }
    
    
    
}

Ennemie::~Ennemie() {
    
}

void Ennemie::doSomething(SDL_Surface * dest) {
    SDL_Surface * t = NULL;
    if(animIdx >= animIdxMax){
        animIdx = 0;
    }
    switch (type) {
        case cerise:
            t = Sprite::Instance().getAnimation("cerise_walk", animIdx);
            break;
        case orange:
            t = Sprite::Instance().getAnimation("orange_walk", animIdx);
            break;
        case pomme:
            t = Sprite::Instance().getAnimation("pomme_walk", animIdx);
            break;
        case banane:
            t = Sprite::Instance().getAnimation("banane_walk", animIdx);
            break;
        case citron:
            t = Sprite::Instance().getAnimation("citron_walk", animIdx);
            break;
        case bombinos:
            t = Sprite::Instance().getAnimation("bombinos_walk", animIdx);
            break;
        case poire:
            t = Sprite::Instance().getAnimation("poire_walk", animIdx);
            break;
        case abricot:
            t = Sprite::Instance().getAnimation("abricot_walk", animIdx);
            break;
        case litchi:
            t = Sprite::Instance().getAnimation("litchi_walk", animIdx);
            break;
        case fraise:
            t = Sprite::Instance().getAnimation("fraise_walk", animIdx);
            break;
        case kiwi:
            t = Sprite::Instance().getAnimation("kiwi_walk", animIdx);
            break;
        case pasteque:
            t = Sprite::Instance().getAnimation("pasteque_walk", animIdx);
            break;
        case ananas:
            t = Sprite::Instance().getAnimation("annanas_walk", animIdx);
            break;
        case blob:
            t = Sprite::Instance().getAnimation("blob_walk", animIdx);
            break;
        case framboise:
            t = Sprite::Instance().getAnimation("framboise_walk", animIdx);
            break;
        case nainbricot:
            t = Sprite::Instance().getAnimation("abricot_walk", animIdx);
            break;
    }
    copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h));
    animIdx++;
}
