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
    
    void RestoreLastState(int& numOfNewlyEnrolled, LListNode<int>* tmpHead, bool needToUpdateCurrent,
                                AVLTree<Student>* StudentsTree){
        if (!needToUpdateCurrent){
            tmpHead = tmpHead->Previous;
        }
        for (; numOfNewlyEnrolled > 0; numOfNewlyEnrolled--){
            Student studentRestore(tmpHead->Data);
            AVLNode<Student>* restoreNode = StudentsTree->Find(&studentRestore);
            restoreNode->_Data.removeCourse(&_ID);
            restoreNode->_Data.AddCoursePending(&_ID, tmpHead);
            tmpHead = tmpHead->Previous;
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
    
    void IncreaseSize(int Addition, AVLTree<Student>* StudentsTree){
        _Size += Addition;
        _AvailableSeats += Addition;
        if (_NumOfPending == 0){
            return;
        }
        int numOfNewlyEnrolled = 0;
        LListNode<int>* tmpHead = _PendingHead;
        for (int i=0; i<_NumOfPending && _AvailableSeats>0 ; i++, numOfNewlyEnrolled++){
            Student student(tmpHead->Data);
            AVLNode<Student>* studentNode = StudentsTree->Find(&student);
            try{
                studentNode->_Data.AddCourseTaken(&tmpHead->Data);
            } catch (bad_alloc& BadAlloc){
                if (numOfNewlyEnrolled){
                    RestoreLastState(numOfNewlyEnrolled, tmpHead, false, StudentsTree);
                    throw bad_alloc();
                }
            }
            try {
                Enroll(&_PendingHead->Data);
            } catch (bad_alloc& BadAlloc){
                RestoreLastState(numOfNewlyEnrolled, tmpHead, true, StudentsTree);
                throw bad_alloc();
            }
            tmpHead = tmpHead->Next;
        }
        while (_PendingHead->Data != tmpHead->Data) {
            _PendingHead = _PendingHead->Next;
            delete _PendingHead->Previous;
            _PendingHead->Previous = NULL;
        }
    }

    const bool Enroll(int* StudentID){
        if (StudentID){
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
    AVLNode<int>* GetEnrolledStudents(){
        return _EnrolledStudents.GetRoot();
    }
    
};

#endif
