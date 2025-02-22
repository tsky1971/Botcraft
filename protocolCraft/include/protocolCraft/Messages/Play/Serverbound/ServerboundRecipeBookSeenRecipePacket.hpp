#pragma once

#if PROTOCOL_VERSION > 736
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookSeenRecipePacket : public BaseMessage<ServerboundRecipeBookSeenRecipePacket>
    {
    public:
#if PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x22;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Recipe Book Seen Recipe";

        virtual ~ServerboundRecipeBookSeenRecipePacket() override
        {

        }

        void SetRecipe(const Identifier& recipe_)
        {
            recipe = recipe_;
        }


        const Identifier& GetRecipe() const
        {
            return recipe;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            recipe = ReadData<Identifier>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(recipe, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["recipe"] = recipe;

            return output;
        }

    private:
        Identifier recipe;
    };
} //ProtocolCraft
#endif
