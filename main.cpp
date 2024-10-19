#include <iostream>
#include <string>
#include <array>

#include "Stack.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char** argv) {
	{
		system("cls");

		unsigned int email_index = 0;
		unsigned int user_index = 0;

		User user_one(++user_index, "User1", "User1@example.com");
		User user_two(++user_index, "User2", "User2@example.com");

		Email email_one(email_index++, user_one.getEmailAddress(), user_two.getEmailAddress(), 
			"First", "Hi there, I hope you are doing well. I wanted to invite you to a meeting on Friday at 2 PM to discuss the project. Let me know if you can make it.");
		Email email_two(email_index++, user_one.getEmailAddress(), user_two.getEmailAddress(), 
			"Second", "Hey there, I wanted to let you know that the meeting time has changed to 3 PM on Friday. Sorry for the inconvenience.");
		Email email_three(email_index++, user_one.getEmailAddress(), user_two.getEmailAddress(),
			"Third", "Hi there, I just wanted to let you know that the meeting on Friday has been cancelled. I apologize for any inconvenience this may have caused. We will be rescheduling the meeting at a later time.");
		Email email_four(email_index++, user_one.getEmailAddress(), user_two.getEmailAddress(),
			"Fourth", "Hi there, I just wanted to make sure that you are aware that the meeting has been cancelled. I will let you know once it has been rescheduled.");
		Email email_five(email_index++, user_one.getEmailAddress(), user_two.getEmailAddress(),
			"Fifth", "Hi there, I just wanted to let you know that the meeting has been rescheduled for next Thursday at 2 PM. I hope you can make it. Let me know if you have any conflicts.");
		
		user_one.sendDraftEmail(user_two);
		user_one.draftEmail(email_one);
		user_one.sendDraftEmail(user_two);

		user_one.sendEmail(email_two, user_two);
		user_one.sendEmail(email_three, user_two);
		user_one.sendEmail(email_four, user_two);
		user_one.sendEmail(email_five, user_two);

		user_two.log();
		user_two.getInbox().peek().display();

		// TODO: Console Flow
		while (true) {
			// TODO: Handle incoming emails
			// TODO: Handle outgoing emails
			// TODO: Handle spam emails
			// TODO: Handle email prioritization
			break;
		}
	}
	std::cout << "End of program" << std::endl;
	std::cin.get();
	return 0;
}
