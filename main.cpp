#include <iostream>
#include <string>
#include <array>

#include "Stack.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char* argv[]) {
	Stack<Email> emails(50, 50);
	uint32_t email_index = 0;
	uint32_t user_index = 0;

	User user1(user_index++, "User1", "sender@example.com");
	User user2(user_index++, "User2", "receiver@example.com");

	LOG(argv[0]);

	Email email(email_index++, "sender@example.com", "receiver@example.com", "Subject Matter");


	// TODO: Handle incoming emails


	// TODO: Handle outgoing emails
	

	// TODO: Handle spam emails
	

	// TODO: Handle email prioritization


	return 0;
}