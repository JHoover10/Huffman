#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <string>
struct Node{
    std::string Chars;
    int NumOfOcc;
    Node *NodeL;
    Node *NodeR;
};
#endif // NODE_H_INCLUDED
