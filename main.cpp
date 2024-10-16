#include <iostream>
#include <string>
#include <array>

#include "Stack.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char** argv) {
	LOG(argv[0]);

	Stack<Email> emails(50, 50);
	unsigned int email_index = 0;
	unsigned int user_index = 0;

	User user1(user_index++, "User1", "sender@example.com");
	User user2(user_index++, "User2", "receiver@example.com");

	Email email(email_index++, "sender@example.com", "receiver@example.com", "Subject Matter");

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