#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundTabListPacket : public BaseMessage<ClientboundTabListPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x61;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Tab List";

        virtual ~ClientboundTabListPacket() override
        {

        }

        void SetHeader(const Chat& header_)
        {
            header = header_;
        }

        void SetFooter(const Chat& footer_)
        {
            footer = footer_;
        }


        const Chat& GetHeader() const
        {
            return header;
        }

        const Chat& GetFooter() const
        {
            return footer;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            header = ReadData<Chat>(iter, length);
            footer = ReadData<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Chat>(header, container);
            WriteData<Chat>(footer, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["header"] = header;
            output["footer"] = footer;

            return output;
        }

    private:
        Chat header;
        Chat footer;

    };
} //ProtocolCraft
