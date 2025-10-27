#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cstdlib>

#include "Plant.h"

class Customer{
private:
    Plant wanted;
    Plant received;
public:
    Customer();
};

#endif