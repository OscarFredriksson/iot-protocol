#include <array>
#include <cstdint>

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
    uint8_t version : 2; 
    CoapType type;
    uint8_t tokenLength : 4;

};