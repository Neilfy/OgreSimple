#ifndef MATERIALMANAGER_H
#define  MATERIALMANAGER_H
#include <string>
#include <map>

namespace OgreSimple
{
    class Material;
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager();
        static MaterialManager* getSingleton();

        Material* create(const std::string& name);
        Material* GetByName(const std::string& name);
    private:
        static MaterialManager* mSingleton;
        std::map<std::string, Material*>	mMaterials;
    };
}
#endif //MATERIALMANAGER_H
