#ifndef LRCUBE_COLORS_H
#define LRCUBE_COLORS_H

#include <string>
#include <vector>


class Colors{
public:
    int id;
    explicit Colors(int id);
    ~Colors();

    void use();
};

extern Colors* addColors(std::string vertexFile, std::string FragmentFile);

#endif