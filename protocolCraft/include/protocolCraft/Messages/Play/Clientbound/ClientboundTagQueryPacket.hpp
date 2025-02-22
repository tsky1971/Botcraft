#pragma once

#if PROTOCOL_VERSION > 388
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundTagQueryPacket : public BaseMessage<ClientboundTagQueryPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x64;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x62;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Tag Query";

        virtual ~ClientboundTagQueryPacket() override
        {

        }

        void SetTransactionId(const int transaction_id_)
        {
            transaction_id = transaction_id_;
        }

        void SetTag(const NBT::Value& tag_)
        {
            tag = tag_;
        }


        int GetTransactionId() const
        {
            return transaction_id;
        }

        const NBT::Value& GetTag() const
        {
            return tag;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            transaction_id = ReadData<VarInt>(iter, length);
            tag = ReadData<NBT::Value>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(transaction_id, container);
            WriteData<NBT::Value>(tag, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["transaction_id"] = transaction_id;
            output["tag"] = tag;

            return output;
        }

    private:
        int transaction_id;
        NBT::Value tag;

    };
} //ProtocolCraft
#endif
