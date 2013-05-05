//
//  PendCourse.h
//  Mivne1
//
//  Created by Aviad Rom on 4/30/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_PendCourse_h
#define Mivne1_PendCourse_h

class PendCourse {
    int _CourseID;
    LListNode<int>* _QueueNode;
public:
    PendCourse(int courseID=0,LListNode<int>* node=NULL):_CourseID(courseID),_QueueNode(node){}
    
    const bool operator<(PendCourse& comperator){
        return (_CourseID < comperator._CourseID);
    }
    
    const bool operator>(PendCourse& comperator){
        return (_CourseID > comperator._CourseID);
    }
    
    const bool operator==(PendCourse& comperator){
        return (_CourseID == comperator._CourseID);
    }
    
    const int GetID(){
        return _CourseID;
    }
    
    void Remove(){
        if (_QueueNode->Previous && _QueueNode->Next)
        _QueueNode->Previous->Next = _QueueNode->Next;
        _QueueNode->Next->Previous = _QueueNode->Previous;
        delete _QueueNode;
    }
};



#endif
