#ifndef __LIGNE_H__
#define __LIGNE_H__

#include "Forme.h"
#include "Point.h"
#include <iostream>

class Ligne : public Forme
{
public:
    // Construction par défaut, par copie, avec paramètres
    Ligne();
    Ligne(const Point& p1, const Point& p2, int IndProfond, std::string label);
    Ligne(const Ligne &other);
    
    
    // Destructeur virtuel car on peut dériver cette classe
    virtual ~Ligne();

    // Opérateur d'affectation
    Ligne &operator=(const Ligne &other);

    // Méthodes virtuelles pour surcharger celles de la classe Mère
    virtual void Display() const override;
	virtual void Longueur() const override;

private:    // Could be protected
    Point p1;
    Point p2;

};
#endif // __LIGNE_H__
