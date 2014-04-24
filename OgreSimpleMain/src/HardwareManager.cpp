#include "HardwareManager.h"

namespace OgreSimple
{
    HardwareManager* HardwareManager::mSingleton = 0;

    HardwareManager::HardwareManager()
    {
        mSingleton = this;
    }

    HardwareManager::~HardwareManager()
    {
        mSingleton = 0;
    }

    HardwareManager* HardwareManager::getSingleton()
    {
        return mSingleton;
    }
}
