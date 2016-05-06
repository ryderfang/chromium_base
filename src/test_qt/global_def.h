#ifndef GLOBAL_DEF_H_
#define GLOBAL_DEF_H_

#include "base/basictypes.h"

#include <string>
#include <vector>

struct VideoInfo {
    VideoInfo() : offset(0) {
    }

    VideoInfo(const std::string& name) : 
        file_name(name),
        offset(0) {
    }

    size_t sz() { return piece.size(); }

    std::string file_name;

    std::string file_hash;

    size_t offset;

    std::vector<std::string> piece;
};

#endif // !GLOBAL_DEF_H_