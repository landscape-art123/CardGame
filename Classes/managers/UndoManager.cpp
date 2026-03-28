#include "managers/UndoManager.h"


void UndoManager::init() 
{
    _records.clear();
}

void UndoManager::pushRecord(const UndoModel& record)
{
    _records.push_back(record);
}

bool UndoManager::canUndo() const
{
    return !_records.empty();
}

bool UndoManager::popRecord(UndoModel& outRecord)
{
    if (_records.empty())
    {
        return false;
    }

    outRecord = _records.back();
    _records.pop_back();
    return true;
}

void UndoManager::clear()
{
    _records.clear();
}