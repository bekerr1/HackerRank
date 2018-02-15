//
//  parser.cpp
//
//  Created by Brendan Kerr on 2/13/18.
//  Copyright © 2018 Brendan Kerr. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "parser.hpp"

using namespace std;

TagNode* Parser::parseLine(string line) {
    TagNode *nn = new TagNode();
    size_t next = 0;
    size_t last = 0;
    stringstream st = stringstream(line);
    char cur;
    TagMeta meta;
    st.get(cur);
    if (cur == START) {
        if (st.peek() == END) { // ending tag
            return nullptr;
        } else { //tag name
            while (cur = st.get()) {
                if (cur == SEP || cur == STOP) {
                    break;
                }
                meta.name += cur;
            }
            if (cur == STOP) {
                nn->info = meta;
                return nn;
            }
            while (true) {
                newAttribute(meta.attributes, st);
                if ((cur = st.peek()) == STOP) {
                    st.get(cur);
                    break;
                } else {
                    st.get(cur);
                }
            }
        }
    }
    nn->info = meta;
    return nn;
}

void Parser::newAttribute(iostream &stream) {
    char current;
    string name;
    string value;
    while (current = stream.get()) {
        if (current == SEP) {
            break;
        } else {
            name += current;
        }
    }
    stream.seekg(2, ios_base::cur); // skip ' = ' chars
    while (current = stream.get()) {
        if (current == SEP || current == STOP) {
            stream.putback(current);
            break;
        } else {
            if (current != DISCARD) {
                value += current;
            }
        }
    }
    attrs[name] = value;
}

string Parser::parseQuery(map<string, TagNode*> leaders, string query) {
    size_t start, end;
    string tag;
    TagNode *current;
    if (extractTag(query, start, end, tag) && tagExists(leaders, tag)) {
        current = leaders[tag];
        while (extractTag(query, start, end, tag)) {
            if (tagExists(current->children, tag)) {
                current = current->children[tag];
            } else {
                return "Not Found!";
            }
        }
        if (tagExists(current->info.attributes, attributeTag(query, start, end, tag))) {
            return current->info.attributes[tag];
        } else {
            return "Not Found!";
        }
    } else {
        return "Not Found!";
    }
}

bool Parser::tagExists(map<string, TagNode*> m, string tag) {
    map<string, TagNode*>::const_iterator itr = m.find(tag);
    if (itr != m.end()) {
        return true;
    } else {
        return false;
    }
}

bool Parser::tagExists(map<string, string> m, string tag) {
    map<string, string>::const_iterator itr = m.find(tag);
    if (itr != m.end()) {
        return true;
    } else {
        return false;
    }
}

bool Parser::extractTag(const string query, size_t &start, size_t &end, string &tag) {
    if ((end = query.find(CHILD, start)) != string::npos) {
        size_t sz = end - start;
        tag = query.substr(start, sz);
        start = end + 1;
        return true;
    } else if ((end = query.find(DATA, start)) != string::npos) {
        size_t sz = end - start;
        tag = query.substr(start, sz);
        start = end + 1;
        return true;
    } else {
        return false;
    }
}

string Parser::attributeTag(const string query, size_t &start, size_t &end, string &tag) {
    return query.substr(start);
}


