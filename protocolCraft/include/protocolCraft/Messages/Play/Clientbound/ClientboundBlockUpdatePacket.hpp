#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockUpdatePacket : public BaseMessage<ClientboundBlockUpdatePacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x09;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Block Update";

        virtual ~ClientboundBlockUpdatePacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetBlockstate(const int blockstate_)
        {
            blockstate = blockstate_;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        int GetBlockstate() const
        {
            return blockstate;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
            blockstate = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<NetworkPosition>(pos, container);
            WriteData<VarInt>(blockstate, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
            output["blockstate"] = blockstate;

            return output;
        }

    private:
        NetworkPosition pos;
        int blockstate;
    };
} //ProtocolCraft
