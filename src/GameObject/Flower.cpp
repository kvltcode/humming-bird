#include "Flower.h"

Flower::Flower(Texture2D texture, FlowerType type, Vector2 position, Vector2 scale):
GameObject(texture, position, scale)
{
    //this is a very basic factory. can really do this for all game objects
    switch(type)
    {
        case FlowerType::FlowerB:
        {
            //279, 300
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (7 * scale.x), position.y  + (137  * scale.y), 59 * scale.x, 62 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (64 * scale.x), position.y + (8  * scale.y), 106 * scale.x, 292 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (170 * scale.x), position.y + (106  * scale.y), 87 * scale.x, 177 * scale.y));
            break;
        }

        case FlowerType::FlowerC:
        {
           //393, 300
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (11 * scale.x), position.y  + (44  * scale.y), 107 * scale.x, 70 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (56 * scale.x), position.y + (152  * scale.y), 62 * scale.x, 146 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (118 * scale.x), position.y + (5  * scale.y), 79 * scale.x, 293 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (197 * scale.x), position.y + (51  * scale.y), 134 * scale.x, 247 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (330 * scale.x), position.y + (159  * scale.y), 57 * scale.x, 81 * scale.y));
            break;
        }

        case FlowerType::FlowerD:
        {
            //425, 300
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (16 * scale.x), position.y  + (142  * scale.y), 355 * scale.x, 144 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (371 * scale.x), position.y + (177  * scale.y), 44 * scale.x, 109 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (99 * scale.x), position.y + (12  * scale.y), 114 * scale.x, 130 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (212 * scale.x), position.y + (58  * scale.y), 101 * scale.x, 84 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (313 * scale.x), position.y + (92  * scale.y), 51 * scale.x, 50 * scale.y));
            break;
        }

        case FlowerType::FlowerE:
        {
            //145, 300
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (4 * scale.x), position.y  + (104  * scale.y), 25 * scale.x, 106 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (27 * scale.x), position.y + (10  * scale.y), 35 * scale.x, 46 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (27 * scale.x), position.y  + (54  * scale.y), 78 * scale.x, 241 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (104 * scale.x), position.y + (85  * scale.y), 41 * scale.x, 121 * scale.y));
            break;
        }

        default:
        {
            //234, 300
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (6 * scale.x), position.y  + (85  * scale.y), 59 * scale.x, 29 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (63 * scale.x), position.y + (11  * scale.y), 76 * scale.x, 288 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (138 * scale.x), position.y + (68  * scale.y), 47 * scale.x, 231 * scale.y));
            mBoundingRects.push_back(std::make_unique<BoundingRect>(position.x + (185 * scale.x), position.y + (135  * scale.y), 47 * scale.x, 87 * scale.y));
        }
    }      

    mVelocity = 300;  
}