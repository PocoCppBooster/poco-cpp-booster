#pragma once
/**
 * @file the utilities of Poco::DynamicStruct. 
 */
#include <Poco/DynamicStruct.h>
#include <ios>
#include <iterator>
#include <stack>

namespace Poco {
namespace booster {

/**
 * @brief the class providing foward itarator accessing all primitive elements in Poco::DynamicStruct: strings, integer, numerics, boolean.
 */
class IterableDynamicStruct {
  public:
    using value_type = Poco::Dynamic::Var;
    using reference = Poco::Dynamic::Var&;
    using const_reference = const Poco::Dynamic::Var&;
    using pointer = Poco::Dynamic::Var*;
    using const_pointer = const Poco::Dynamic::Var*;
    using difference_type = std::streamsize;
    using size_type = std::size_t;

    template <typename RefType>
    struct ConstFowardIteratorWrapper {
      public:
        virtual void forward() = 0;
        virtual RefType value() = 0;
    };

    
    class ConstIterator : public std::forward_iterator_tag {
      public:
        using difference_type = std::streamsize;
        using value_type = Poco::Dynamic::Var;
        using pointer = const value_type*;
        using reference = const value_type&;

        /**
         * @brief constructor that indicates the elements of sub-struct/list/deque.
         * parent_iter indicates 
         */
        explicit ConstIterator(pointer var)
            : curr_var_(var)
        {
        }

        virtual ConstIterator& operator++() = 0;

        virtual ConstIterator& operator++(int) = 0;

        virtual reference operator*() = 0;

      private:
        pointer curr_var_;
    };

    IterableDynamicStruct(const Poco::DynamicStruct& dynst)
    {
    }
};
} // the end of booster namespace.
} // the end of Poco namespace.