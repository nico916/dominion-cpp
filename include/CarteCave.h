#ifndef CARTECAVE_H
#define CARTECAVE_H
#include <iostream>
#include "CarteAction.h"
#include "Joueur.h"

class CarteCave : CarteAction
{
    public:
        CarteCave(const std::string& nom, int prix, std::string type, int nbActions);

        virtual ~CarteCave()=default;
        //virtual void Afficher() const override ;


};

#endif // CARTECAVE_H
