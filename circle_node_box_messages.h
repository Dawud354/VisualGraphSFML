//
// Created by dawud on 28/07/2025.
//

#ifndef CIRCLENODEBOXMESSAGES_H
#define CIRCLENODEBOXMESSAGES_H



enum class CircleNodeBoxMessages {
    ADDED_CIRCLE, // Message to add a circle
    REMOVED_CIRCLE, // Message to remove a circle
    SELECTED_ONE_CIRCLE_TO_CONNECT, // Message to indicate one circle selected for connection
    CONNECTED_CIRCLES, // Message to connect two circles
    SELECTED_ONE_CIRCLE_TO_DISCONNECT, // Message to indicate one circle selected for disconnection
    DISCONNECTED_CIRCLES, // Message to disconnect two circles
    NOTHING_DONE, // Message to indicate no action taken

};

inline std::string to_string(CircleNodeBoxMessages msg) {
    switch (msg) {
        case CircleNodeBoxMessages::ADDED_CIRCLE: return "ADDED_CIRCLE";
        case CircleNodeBoxMessages::REMOVED_CIRCLE: return "REMOVED_CIRCLE";
        case CircleNodeBoxMessages::CONNECTED_CIRCLES: return "CONNECTED_CIRCLES";
        case CircleNodeBoxMessages::DISCONNECTED_CIRCLES: return "DISCONNECTED_CIRCLES";
        case CircleNodeBoxMessages::NOTHING_DONE: return "NOTHING_DONE";
        default: return "UNKNOWN_MESSAGE";
    }
}



#endif //CIRCLENODEBOXMESSAGES_H
