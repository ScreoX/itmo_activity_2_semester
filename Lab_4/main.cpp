#include <iostream>
#include "vector"
#include <algorithm>
#include "Equilateral_Triangle.h"
#include "Parallelogram.h"


enum Figure
{
    EQUILATERAL_TRIANGLE = 1,
    PARALLELOGRAM = 2,
};

enum Commands {
    ADD_FIGURE = 1,
    SHOW_ALL_FIGURES,
    SUM_PERIMETERS_OF_FIGURES,
    SUM_AREAS_OF_FIGURES,
    CENTRE_MASS_OF_FIGURE,
    TOTAL_MEMORY_FOR_FIGURES,
    SORTING_FIGURES_BY_MASS,
    END
};
int main() {

    std::vector<IFigure*> system;
    
    int command;
    double x, y, sumP, sumS, massAll;
    CVector2D centerMass;
    while(true) {

        std::cout << "\n1. Add figure\n" ;
        std::cout << "2. Show all figures\n" ;
        std::cout << "3. Sum of figure's perimeters \n" ;
        std::cout << "4. Sum of figure's areas\n" ;
        std::cout << "5. Center of system mass\n" ;
        std::cout << "6. Sum of figure's memory\n" ;
        std::cout << "7. Sort figures by mass\n" ;
        std::cout << "8. END\n" ;
        std::cout << "\nAdd command:\n";

        std::cin >> command;

        switch (command) {
            case ADD_FIGURE:

                std::cout << "1. Triangle";
                std::cout << "\n2. Parallelogram";
                std::cout << "\nAdd command:\n";
                std::cin >> command;

                switch (command) {
                    case EQUILATERAL_TRIANGLE:
                        system.push_back(new Equilateral_Triangle());
                        break;
                    case PARALLELOGRAM:
                        system.push_back(new Parallelogram());
                        break;
                    default:
                        std::cout << "\nFigure not found";
                        break;
                }
                break;
            case SHOW_ALL_FIGURES:
                for (IFigure*& figure : system) {
                    figure->draw();
                }
                break;
            case SUM_PERIMETERS_OF_FIGURES:
                sumP = 0;
                for (IFigure*& figure : system) {
                    sumP += figure->perimeter();
                }
                std::cout << "Perimeters sum of system: " << sumP << "\n";
                break;
            case SUM_AREAS_OF_FIGURES:
                sumS = 0;
                for (auto& figure : system) {
                    sumS += figure->square();
                }
                std::cout <<"Area system: " << sumS << "\n";
                break;
            case CENTRE_MASS_OF_FIGURE:
                massAll = 0;
                x = 0;
                y = 0;
                for (IFigure*& figure : system) {
                    x += figure->position().x * figure->mass();
                    y += figure->position().y * figure->mass();
                    massAll += figure->mass();
                }
                centerMass.x = x / massAll;
                centerMass.y = y / massAll;
                std::cout << "Center weight coords: " << centerMass << "\n";
                break;
            case TOTAL_MEMORY_FOR_FIGURES:
                std::cout << "Figures memory: ";
                for (IFigure*& figure : system) {
                    std::cout << figure->size() << " ";
                }
                std::cout<<'\n';
                break;
            case SORTING_FIGURES_BY_MASS:
                sort(system.begin(), system.end(), [](IFigure* x, IFigure* y) {return *x < *y; });
                std::cout << "\nFigures weight: ";
                for (IFigure*& figure : system) {
                    std::cout << figure->mass() << " ";
                }
                std::cout<<'\n';
                break;

            case END:
                return 0;

            default:
                std::cout << "Figure not found\n";

                break;
        }
    }
}
