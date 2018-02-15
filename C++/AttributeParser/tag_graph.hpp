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

class TagGraph {
public:
    void constructGraph(istream&);
    void analyzeGraph();
    
private:
    map<string, TagNode*> leaders;
    Parser p;
    TagNode* produceLeaders(int, TagNode*, int&, istream&);
    void analyzeNode(TagNode*, TagNode*);
};

#endif /* tag_graph_hpp */
