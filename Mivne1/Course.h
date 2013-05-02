//
//  Course.h
//  Mivne1
//
//  Created by Aviad Rom on 4/21/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_Course_h
#define Mivne1_Course_h
#include "AVLTree.h"
#include "Student.h"
#include "LList.h"

class PendingStudent {
    int _StudentID;
    int _PendTiming;
public:
    PendingStudent(int ID,int Timing):_StudentID(ID),_PendTiming(Timing){}
    const int GetId() const{
        return _StudentID;
    }
    
    const int GetPend() const{
        return _PendTiming;
    }
};

class Course{
    int _ID;
    int _Size;
    int _AvailableSeats;
    int _NumOfPending;
    AVLTree<int> _EnrolledStudents; //switched to int-doesn't need any extra info in here.
    LListNode<int>* _PendingHead; //where we pull students from
    LListNode<int>* _PendingTail; //where we push students to
    
    void AddToPend (int studentID){ //only use this to
        LListNode<int>* node = new LListNode<int>(studentID);
        if (_PendingTail == NULL && _PendingHead == NULL){
            _PendingHead = node;
            _PendingTail = node;
        }else {
            _PendingTail->Previous = node;
            node->Next = _PendingTail;
            _PendingTail = node;
        }
    }
public:
    Course(): _ID(-1), _Size(0){}
    Course(int Id,int Size):_ID(Id),_Size(Size),_AvailableSeats(Size),_NumOfPending(0), _PendingHead(NULL),
                            _PendingTail(NULL){}
    ~Course(){}
    
    int GetID(){
        return _ID;
    }
    
    int GetSize(){
        return _Size;
    }
    
    void IncreaseSize(int Addition){
        _Size += Addition;
        if (_NumOfPending == 0){
            return;
        }
        for (int i=0; i<_NumOfPending; i++){
            //TODO-write function PendingToEnrolled to move students from
            // pending list to enrolled list and also update the students accordingly
        }
        
        //TODO- continue working on this.
        //if there are pending students they need to move from pending to enrolled
        // according to the new course size
    }

    const bool Enroll(int* StudentID){
        if (StudentID){
  //          Student student(*StudentID);
            if (_AvailableSeats){
                _EnrolledStudents.Insert(StudentID);
                _AvailableSeats--;
                return true;
            }
            AddToPend(*StudentID);
        }
        return false;
    }
    
    const bool Leave(int* StudentID){ //Removal from pending list is done via DS, by the student object.
        if (!StudentID){
            return false;
        }
        if (_EnrolledStudents.IsIn(StudentID)){
            _EnrolledStudents.Remove(StudentID);
            if (_PendingTail){
                _EnrolledStudents.Insert(&(_PendingTail->Data));
            } else {
                _AvailableSeats++;
            }

        }
        return true;
    }
    
    //used to check if student is either on course enrolled tree or pending tree.
    const bool IsEnrolled(int* StudentID) {
        Student student(*StudentID);
        if (_EnrolledStudents.IsIn(StudentID)){ // || _PendingStudents.IsIn(&student)){
            return true;
        }
            return false;
    } // Maybe not relevant anymore
    
    const bool operator<(Course& Comperator) const{
        return (_ID < Comperator.GetID());
    }
    
    const bool operator>(Course& Comperator) const{
        return (_ID > Comperator.GetID());
    }
    
    const bool operator==(Course& Comperator) const{
        return (_ID == Comperator.GetID());
    }

    LListNode<int>* GetQueueTail(){
        return _PendingTail;
    }
    
};

#endif
