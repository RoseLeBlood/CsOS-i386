#include <cxx/list.hpp>

namespace std
{
    namespace internal
    {
        void list_base_node::link_before(list_base_node* nextNode)
        {
            assert(!in_list());
            prev = nextNode->prev;
            prev->next = this;
            nextNode->prev = this;
            next = nextNode;
        }
        void list_base_node::unlink()
        {
            assert(in_list());
            prev->next = next;
            next->prev = prev;
            next = prev = this;
        }
    } 
}
