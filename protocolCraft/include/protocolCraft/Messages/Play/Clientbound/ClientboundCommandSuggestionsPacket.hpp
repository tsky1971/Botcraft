#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 356
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundCommandSuggestionsPacket : public BaseMessage<ClientboundCommandSuggestionsPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x0D;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Command Suggestions";

        virtual ~ClientboundCommandSuggestionsPacket() override
        {

        }

#if PROTOCOL_VERSION > 356
        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetStart(const int start_)
        {
            start = start_;
        }

        void SetLength(const int length__)
        {
            length_ = length__;
        }
#endif

        void SetSuggestions(const std::vector<std::string>& suggestions_)
        {
            suggestions = suggestions_;
        }

#if PROTOCOL_VERSION > 356
        void SetTooltips(const std::vector<std::optional<Chat>>& tooltips_)
        {
            tooltips = tooltips_;
        }
#endif

#if PROTOCOL_VERSION > 356
        int GetId_() const
        {
            return id_;
        }

        int GetStart() const
        {
            return start;
        }

        int GetLength() const
        {
            return length_;
        }
#endif

        const std::vector<std::string>& GetSuggestions() const
        {
            return suggestions;
        }

#if PROTOCOL_VERSION > 356
        const std::vector<std::optional<Chat>>& GetTooltips() const
        {
            return tooltips;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 356
            id_ = ReadData<VarInt>(iter, length);
            start = ReadData<VarInt>(iter, length);
            length_ = ReadData<VarInt>(iter, length);
#endif
            const int count = ReadData<VarInt>(iter, length);
            suggestions = std::vector<std::string>(count);
#if PROTOCOL_VERSION > 356
            tooltips = std::vector<std::optional<Chat>>(count);
#endif
            for (int i = 0; i < count; ++i)
            {
                suggestions[i] = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 356
                tooltips[i] = ReadOptional<Chat>(iter, length);
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

#if PROTOCOL_VERSION > 356
            WriteData<VarInt>(id_, container);
            WriteData<VarInt>(start, container);
            WriteData<VarInt>(length_, container);
#endif
            WriteData<VarInt>(static_cast<int>(suggestions.size()), container);
            for (int i = 0; i < suggestions.size(); ++i)
            {
                WriteData<std::string>(suggestions[i], container);
#if PROTOCOL_VERSION > 356
                WriteOptional<Chat>(tooltips[i], container);
#endif
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;



#if PROTOCOL_VERSION > 356
            output["id_"] = id_;
            output["start"] = start;
            output["length_"] = length_;
#endif
            output["suggestions"] = suggestions;

#if PROTOCOL_VERSION > 356
            output["tooltips"] = Json::Array();
            for (const auto& t : tooltips)
            {
                output["tooltips"].push_back(t.has_value() ? t.value().Serialize() : Json::Value());
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 356
        int id_;
        int start;
        int length_;
#endif
        std::vector<std::string> suggestions;
#if PROTOCOL_VERSION > 356
        std::vector<std::optional<Chat>> tooltips;
#endif

    };
} //ProtocolCraft
