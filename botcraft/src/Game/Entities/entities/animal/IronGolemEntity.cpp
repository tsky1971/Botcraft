#include "botcraft/Game/Entities/entities/animal/IronGolemEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, IronGolemEntity::metadata_count> IronGolemEntity::metadata_names{ {
        "data_flags_id",
    } };

    IronGolemEntity::IronGolemEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);
    }

    IronGolemEntity::~IronGolemEntity()
    {

    }


    std::string IronGolemEntity::GetName() const
    {
        return "IronGolem";
    }

    EntityType IronGolemEntity::GetType() const
    {
        return EntityType::IronGolem;
    }

    double IronGolemEntity::GetWidth() const
    {
        return 1.4;
    }

    double IronGolemEntity::GetHeight() const
    {
        return 2.7;
    }


    std::string IronGolemEntity::GetClassName()
    {
        return "IronGolem";
    }

    EntityType IronGolemEntity::GetClassType()
    {
        return EntityType::IronGolem;
    }


    ProtocolCraft::Json::Value IronGolemEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractGolemEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    void IronGolemEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char IronGolemEntity::GetDataFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void IronGolemEntity::SetDataFlagsId(const char data_flags_id)
    {
        metadata["data_flags_id"] = data_flags_id;
    }

}
