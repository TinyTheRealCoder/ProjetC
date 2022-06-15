#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <string>

#include "Forme.h"
#include "Point.h"

class Triangle : public Forme
{
public:

    // Constructeurs
    // Pour aller au bout du raisonnement, le passage par référence const est plus
    // rapide et plus sûr (pas de modification possible des objets, pas de copies inutiles)
    Triangle(const Point& s1, const Point& s2, const Point& s3, int IndProfond, const std::string& label);
    Triangle();
    Triangle(const Triangle &other);

    // Destructeur virtuel
    virtual ~Triangle();

    // Affectation
    Triangle &operator=(const Triangle &other);

    // Méthodes virtuelles que l'on affine
    virtual float Surface() const override;
    virtual float Perimeter() const override;
    virtual void Display() const override;
	
	
// Pourrait aussi être "protected:"
private:
    // On pourrait prendre un tableau de 3 Points aussi
    Point m_p1;
    Point m_p2;
    Point m_p3;

    // Pour compter les triangles
    static unsigned int m_triangleCount;
};

#endif // __TRIANGLE_H__
