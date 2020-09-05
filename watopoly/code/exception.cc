#include "exception.h"

Exception :: Exception(std::string message):
	message{message}
{}

std::string Exception :: getMessage(){
	return message;
}
