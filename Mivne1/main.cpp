//
//  main.cpp
//  Mivne1
//
//  Created by Aviad Rom on 4/19/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#include <iostream>
#include "AVLTree.h"
#include "AVLTests.h"
#include "DS.h"
using namespace std;


int main(int argc, const char * argv[])
{
    InsertRemoveBasic();
    LeftLeftInsertionBasic();
    LeftRightInsertionBasic();
    RightRightInsertionBasic();
    RightLeftInsertionBasic();
    InsertionCombo();
    InsertionCombo2();
    LeftLeftRemove();
    RLRRRemoveCombo();
    AddCourseTest();
    RemoveCourseTest();
    return 0;
}

