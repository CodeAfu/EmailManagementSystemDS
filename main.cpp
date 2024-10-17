#include <iostream>
#include <string>
#include <array>

#include "Stack.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char** argv) {
	unsigned int email_index = 0;
	unsigned int user_index = 0;

	User sender(++user_index, "User1", "sender@example.com");
	User receiver(++user_index, "User2", "receiver@example.com");

	Email email(++email_index, sender.getEmailAddress(), receiver.getEmailAddress(), "Subject", "Body");
	
	sender.composeEmail(email);
	sender.sendComposedEmail(receiver);
	receiver.log();
	receiver.getInbox().peek().display();

	// TODO: Console Flow
	while (true) {
		// TODO: Handle incoming emails
		// TODO: Handle outgoing emails
		// TODO: Handle spam emails
		// TODO: Handle email prioritization
		break;
	}



	return 0;
}
