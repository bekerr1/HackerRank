//
//  parser.hpp
//
//  Created by Brendan Kerr on 2/13/18.
//  Copyright © 2018 Brendan Kerr. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>


struct TagMeta {
    string name;
    map<string, string> attributes;
};
struct TagNode {
    TagMeta info;
    map<string, TagNode *> children;
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
    
private:
    void newAttribute(std::iostream&);
    TagNode* parseLine(std::string);
    parseQuery(map<string, TagNode*>, string);
    tagExists(map<string, TagNode*>, string);
    tagExists(map<string, string>, string);
    extractTag(const string, size_t&, size_t&, string&);
    attributeTag(const string, size_t&, size_t&, string&);
};

#endif /* parser_hpp */
