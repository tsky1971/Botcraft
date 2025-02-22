#include "botcraft/Game/Entities/entities/monster/WitchEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, WitchEntity::metadata_count> WitchEntity::metadata_names{ {
        "data_using_item",
    } };

    WitchEntity::WitchEntity()
    {
        // Initialize all metadata with default values
        SetDataUsingItem(false);
    }

    WitchEntity::~WitchEntity()
    {

    }


    std::string WitchEntity::GetName() const
    {
        return "Witch";
    }

    EntityType WitchEntity::GetType() const
    {
        return EntityType::Witch;
    }

    double WitchEntity::GetWidth() const
    {
        return 0.6;
    }

    double WitchEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string WitchEntity::GetClassName()
    {
        return "Witch";
    }

    EntityType WitchEntity::GetClassType()
    {
        return EntityType::Witch;
    }


    ProtocolCraft::Json::Value WitchEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 404
        ProtocolCraft::Json::Value output = RaiderEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = MobEntity::Serialize();
#endif

        output["metadata"]["data_using_item"] = GetDataUsingItem();

        return output;
    }


    void WitchEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 404
            RaiderEntity::SetMetadataValue(index, value);
#else
            MobEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool WitchEntity::GetDataUsingItem() const
    {
        return std::any_cast<bool>(metadata.at("data_using_item"));
    }


    void WitchEntity::SetDataUsingItem(const bool data_using_item)
    {
        metadata["data_using_item"] = data_using_item;
    }

}
