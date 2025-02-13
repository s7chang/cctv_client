#include "xml_parser.h"

void XMLParser::parseMetadata(const std::string& xmlData) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xmlData.c_str());

    if (!result) {
        std::cerr << "XML parsing failed: " << result.description() << std::endl;
        return;
    }

    for (auto& obj : doc.child("tt:MetaDataStream").child("tt:VideoAnalytics").children("tt:Object")) {
        std::string objectId = obj.attribute("ObjectId").value();
        std::string type = obj.child("tt:Class").child("tt:Type").child_value();
        std::cout << "Detected Object ID: " << objectId << ", Type: " << type << std::endl;
    }
}
