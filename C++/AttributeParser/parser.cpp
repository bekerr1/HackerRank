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

Attribute Parser::newAttribute(iostream &stream) {
    //cout << "New Attriute: " << endl;
    char current;
    Attribute attr;
    while ((current = stream.get())) {
        if (current == SEP) {
            break;
        } else {
            attr.name += current;
        }
    }
    stream.seekg(2, ios_base::cur); // skip ' = ' chars
    while ((current = stream.get())) {
        if (current == SEP || current == STOP) {
            stream.putback(current);
            break;
        } else {
            if (current != DISCARD) {
                attr.value += current;
            }
        }
    }
    //cout << "Name: " << attr.name << " Value: " << attr.value << endl;
    return attr;
}

TagNode* Parser::parseLine(string line) {
    
    //cout << "Parsing line: " << line << endl;
    TagNode *nn = new TagNode();
    stringstream st = stringstream(line);
    char cur;
    TagMeta meta;
    st.get(cur);
    //cout << cur << endl;
    if (cur == START) {
        if (st.peek() == END) { // ending tag
            cout << "End char hit!" << endl;
            return nullptr;
        } else { //tag name
            while ((cur = st.get())) {
                if (cur == SEP || cur == STOP) {
                    break;
                }
                //cout << cur;
                meta.name += cur;
            }
            //cout << endl;
            if (cur == STOP) {
                //cout << "tag with no attributes" << endl;
                nn->info = meta;
                return nn;
            }
            while (true) {
                meta.attributes.push_back(newAttribute(st));
                if ((cur = st.peek()) == STOP) {
                    st.get(cur);
                    //cout << "Stop char: " << cur << endl;
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
