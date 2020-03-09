#pragma once

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/InterfaceClient.hpp>

class ChatCommandClient : public Botcraft::InterfaceClient
{
public:
    ChatCommandClient(const std::vector<int> &printed_packets_ = std::vector<int>(0));
    ~ChatCommandClient();

protected:
    virtual void Handle(ProtocolCraft::ChatMessageClientbound &msg) override;

    // Check for any spawnable blocks in a sphere from pos and prints
    // all the positions into a file
    // Use check_lighting to add a check on light block value (> 7)
    // (warning: ignore top slabs and upside-down stairs,
    // you should check for such blocks manually)
    void CheckPerimeter(const Botcraft::Position &pos, const float radius, const bool check_lighting);
};