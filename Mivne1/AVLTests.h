//
//  AVLTests.h
//  Mivne1
//
//  Created by Aviad Rom on 4/27/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_AVLTests_h
#define Mivne1_AVLTests_h
#include "AVLTree.h"
using namespace std;

// testing on int primitive
void InsertRemoveBasic(){
    AVLTree<int> tester;
    int nodes[]={6,4,8,3,5,7,9};
    for (int i = 0 ; i < 7 ; i++){
        tester.Insert(nodes+i);
        if (!tester.IsIn(nodes+i)){
            cout <<  "InsertRemoveBasic: Insertion failed. node " << nodes+i << "failed to insert"<< endl;
            return;
        }
    }
    for (int i = 6 ; i >= 0 ; i--){
        tester.Remove(nodes+i);
        if (tester.IsIn(nodes+i)){
            cout << "InsertRemoveBasic: Removal failed. node " << nodes+i << "still in tree" << endl;
            return;
        }
    }
    if (!tester.IsEmpty()){
        cout << "InsertRemoveBasic:Test Failed. did not remove all nodes from tree" << endl;
        return;
    }
        cout << "InsertRemoveBasic: Test Passed."<<endl;

}

void LeftLeftInsertionBasic(){
    AVLTree<int> tester;
    int nodes[]={12,8,15,6,10,14,24,4,11,13,20,29,19,18};
    for (int i = 0; i < 14; i++)
        tester.Insert(nodes+i);
    AVLNode<int>* actual = tester.Find(nodes);
    if (actual->_Balance == -1 && actual->_Height == 4){
        cout << "LeftLeftInsertionBasic: Test Passed." << endl;
    } else {
        cout << "LeftLeftInsertionBasic: Test failed. check right branch on debug" <<endl;
    }
}

void LeftRightInsertionBasic(){
    AVLTree<int> tester;
    int nodes[12]={15,10,20,6,13,17,24,4,7,12,14,11};
    for (int i = 0; i < 12; i++)
        tester.Insert(nodes+i);
    AVLNode<int>* actual = tester.Find(nodes);
    if (actual->_Parent){
        actual = actual->_Parent;
    }
    if  (actual->_Data == 13 && actual->_Height == 3 && actual->_Balance == 0){
        cout << "LeftRightInsertionBasic: Test passed." <<  endl;
    } else {
        cout << "LeftRightInsertionBasic:Test failed. actual root is:" << actual->_Data << endl;
        cout << "Root info: Height=" << actual->_Height << " Balance=" << actual->_Balance <<endl;
    }

}

void RightRightInsertionBasic(){
    AVLTree<int> tester;
    int nodes[]={3,2,6,1,5,7,4,8,9};
    for (int i = 0; i < 9; i++){
        tester.Insert(nodes+i);
    }
    AVLNode<int>* actual = tester.Find(nodes);
    if (actual->_Height != 3){
        cout << "RightRightInsertion: Test failed. Debug right branch (did not perform roll correctly)" <<endl;
    }else {
        cout << "RightRightInsertion: Test Passed." << endl;
    }
}

void RightLeftInsertionBasic(){
    AVLTree<int> tester;
    int nodes[]={11,8,19,6,10,13,25,12,17,23,29,15};
    for (int i = 0; i< 12; i++){
        tester.Insert(nodes+i);
    }
    AVLNode<int>* actual = tester.Find(nodes+5);
    if (actual->_Parent){
        cout << "RightLeftInsertionBasic: Test failed. roll did not perform correctly" << endl;
    }
    else cout << "RightLeftInsertionBasic: Test Passed."<<endl;
}

void InsertionCombo(){
    AVLTree<int> tester;
    int nodes[]={50,20,80,70,90,75};
    for (int i = 0; i < 6; i++) tester.Insert(nodes+i);
    AVLNode<int>* actual = tester.Find(nodes+3);
    if (actual->_Parent){
        cout << "InsertionCombo: Test Failed. wrong root" << endl;
    } else cout << "InsertionCombo: Test Passed." << endl;
}

void InsertionCombo2(){
    AVLTree<int> tester;
    int nodes[]={50,20,90,10,40,70,100,5,15,30,45,35};
    for (int i = 0; i < 12; i++) tester.Insert(nodes+i);
    AVLNode<int>* actual = tester.Find(nodes+4);
    if (actual->_Parent) cout << "InsertionCombo2: Test Failed. wrong root." << endl;
    else cout << "InsertionCombo2: Test Passed." << endl;

}

void LeftLeftRemove(){
    AVLTree<int> tester;
    int nodes[]={12,8,15,6,10,14,24,4,11,13,20,29,19,18};
    for (int i = 0; i < 14 ; i++) tester.Insert(nodes+i);
    tester.Remove(nodes+11);
    if (tester.IsIn(nodes+11)) {
        cout << "LeftLeftRemove: Test Failed. node was not removed" << endl;
        return;
    }
    AVLNode<int>* actual = tester.Find(nodes+6);
    if  (actual->_Parent->_Data == 19 && actual->_Left->_Data == 20){
        cout << "LeftLeftRemove: Test Passed." << endl;
    } else cout << "LeftLeftRemove: Test Failed. did not update all node data" << endl;
    
}

void RLRRRemoveCombo(){
    AVLTree<int> tester;
    int nodes[]={5,2,8,1,4,6,10,3,7,9,12,11};
    for (int i = 0; i < 12; i++) tester.Insert(nodes+i);
    tester.Remove(nodes+3);
    if (tester.IsIn(nodes+3)){
        cout << "RLRRRemoveCombo: Test failed. node was not removed." << endl;
    }
    AVLNode<int>* actual = tester.Find(nodes+2);
    if (actual->_Parent){
        cout <<"RLRRRemoveCombo: Test failed. wrong root." <<endl;
        }else cout << "RLRRRemoveCombo: Test Passed." << endl;
}

//testing code is generic with strings
        


#endif
