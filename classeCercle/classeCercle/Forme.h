
#ifndef __FORME_H__
#define __FORME_H__

#include <string>
#include <iostream>

class Forme
{
public:
    // Construction/Destruction
    Forme();
    Forme(const std::string& label, int IndProfond);    // Avec une string
    Forme(const Forme& other);          // Construction par recopie
    virtual ~Forme();

    // Operator d'affectation
    Forme& operator=(const Forme& other);

    // Accesseur
    void SetLabel(const std::string& s);
    std::string GetLabel() const;
    
    void SetIndProfond( int IndProfond);
    int GetIndProfond(); 

    // M�thodes virtuelles � d�clarer dans les classes filles
    // On d�clare la m�thode en inline (i.e. le code est directement
    // int�gr� dans la d�claration de la classe).
    virtual void Display() const
    {
        std::cout << "Je suis une Forme" << std::endl;
    }

    virtual float Surface() const { return 0.0f; }
    virtual float Perimeter() const { return 0.0f; }
    virtual float Longueur() const { return 0.0f; }

protected:  // ou private
    std::string * m_label;
    int * m_IndProfond; 
};

#endif // __FORME_H__
