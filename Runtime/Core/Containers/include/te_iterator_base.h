#ifndef TE_ITERATOR_BASE_H
#define TE_ITERATOR_BASE_H
#define __VALUE_TYPE(__i) TE::value_type(__i)
#define __ITERATOR_CATEGORY(_i) TE::iterator_category(_i)
#define __DISTANCE_TYPE(__i) TE::distance_type(__i)
namespace TE
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag :public input_iterator_tag {};
    struct bidirectional_iterator_tag :public forward_iterator_tag {};
    struct random_access_iterator_tag :public bidirectional_iterator_tag {};

    template<typename _Tp, typename _Distance>
    struct input_iterator
    {
        typedef input_iterator_tag iterator_category;
        typedef _Tp value_type;
        typedef _Distance difference_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
    };

    struct output_iterator {
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
    };

    template<typename _Tp,typename _Distance>
    struct forward_iterator
    {
        typedef forward_iterator_tag iterator_category;
        typedef _Tp value_type;
        typedef _Distance difference_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
    };

    template <class _Tp, class _Distance> struct bidirectional_iterator {
        typedef bidirectional_iterator_tag iterator_category;
        typedef _Tp                        value_type;
        typedef _Distance                  difference_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
    };

    template <class _Tp, class _Distance> struct random_access_iterator {
        typedef random_access_iterator_tag iterator_category;
        typedef _Tp                        value_type;
        typedef _Distance                  difference_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
    };


    template <typename  _Category, typename  _Tp, typename  _Distance = ptrdiff_t,
        typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator {
        typedef _Category  iterator_category;
        typedef _Tp        value_type;
        typedef _Distance  difference_type;
        typedef _Pointer   pointer;
        typedef _Reference reference;
    };

    template<class _Tp>
    inline _Tp*value_type(const _Tp*){return (_Tp*)(0);}

    inline output_iterator_tag iterator_category(const output_iterator&)
    {
        return output_iterator_tag();
    }

    template <class _Tp, class _Distance>
    inline _Distance* distance_type(const input_iterator<_Tp, _Distance>&)
    {
        return (_Distance*)(0);
    }

    template <class _Tp>
    inline ptrdiff_t* distance_type(const _Tp*) { return (ptrdiff_t*)(0); }

    template<typename RandomAccessIter,typename BidirectionalIter,typename Distance>
    inline BidirectionalIter __copy_backward(RandomAccessIter first, RandomAccessIter last, BidirectionalIter result, random_access_iterator_tag, Distance*)
    {
        for (Distance n = last - first; n > 0; --n) {
            *--result = *--last;
        }
        return result;
    }

    template<typename BI1,typename BI2>
    inline BI2 copy_backward(BI1 first, BI1 last, BI2 result)
    {
        for (auto n = last - first; n > 0; --n) {
            *--result = *--last;
        }
        return result;
    }

}

#endif //end TE_ITERATOR_BASE_H