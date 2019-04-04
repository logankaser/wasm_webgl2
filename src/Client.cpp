#include "Client.hpp"

Client::Client() :
window(_window_target),
input(_input_target, &window)
{}
