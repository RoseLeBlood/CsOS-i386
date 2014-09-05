#ifndef STD_SLIST_H
#define STD_SLIST_H

#include <cxx/allocator.hpp>
#include <cxx/iterator.hpp>

namespace std
{
	namespace internal
	{
	    struct slist_base_node
	    {
            slist_base_node()
            {
            	reset();
            }
            void reset()
            {
           		next = this;
            }
            bool in_list() const 
            { 
            	return this != next; 
            }

            void link_after(slist_base_node* prevNode);
            void unlink(slist_base_node* prevNode);

            slist_base_node*        next;
	    };
	}

	template<typename T, class TAllocator = std::allocator> class slist
	{
    private:
        struct node : public internal::slist_base_node
        {
            node(): internal::slist_base_node() 
            {
            
            }
            explicit node(const T& v)
            	: internal::slist_base_node(), value(v) 
           	{
           	
           	}
            T 	value;
        };
        static inline node* upcast(internal::slist_base_node* n)
        {
        	return (node*)n;
        }
        template<typename TNodePtr, typename TPtr, typename TRef> class node_iterator
        {
        public:
            typedef forward_iterator_tag    iterator_category;

            explicit node_iterator(TNodePtr node)
            	: m_node(node) 
            {
            }
            template<typename UNodePtr, typename UPtr, typename URef>
            node_iterator(const node_iterator<UNodePtr, UPtr, URef>& rhs)
            	: m_node(rhs.node())
            {
            }

            TRef operator*() const
            {
                assert(m_node != 0);
                return m_node->value;
            }
            TPtr operator->() const
            {
                return &m_node->value;
            }
            TNodePtr node() const
            {
                return m_node;
            }
            TNodePtr next() const
            {
                return upcast(m_node->next);
            }
            
            node_iterator& operator++()
            {
                m_node = upcast(m_node->next);
                return *this;
            }
            node_iterator operator++(int)
            {
                node_iterator copy(*this);
                ++(*this);
                return copy;
            }

            bool operator==(const node_iterator& rhs) const
            {
                return rhs.m_node == m_node;
            }
            bool operator!=(const node_iterator& rhs) const
            {
                return !(rhs == *this);
            }
        private:
          	TNodePtr        m_node;
        };

	public:
        typedef T                                                                                                       value_type;
        typedef TAllocator                                         		allocator_type;
        typedef int                                                     size_type;
        typedef node_iterator<node*, T*, T&>                         	iterator;
        typedef node_iterator<const node*, const T*, const T&>          const_iterator;
        static const size_t                                  			kNodeSize = sizeof(node);

        explicit slist(const allocator_type& allocator = allocator_type())
        	: m_allocator(allocator)
        {
        	m_root.reset();
        }
        template<class InputIterator> slist(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type())
        	: m_allocator(allocator)
        {
            m_root.reset();
            assign(first, last);
        }
        slist(const slist& rhs, const allocator_type& allocator = allocator_type())
        	: m_allocator(allocator)
        {
            m_root.reset();
            assign(rhs.begin(), rhs.end());
        }
        ~slist()
        {
            clear();
        }

        slist& operator=(const slist& rhs)
        {
            if (this != &rhs)
            {
             	assign(rhs.begin(), rhs.end());
            }
            return *this;
        }

        iterator begin()                               
        { 
        	return iterator(upcast(m_root.next)); 
        }
        const_iterator begin() const    
        { 
        	return const_iterator(upcast(m_root.next)); 
        }
        iterator end()                                  
        { 
        	return iterator(&m_root); 
        }
        const_iterator end() const              
        { 
        	return const_iterator(&m_root); 
        }

        const T& front() const  
        { 
        	assert(!empty()); 
        	return upcast(m_root.next)->value; 
        }
        T& front()                              
        { 
        	assert(!empty()); 
        	return upcast(m_root.next)->value; 
        }

        void push_front(const T& value)
        {
            node* newNode = construct_node(value);
            newNode->link_after(&m_root);
        }
        void pop_front()
        {
            assert(!empty());
            node* n = upcast(m_root.next);
            n->unlink(&m_root);
            destruct_node(n);
        }
        void insert_after(iterator pos, const T& value)
        {
            node* newNode = construct_node(value);
            newNode->link_after(pos.node());
        }

        template<class InputIterator> void assign(InputIterator first, InputIterator last) 
        {
            clear();
            iterator it(&m_root);
            while (first != last)
            {
                insert_after(it, *first);
                ++it;
                ++first;
            }
        }

        void clear()
        {
            node* it = upcast(m_root.next);
            while (it != &m_root)
            {
                node* nextIt = upcast(it->next);
                destruct_node(it);
                it = nextIt;
            }
            m_root.reset();
        }       
        bool empty() const      
        { 
        	return !m_root.in_list(); 
        }

        size_type size() const
        {
            const node* it = upcast(m_root.next);
            size_type size(0);
            while (it != &m_root)
            {
                ++size;
                it = upcast(it->next);
            }
            return size;
        }


        static iterator previous(iterator nextIt)
        {
            assert(nextIt.node()->in_list());
            iterator prevIt = nextIt;
            while (nextIt.node() != prevIt.next())
              	++prevIt;
            return prevIt;
        }
        static const_iterator previous(const_iterator nextIt)
        {
            assert(nextIt.node()->in_list());
            const_iterator prevIt = nextIt;
            while (nextIt.node() != prevIt.next())
              	++prevIt;
            return prevIt;
        }
	private:
        node* construct_node(const T& value)
        {
            void* mem = m_allocator.allocate(sizeof(node));
            return new (mem) node(value);
        }
        void destruct_node(node* n)
        {
            n->~node();
            m_allocator.deallocate(n, sizeof(node));
        }

        allocator_type  m_allocator;
        node           	m_root;
	};
} 

#endif 
