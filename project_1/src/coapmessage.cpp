#include "coapmessage.h"

CoapMessage::CoapMessage(CoapCode code, uint16_t messageId, const std::string& path):
        code(code), messageId(messageId), path(path)
{}

std::ostream& operator<<(std::ostream& os, const CoapType& rhs) {
    switch(rhs) {
        case Confirmable: 
            os << "Confirmable";
            break;
        case NonConfirmable: 
            os << "Non Confirmable";
            break;
        case Acknowledgement: 
            os << "Acknowledgement";
            break;
        case Reset: 
            os << "Reset";
            break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const CoapCode& rhs) {
    switch(rhs) {
        case GET: 
            os << "GET";
            break;
        case POST: 
            os << "POST";
            break;
        case PUT: 
            os << "PUT";
            break;
        case DELETE: 
            os << "DELETE";
            break;
        default: 
            os << "Other";
            break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const CoapMessage& rhs) {
    
    std::string delimiter = ", ";

    os << "\n----Coap Message----\n"; 
    os << "Version: " << int(rhs.version) << delimiter;
    os << "Type: " << rhs.type << delimiter;
    os << "Token Length: " << int(rhs.tokenLength) << delimiter; 
    os << "Code: " << rhs.code << delimiter;
    os << "Message Id: " << rhs.messageId << delimiter; 
    os << "Option Delta: " << int(rhs.optionDelta) << delimiter;
    os << "Option: " << rhs.path;
    os << "\n--------------------\n";

    return os;
}


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