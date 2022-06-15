#ifndef __CERCLE_H__
#define __CERCLE_H__

#include "Forme.h"
#include "Point.h"
#include <iostream>

class Cercle : public Forme
{
public:
    // Construction par défaut, par copie, avec paramètres
    Cercle();
    Cercle(const Cercle &other);
    Cercle(Point centre, int radius, int IndProfond, std::string label);

    // Destructeur virtuel car on peut dériver cette classe
    virtual ~Cercle();

    // Opérateur d'affectation
    Cercle &operator=(const Cercle &other);

    // Méthodes virtuelles pour surcharger celles de la classe Mère
    virtual float Surface() const override;
    virtual float Perimeter() const override;
    virtual void Display() const override;
    

private:    // Could be protected
    Point m_center;
    int m_radius;

    static unsigned int m_circleCount;
};
#endif // __CERCLE_H__
