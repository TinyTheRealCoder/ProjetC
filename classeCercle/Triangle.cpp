#include "Triangle.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std; // Jamais dans un point h(pp) !

// R�servation m�moire de l'attribut statique de la classe Triangle
// static
unsigned int Triangle::m_triangleCount = 0;

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3, const std::string& label) :
    // Appel du contructeur de Forme avec un label
    Forme(label),
    // Appel des 3 constrcteurs par copies des Points
    m_p1(p1),
    m_p2(p2),
    m_p3(p3)
{
    std::cout << "Triangle (riche)" << std::endl;
    m_triangleCount++;
}

Triangle::Triangle()
{
    std::cout << "Triangle (defaut)" << std::endl;
    m_triangleCount++;
}

Triangle::~Triangle()
{
    std::cout << "~Triangle" << std::endl;
    m_triangleCount--;
}

Triangle::Triangle(const Triangle &other) :
    // Appel du contructeur de Forme avec un label
    Forme(*other.m_label),
    // Appel des 3 constrcteurs par copies des Points
    m_p1(other.m_p1),
    m_p2(other.m_p2),
    m_p3(other.m_p3)
{
    std::cout << "Triangle (copie)" << std::endl;
    m_triangleCount++;
}

Triangle &Triangle::operator=(const Triangle &other)
{
    if (this == &other) return *this; // handle self assignment

    std::cout << "Triangle (affectation)" << std::endl;
    *m_label = *other.m_label;
    m_p1 = other.m_p1;
    m_p2 = other.m_p2;
    m_p3 = other.m_p3;
    return *this;
}

// On red�finit les m�thodes virtuelles pour les affiner
float Triangle::Surface() const
// avec la formul de H�eron
{
    float a = m_p1.Distance(m_p2);
    float b = m_p1.Distance(m_p3);
    float c = m_p2.Distance(m_p3);
    float s = (a + b + c)/2. ;
    return sqrt(s*(s-a)*(s-b)*(s-c)) ;
}

float Triangle::Perimeter() const
{
    return m_p1.Distance(m_p2) + m_p1.Distance(m_p3) + m_p2.Distance(m_p3);
}

void Triangle::Display() const
{
    std::cout << "Triangle " << GetLabel() << "="
              << "(" << m_p1.GetX() << "," << m_p1.GetY() << ")"
              << "(" << m_p2.GetX() << "," << m_p2.GetY() << ")"
              << "(" << m_p3.GetX() << "," << m_p3.GetY() << ")"
              << " P=" << Perimeter() << " S=" << Surface() << std::endl;
}