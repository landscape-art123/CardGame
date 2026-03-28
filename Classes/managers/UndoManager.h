#pragma once
#include "models/UndoModel.h"
using namespace std;
USING_NS_CC;

//作为 controller 的成员，负责维护回退记录栈。

class UndoManager
{
public:
    void init();
    void pushRecord(const UndoModel& record);
    bool canUndo() const;
    bool popRecord(UndoModel& outRecord);
    void clear();

private:
    vector<UndoModel> _records;
};