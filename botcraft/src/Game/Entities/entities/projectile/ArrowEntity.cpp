#include "botcraft/Game/Entities/entities/projectile/ArrowEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ArrowEntity::metadata_count> ArrowEntity::metadata_names{ {
        "id_effect_color",
    } };

    ArrowEntity::ArrowEntity()
    {
        // Initialize all metadata with default values
        SetIdEffectColor(-1);
    }

    ArrowEntity::~ArrowEntity()
    {

    }


    std::string ArrowEntity::GetName() const
    {
        return "Arrow";
    }

    EntityType ArrowEntity::GetType() const
    {
        return EntityType::Arrow;
    }

    double ArrowEntity::GetWidth() const
    {
        return 0.5;
    }

    double ArrowEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string ArrowEntity::GetClassName()
    {
        return "Arrow";
    }

    EntityType ArrowEntity::GetClassType()
    {
        return EntityType::Arrow;
    }


    ProtocolCraft::Json::Value ArrowEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractArrowEntity::Serialize();

        output["metadata"]["id_effect_color"] = GetIdEffectColor();

        return output;
    }


    void ArrowEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractArrowEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int ArrowEntity::GetIdEffectColor() const
    {
        return std::any_cast<int>(metadata.at("id_effect_color"));
    }


    void ArrowEntity::SetIdEffectColor(const int id_effect_color)
    {
        metadata["id_effect_color"] = id_effect_color;
    }

}
