#include "coapmessage.h"
#include <iostream>

CoapMessage::CoapMessage(CoapCode code, uint16_t messageId, const std::string& path):
        code(code), messageId(messageId), path(path)
{}

std::vector<char> CoapMessage::serialize()
{

    std::vector<char> msg = {
        char((version << 6) | (type << 4) | tokenLength),
        char(code),
        char(messageId >> 8),  
        char(messageId & 0xff),
        char(optionDelta << 4 | path.size()),
        // char(0xb4),
        // char(0x74), 
        // char(0x65), 
        // char(0x73), 
        // char(0x74),
    };

    for(auto c: path) msg.push_back(c);

    return msg;
}