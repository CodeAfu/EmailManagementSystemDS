#include <iostream>
#include <string>
#include <array>

#include "PrintColoring.hpp"
#include "IdxGen.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

User createUser(IdxGen& idxGen);
void test(IdxGen& idxGen);

int main(int argc, char** argv) {
	IdxGen idxGen; // Generates Index for User and Email objects
	system("cls");
	// test(idxGen);

	// TODO: Console Flow
	while (true) {
		// TODO: Handle incoming emails
		// TODO: Handle outgoing emails
		// TODO: Handle spam emails
		// TODO: Handle email prioritization
		break;
	}

	std::cout << "END" << std::endl;
	std::cin.get();
	return 0;
}


void test(IdxGen& idxGen) {
	User user_one(idxGen.nextUser(), "John", "j1@example.com");
	User user_two(idxGen.nextUser(), "Jane", "j2@example.com");

	Email email_one(idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(), 
		"First", "Hi there, I hope you are doing well. I wanted to invite you to a meeting on Friday at 2 PM to discuss the project. Let me know if you can make it.");
	Email email_two(idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(), 
		"Second", "Hey there, I wanted to let you know that the meeting time has changed to 3 PM on Friday. Sorry for the inconvenience.");
	Email email_three(idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(),
		"Third", "Hi there, I just wanted to let you know that the meeting on Friday has been cancelled. I apologize for any inconvenience this may have caused. We will be rescheduling the meeting at a later time.");
	Email email_four(idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(),
		"Fourth", "Hi there, I just wanted to make sure that you are aware that the meeting has been cancelled. I will let you know once it has been rescheduled.");
	
	user_one.receiveEmail(email_one);
	user_one.receiveEmail(email_two);
	user_one.receiveEmail(email_three);
	user_one.receiveEmail(email_four);
}

// User createUser(IdxGen& idxGen) {
//     int id;
//     std::string name, emailAddress;
    
//     std::cout << "Enter user name: ";
//     std::cin >> name;
    
//     std::cout << "Enter user email address: ";
//     std::cin >> emailAddress;
    
//     User newUser(id, name, emailAddress);
    
//     return newUser;
// }