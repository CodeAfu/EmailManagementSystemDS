#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>

#include "ColorFormat.hpp"
#include "IdxGen.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

static IdxGen s_idxGen;  // Generates Index for User and Email objects

User createUser();
void test();

int main(int argc, char** argv) {
	system("cls");

	{ test(); }

	// TODO: Console Flow
	while (true) {
		// TODO: Handle incoming emails
		// TODO: Handle outgoing emails
		// TODO: Handle spam emails
		// TODO: Handle email prioritization
		break;
	}

	ColorFormat::print("END", Cyan);
	std::cin.get();
	return 0;
}

void test() {
	User user_one(s_idxGen.nextUser(), "John", "j1@example.com");
	User user_two(s_idxGen.nextUser(), "Jane", "j2@example.com");

	Email email_one(s_idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(), 
		"First", "Hi there, I hope you are doing well. I wanted to invite you to a meeting on Friday at 2 PM to discuss the project. Let me know if you can make it.");
	Email email_two(s_idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(), 
		"Second", "Hey there, I wanted to let you know that the meeting time has changed to 3 PM on Friday. Sorry for the inconvenience.");
	Email email_three(s_idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(),
		"Third", "Hi there, I just wanted to let you know that the meeting on Friday has been cancelled. I apologize for any inconvenience this may have caused. We will be rescheduling the meeting at a later time.");
	Email email_four(s_idxGen.nextEmail(), user_one.getEmailAddress(), user_two.getEmailAddress(),
		"Fourth", "Hi there, I just wanted to make sure that you are aware that the meeting has been cancelled. I will let you know once it has been rescheduled.");

	user_one.composeEmail(email_one, user_two);
	user_one.composeEmail(email_two, user_two);
	user_one.composeEmail(email_three, user_two);
	user_one.composeEmail(email_four, user_two);

	user_two.composeEmail(email_three, user_one);
	user_two.composeEmail(email_four, user_one);
	
	EmailService::GetInstance().sendAll();
	
	std::cout << std::endl;
	user_two.viewInbox();
	std::cout << std::endl;

	Email email = user_two.getFromInbox(3);
	email.display();

}
