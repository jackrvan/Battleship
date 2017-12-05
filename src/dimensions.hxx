#ifndef DIMENSIONS_H
#define DIMENSIONS_H


#include <QString>


class Dimensions {
public:
    static const int margin = 25;

    static const int boxSize = 35;
    static const int hudHeight = (boxSize * 5) + 300;
    static const int hudWidth = 300;

    static const int boardSize = boxSize * 10 + 2 * margin; //520

    static const int sceneHeight = boardSize;
    static const int sceneWidth = boardSize + hudWidth; 
};


#endif
