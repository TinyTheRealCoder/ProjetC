#ifndef __CERCLE_H__
#define __CERCLE_H__

#include "Forme.h"
#include "Point.h"
#include <iostream>

class Cercle : public Forme
{
public:
    // Construction par d�faut, par copie, avec param�tres
    Cercle();
    Cercle(const Cercle &other);
    Cercle(Point centre, int radius, std::string label);

    // Destructeur virtuel car on peut d�river cette classe
    virtual ~Cercle();

    // Op�rateur d'affectation
    Cercle &operator=(const Cercle &other);

    // M�thodes virtuelles pour surcharger celles de la classe M�re
    virtual float Surface() const override;
    virtual float Perimeter() const override;
    virtual void Display() const override;

private:    // Could be protected
    Point m_center;
    int m_radius;

    static unsigned int m_circleCount;
};
#endif // __CERCLE_H__