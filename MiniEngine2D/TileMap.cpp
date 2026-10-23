#include "TileMap.h"
#include <fstream>
#include <iostream>
#include <sstream>

TileMap::TileMap(const std::string& filename, Texture* wallTex, Texture* floorTex, Texture* objTex)
    : width(0), height(0), tileSize(64) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open level file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        if (!row.empty()) {
            grid.push_back(row);
            if (width == 0) width = row.size();
            height++;
        }
    }
    file.close();

    std::cout << "Loaded level: " << width << "x" << height << " tiles" << std::endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int tileType = grid[y][x];
            if (tileType == 0) continue;

            Texture* tex = nullptr;
            float r = 1.0f, g = 1.0f, b = 1.0f;

            switch (tileType) {
            case 1:
                tex = wallTex;
                r = 0.5f; g = 0.5f; b = 0.5f;
                break;
            case 2:
                tex = objTex;
                r = 1.0f; g = 0.3f; b = 0.3f;
                break;
            case 3:
                tex = objTex;
                r = 0.3f; g = 0.3f; b = 1.0f;
                break;
            case 4:
                tex = objTex;
                r = 0.3f; g = 1.0f; b = 0.3f;
                break;
            }

            if (tex) {
                float px = x * tileSize + tileSize / 2.0f;
                float py = y * tileSize + tileSize / 2.0f;
                Sprite* tile = new Sprite(tex, px, py, tileSize, tileSize);
                tile->setColor(r, g, b);
                tiles.push_back(tile);
            }
        }
    }
}

void TileMap::draw(Shader& shader, Camera& camera, int screenWidth, int screenHeight) {
    for (Sprite* tile : tiles) {
        tile->draw(shader, camera, screenWidth, screenHeight);
    }
}

bool TileMap::isWall(float x, float y, float objWidth, float objHeight) const {
    float leftA = x - objWidth / 2.0f;
    float rightA = x + objWidth / 2.0f;
    float topA = y - objHeight / 2.0f;
    float bottomA = y + objHeight / 2.0f;

    for (int ty = 0; ty < height; ty++) {
        for (int tx = 0; tx < width; tx++) {
            if (grid[ty][tx] == 1) {
                float leftB = tx * tileSize;
                float rightB = leftB + tileSize;
                float topB = ty * tileSize;
                float bottomB = topB + tileSize;

                if (leftA < rightB && rightA > leftB &&
                    topA < bottomB && bottomA > topB) {
                    return true;
                }
            }
        }
    }
    return false;
}

TileMap::~TileMap() {
    for (Sprite* tile : tiles) {
        delete tile;
    }
}