#pragma once

#if PROTOCOL_VERSION > 351
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerLookAtPacket : public BaseMessage<ClientboundPlayerLookAtPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x37;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Face Player";

        virtual ~ClientboundPlayerLookAtPacket() override
        {

        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetEntity(const int entity_)
        {
            entity = entity_;
        }

        void SetFromAnchor(const int from_anchor_)
        {
            from_anchor = from_anchor_;
        }

        void SetToAnchor(const int to_anchor_)
        {
            to_anchor = to_anchor_;
        }

        void SetAtEntity(const bool at_entity_)
        {
            at_entity = at_entity_;
        }


        double GetX() const
        {
            return x;
        }

        double GetY() const
        {
            return y;
        }

        double GetZ() const
        {
            return z;
        }

        int GetEntity() const
        {
            return entity;
        }

        int GetFromAnchor() const
        {
            return from_anchor;
        }

        int GetToAnchor() const
        {
            return to_anchor;
        }

        bool GetAtEntity() const
        {
            return at_entity;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            from_anchor = ReadData<VarInt>(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            at_entity = ReadData<bool>(iter, length);
            if (at_entity)
            {
                entity = ReadData<VarInt>(iter, length);
                to_anchor = ReadData<VarInt>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(from_anchor, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<bool>(at_entity, container);
            if (at_entity)
            {
                WriteData<VarInt>(entity, container);
                WriteData<VarInt>(to_anchor, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["from_anchor"] = from_anchor;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["at_entity"] = at_entity;
            if (at_entity)
            {
                output["entity"] = entity;
                output["to_anchor"] = to_anchor;
            }

            return output;
        }

    private:
        double x;
        double y;
        double z;
        int entity;
        int from_anchor;
        int to_anchor;
        bool at_entity;

    };
} //ProtocolCraft
#endif
