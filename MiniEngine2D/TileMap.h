#pragma once
#include <vector>
#include <string>
#include "Sprite.h"

class TileMap {
public:
    int width, height;
    int tileSize;

    TileMap(const std::string& filename, Texture* wallTex, Texture* floorTex, Texture* objTex);

    void draw(Shader& shader, Camera& camera, int screenWidth, int screenHeight);
    bool isWall(float x, float y, float objWidth, float objHeight) const;

    int getTile(int x, int y) const;

    ~TileMap();

private:
    std::vector<Sprite*> tiles;
    std::vector<std::vector<int>> grid;
};