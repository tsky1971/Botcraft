#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataNone : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataNone() override
        {

        }


#if PROTOCOL_VERSION > 760
        void SetCookingBookCategory(const int cooking_book_category_)
        {
            cooking_book_category = cooking_book_category_;
        }
#endif


#if PROTOCOL_VERSION > 760
        int GetCookingBookCategory() const
        {
            return cooking_book_category;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 760
            cooking_book_category = ReadData<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 760
            WriteData<VarInt>(cooking_book_category, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION > 760
            output["cooking_book_category"] = cooking_book_category;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 760
        int cooking_book_category;
#endif
    };
}
#endif
