#ifndef TOOLS_H_
#define TOOLS_H_

#include <string>

namespace pr {
    template <typename iterator>
    size_t count (iterator begin, iterator end){
        size_t count = 0;
        for(iterator it = begin; it != end; ++it){
            ++count;
        }
        return count;
    }

    template <typename iterator, typename T>
    size_t count (iterator begin, iterator end, const T& value){
        size_t count = 0;
        for(iterator it = begin; it != end; ++it){
            if(*it == value){
                ++count;
            }
        }
        return count;
    }
}

#endif /* TOOLS_H_ */