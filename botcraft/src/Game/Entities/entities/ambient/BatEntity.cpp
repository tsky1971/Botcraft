#include "botcraft/Game/Entities/entities/ambient/BatEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, BatEntity::metadata_count> BatEntity::metadata_names{ {
        "data_id_flags",
    } };

    BatEntity::BatEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFlags(0);
    }

    BatEntity::~BatEntity()
    {

    }


    std::string BatEntity::GetName() const
    {
        return "Bat";
    }

    EntityType BatEntity::GetType() const
    {
        return EntityType::Bat;
    }

    double BatEntity::GetWidth() const
    {
        return 0.5;
    }

    double BatEntity::GetHeight() const
    {
        return 0.9;
    }


    std::string BatEntity::GetClassName()
    {
        return "Bat";
    }

    EntityType BatEntity::GetClassType()
    {
        return EntityType::Bat;
    }


    ProtocolCraft::Json::Value BatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AmbientCreatureEntity::Serialize();

        output["metadata"]["data_id_flags"] = GetDataIdFlags();

        return output;
    }


    void BatEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AmbientCreatureEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char BatEntity::GetDataIdFlags() const
    {
        return std::any_cast<char>(metadata.at("data_id_flags"));
    }


    void BatEntity::SetDataIdFlags(const char data_id_flags)
    {
        metadata["data_id_flags"] = data_id_flags;
    }

}
