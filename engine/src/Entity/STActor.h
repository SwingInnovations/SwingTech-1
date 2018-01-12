#ifndef WAHOO_STACTOR_H
#define WAHOO_STACTOR_H

#include "STEntity.h"

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

/**
 * @brief 3D Object. Use STSpriteActor for 2D Character
 */
class STActor : public STEntity {
public:
    STActor() = default;
    STActor(const std::string& filePath);
    STActor(STMesh_Structure structure, std::string& tag, STMaterial* material);
    STActor(STMesh_Structure, std::map<std::string, std::shared_ptr<STMaterial>>);
    STActor(STEntity* parent, STMesh_Structure, std::map<std::string, STMaterial*>);
    ~STActor();

    void AddChildActor(std::shared_ptr<STActor> actor);
    static std::shared_ptr<STActor> Create(const std::string& filename);

    template<typename Archive> inline void serialize(Archive& ar){
        ar(cereal::virtual_base_class<STEntity>(this));
    }

    void draw() override;
    void draw(STMaterial*);
    void draw(Camera*, int) override;
    void draw(STMaterial *overrideMaterial, bool flag);
};
#endif //WAHOO_STACTOR_H
