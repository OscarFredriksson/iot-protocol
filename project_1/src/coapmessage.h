#include <array>
#include <cstdint>
#include <string>
#include <vector>

enum CoapType {
    Confirmable = 0x00,
    NonConfirmable = 0x01,
    Acknowledgement = 0x10,
    Reset = 0x11
};

enum CoapCode {
    //Method Codes
    EMPTY = 0x00,
    GET = 0x01,
    POST = 0x02,
    PUT = 0x03,
    DELETE = 0x04,

    //Response Codes
    //Success
    Created = 0x41,
    Deleted = 0x42,
    Valid = 0x43,
    Changed = 0x44,
    Content = 0x45,
    Continue = 0x5f,

    //Client Error
    BadRequest = 0x80,
    Unauthorized = 0x81,
    BadOption = 0x82,
    Forbidden = 0x83,
    NotFound = 0x84,
    MethodNotAllowed = 0x85,
    NotAcceptable = 0x86,
    RequestEntityIncomplete = 0x88,
    PreconditionFailed = 0x8c,
    RequestEntityTooLarge = 0x8d,
    UnsupportedContentFormat = 0x8f,

    //Server Error
    InternalServerError = 0xa0,
    NotImplemented = 0xa1,
    BadGateway = 0xa2,
    ServiceUnavailable = 0xa3,
    GatewayTimeout = 0xa4,
    ProxyingNotSupported = 0xa5
};

class CoapMessage {
public:
    CoapMessage(CoapCode code, uint16_t messageId, const std::string& path);

    const char version = 0x01;
    const CoapType type = Confirmable; 
    const uint8_t tokenLength: 4 = 0;
    const uint8_t optionDelta: 4 = 11; //Uri-Path

    const CoapCode code;
    const uint16_t messageId;
    const std::string path;

    std::vector<char> serialize();
};