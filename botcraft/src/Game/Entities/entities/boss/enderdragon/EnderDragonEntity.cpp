#include "botcraft/Game/Entities/entities/boss/enderdragon/EnderDragonEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, EnderDragonEntity::metadata_count> EnderDragonEntity::metadata_names{ {
        "data_phase",
    } };

    EnderDragonEntity::EnderDragonEntity()
    {
        // Initialize all metadata with default values
        SetDataPhase(10);
    }

    EnderDragonEntity::~EnderDragonEntity()
    {

    }


    std::string EnderDragonEntity::GetName() const
    {
        return "EnderDragon";
    }

    EntityType EnderDragonEntity::GetType() const
    {
        return EntityType::EnderDragon;
    }

    double EnderDragonEntity::GetWidth() const
    {
        return 16.0;
    }

    double EnderDragonEntity::GetHeight() const
    {
        return 8.0;
    }


    std::string EnderDragonEntity::GetClassName()
    {
        return "EnderDragon";
    }

    EntityType EnderDragonEntity::GetClassType()
    {
        return EntityType::EnderDragon;
    }


    ProtocolCraft::Json::Value EnderDragonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MobEntity::Serialize();

        output["metadata"]["data_phase"] = GetDataPhase();

        return output;
    }


    void EnderDragonEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int EnderDragonEntity::GetDataPhase() const
    {
        return std::any_cast<int>(metadata.at("data_phase"));
    }


    void EnderDragonEntity::SetDataPhase(const int data_phase)
    {
        metadata["data_phase"] = data_phase;
    }

}
