//
//  LList.h
//  Mivne1
//
//  Created by Aviad Rom on 4/29/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_LList_h
#define Mivne1_LList_h
#include <iostream>

template <typename T>
class LListNode {
public:
    LListNode(T data, LListNode<T>* next = NULL, LListNode<T>* previous = NULL):Data(data),
                        Next(next), Previous(previous){}
    T Data;
    LListNode<T>* Next;
    LListNode<T>* Previous;
};

#endif
