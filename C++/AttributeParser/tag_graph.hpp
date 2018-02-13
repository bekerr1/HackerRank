//
//  tag_graph.hpp
//
//  Created by Brendan Kerr on 2/13/18.
//  Copyright © 2018 Brendan Kerr. All rights reserved.
//

#ifndef tag_graph_hpp
#define tag_graph_hpp

#include <stdio.h>
#include "parser.hpp"

class TagTree {
public:
    void constructTree();
    void analyzeTree();
    TagNode* produceLeaders(int, TagNode*, int&);
private:
    std::vector<TagNode*> leaders;
    Parser p;
    
    void analyzeNode(TagNode*, TagNode*);
};

#endif /* tag_graph_hpp */
