#include <iostream>
#include <cstdlib>
#include <string>

#include "Ligne.h"

using namespace std;

//static
int Ligne::nbLigne = 0;

//Default constructor
Ligne::Ligne() : Forme()
{
    p1 = new Point();
    p2 = new Point();
}

//Constructor

Ligne::Ligne(const Point& p1Tmp, const Point& p2Tmp, int IndProfond, std::string& label) : Forme (label, IndProfond)
{
    *p1 = p1Tmp;
    *p2 = p2Tmp;

    //Point center((x1 + x2)/2, (y1 + y2)/2);
    //Forme(string("Ligne"), center);

}

//Copy constructor

Ligne::Ligne(const Ligne& copy): Forme(copy.GetLabel(), copy.GetIndProfond())
{
    p1->SetX(copy.p1->GetX());
    p2->SetX(copy.p2->GetX());
    p1->SetY(copy.p1->GetY());
    p2->SetY(copy.p2->GetY());
}

//Destructeur
Ligne::~Ligne()
{
    cout << "~Ligne" << endl;
    nbLigne--;
}

// Accesseur 

//Setter

void Ligne::SetX1(int x)
{
    p1->SetX(x);
}

void Ligne::SetX2(int x)
{
    p2->SetX(x);
}

void Ligne::SetY1(int y)
{
    p1->SetY(y);
}

void Ligne::SetY2(int y)
{
    p2->SetY(y);
}

//GETTERS

int Ligne::GetX1()
{
    return p1->GetX();
}

int Ligne::GetX2()
{
    return p2->GetX();
}

int Ligne::GetY1()
{
    return p1->GetY();
}

int Ligne::GetY2()
{
    return p2->GetY();
}

/*
//-------------------------------------------
void Ligne::Display() const
//-------------------------------------------
{
    // On affiche le nom
    /*
    std::cout << "Ligne " << GetLabel() << "= (";
    m_corner.Display();
    cout << " w=" << m_w << " h=" << m_h << ")"
    << " P=" << Perimeter() << " S=" << Surface() << endl;
    
}*/
