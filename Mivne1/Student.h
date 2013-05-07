//
//  Student.h
//  Mivne1
//
//  Created by Aviad Rom on 4/22/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_Student_h
#define Mivne1_Student_h
#include "AVLTree.h"
#include "LList.h"
#include "PendCourse.h"

class Student {
    int _ID;
    AVLTree<int> _CoursesTaken;
    AVLTree<PendCourse> _CoursesPending;
    int _NumberOfCoursesTaken;
public:
    Student():_ID(-1),_NumberOfCoursesTaken(0){}
    
    Student(int ID):_ID(ID),_NumberOfCoursesTaken(0){}
    
    ~Student(){}
    
    /* GetEnrolledStudents
    * Description: Returns a pointer to the root node of the courses pending tree
    *              of the student.
    */
    AVLNode<PendCourse>* GetCoursesPending(){
        return _CoursesPending.GetRoot();
    }

    /*GetID
     * Description: Getter to _ID property of the student
     */
    int GetID(){
        return _ID;
    }
    
    /* AddCourseTaken
     * Description: Adds a course ID to the _CoursesTaken tree.
     * @param CourseID: pointer to course's ID element.
     * @return: true if added successfully.
     *          false if invalid pointer was provided.
     */
    const bool AddCourseTaken(int* CourseID){
        if (CourseID){
            PendCourse pend(*CourseID,NULL);
            _CoursesTaken.Insert(CourseID);
            if (_CoursesPending.IsIn(&pend)){
                _CoursesPending.Remove(&pend);
            }
            _NumberOfCoursesTaken++;
            return true;
        }
        return false;
    }
    
    /*AddCoursePending
     * Description: Adds a course to the student's pending courses tree.
     * @param CourseID: Pointer to the ID of the course
     * @param QueueLocation: Pointer to the location in the course's pending list.
     * @return: true if successfully added.
     *          false if either one of the pointers is invalid (NULL)
     */
    const bool AddCoursePending (int* CourseID, LListNode<int>* QueueLocation){
        if (CourseID && QueueLocation){
            PendCourse pend(*CourseID,QueueLocation);
            if (!_CoursesTaken.IsIn(CourseID)){
                _CoursesPending.Insert(&pend);
                return true;
            }
        }
        return false;
    }
    
    /*RemoveCourse
     * Description: Removes a course from the student's lists of courses
     * @param CourseID: pointer to the course's ID element.
     * @return: true if successfully removed course from student's lists.
     *          false if pointer was invalid.
     */
    const bool RemoveCourse(int* CourseID){
        if (CourseID){
            if (_CoursesTaken.IsIn(CourseID)){
                _CoursesTaken.Remove(CourseID);
                _NumberOfCoursesTaken--;
            }
            PendCourse pendRemoval(*CourseID,NULL);
            _CoursesPending.Remove(&pendRemoval);
            return true;
        }
        return false;
    }
    
    
    const bool operator< (Student& Comperator) const{
        return (_ID < Comperator.GetID());
    }
    
    const bool operator> (Student& Comperator) const{
        return (_ID > Comperator.GetID());
    }
    
    const bool operator== (Student& Comperator) const{
        return (_ID == Comperator.GetID());
    }
    
    const int GetNumberOfCoursesTaken() const{
        return _NumberOfCoursesTaken;
    }
    
    /*IsCourseTaken
     * Description: Returns a bool true/false according to wether a student is
     *              on a course's enrolled list or not.
     * @param CourseID: ID of the course to be checked.
     */
    const bool IsCourseTaken(int courseId){
        return _CoursesTaken.IsIn(&courseId);
    }
    
    /*IsCoursePending
     * Description: Returns a bool true/false according to wether a student is
     *              on a course's pending list or not.
     * @param CourseID: ID of the course to check.
     */
    const bool IsCoursePending(int courseID){
        PendCourse course(courseID);
    	return _CoursesPending.IsIn(&course);
    }
};

#endif
