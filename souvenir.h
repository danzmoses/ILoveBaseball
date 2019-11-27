#ifndef SOUVENIR_H
#define SOUVENIR_H

struct Souvenir
{
    std::string name;
    double price;
    Souvenir(std::string n, double p) { this->name = n;
                                        this->price = p; }
};

#endif // SOUVENIR_H
