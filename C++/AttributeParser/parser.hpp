//
//  parser.hpp
//
//  Created by Brendan Kerr on 2/13/18.
//  Copyright © 2018 Brendan Kerr. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>

struct Attribute {
    std::string name;
    std::string value;
};
struct TagMeta {
    std::string name;
    std::vector<Attribute> attributes;
};
struct TagNode {
    TagMeta info;
    std::vector<TagNode *> children;
};

struct Parser {
    const char START = '<';
    const char STOP = '>';
    const char END = '/';
    const char CHILD = '.';
    const char DATA = '~';
    const char SEP = ' ';
    const char VAL = '=';
    const char DISCARD = '\"';
    
    Attribute newAttribute(std::iostream&);
    TagNode* parseLine(std::string);
};

#endif /* parser_hpp */
