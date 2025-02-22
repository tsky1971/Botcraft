#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockEntityDataPacket : public BaseMessage<ClientboundBlockEntityDataPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Block Entity Data";

        virtual ~ClientboundBlockEntityDataPacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

#if PROTOCOL_VERSION < 757
        void SetType(const unsigned char type_)
        {
            type = type_;
        }
#else
        void SetType(const int type_)
        {
            type = type_;
        }
#endif

        void SetTag(const NBT::Value& tag_)
        {
            tag = tag_;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

#if PROTOCOL_VERSION < 757
        unsigned char GetType() const
        {
            return type;
        }
#else
        int GetType() const
        {
            return type;
        }
#endif

        const NBT::Value& GetTag() const
        {
            return tag;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
#if PROTOCOL_VERSION < 757
            type = ReadData<unsigned char>(iter, length);
#else
            type = ReadData<VarInt>(iter, length);
#endif
            tag = ReadData<NBT::Value>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<NetworkPosition>(pos, container);
#if PROTOCOL_VERSION < 757
            WriteData<unsigned char>(type, container);
#else
            WriteData<VarInt>(type, container);
#endif
            WriteData<NBT::Value>(tag, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
            output["type"] = type;
            output["tag"] = tag;

            return output;
        }

    private:
        NetworkPosition pos;
#if PROTOCOL_VERSION < 757
        unsigned char type;
#else
        int type;
#endif
        NBT::Value tag;
    };
} //ProtocolCraft
