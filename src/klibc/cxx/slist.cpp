#include <cxx/slist.hpp>

namespace std
{
    namespace internal
    {
        void slist_base_node::link_after(slist_base_node* prevNode)
        {
                assert(!in_list());
                next = prevNode->next;
                prevNode->next = this;
        }
        void slist_base_node::unlink(slist_base_node* prevNode)
        {
            assert(in_list());
            assert(prevNode->next == this);
            prevNode->next = next;
            next = this;
        }
    }
}
