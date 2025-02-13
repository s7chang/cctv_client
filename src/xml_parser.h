#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <string>
#include "pugixml.hpp"

class XMLParser {
public:
    static void parseMetadata(const std::string& xmlData);
};

#endif // XML_PARSER_H
