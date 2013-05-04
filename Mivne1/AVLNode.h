//
//  AVLNode.h
//  Mivne1
//
//  Created by Aviad Rom on 4/26/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_AVLNode_h
#define Mivne1_AVLNode_h
template <typename T>
class AVLNode{
public:
    T _Data;
    int _Balance;
    int _Height;
    AVLNode *_Left, *_Right, *_Parent;
    
    
    AVLNode<T>(){
        _Balance=0;
        _Height=0;
        _Left=NULL;
        _Right=NULL;
        _Parent=NULL;
    };
    AVLNode<T>(T Data):_Data(Data),_Balance(0),_Height(0),_Left(NULL),
    _Right(NULL),_Parent(NULL){}
    
    ~AVLNode(){}
    
    const bool operator<(AVLNode<T>& Comperator) {
        return (_Data < Comperator._Data);
    }
};


#endif
