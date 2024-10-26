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

void test();

int main(int argc, char** argv) {
	system("cls");

	test();

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
	User john(s_idxGen.nextUser(), "John", "j1@example.com");
	User potato(s_idxGen.nextUser(), "Potato", "j2@example.com");

	Email email_one(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(), 
		"First", "Hi there, I hope you are doing well. I wanted to invite you to a meeting on Friday at 2 PM to discuss the project. Let me know if you can make it.");
	Email email_two(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(), 
		"Second", "Hey there, I wanted to let you know that the meeting time has changed to 3 PM on Friday. Sorry for the inconvenience.");
	Email email_three(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(),
		"Third", "Hi there, I just wanted to let you know that the meeting on Friday has been cancelled. I apologize for any inconvenience this may have caused. We will be rescheduling the meeting at a later time.");
	Email email_four(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(),
		"Fourth", "Hi there, I just wanted to make sure that you are aware that the meeting has been cancelled. I will let you know once it has been rescheduled.");

	john.composeDraftEmail(email_one, potato);
	john.composeDraftEmail(email_two, potato);
	john.composeDraftEmail(email_three, potato);
	john.composeDraftEmail(email_four, potato);

	potato.composeDraftEmail(email_three, john);
	potato.composeDraftEmail(email_four, john);

	Stack<Email> inbox = john.getInbox().getEmails();
	LLQueue<Email*> draft_emails = john.getOutbox().getDraftEmails();
	LLQueue<Email*> sent_emails = john.getOutbox().getSentEmails();

	john.viewDraftEmails();

	std::cout << std::endl;	
	std::cout << "Outbox Size: " << john.getOutboxSize() << std::endl;
	john.sendDraftEmails();
	std::cout << "Outbox Size: " << john.getOutboxSize() << std::endl;
	std::cout << std::endl;	
	
	std::cout << std::endl;
	john.viewDraftEmails();
	std::cout << std::endl;

	std::cout << std::endl;
	potato.viewInbox();
	std::cout << std::endl;

	std::cout << std::endl;
	john.viewSentEmails();
	std::cout << std::endl;

	Email email = potato.getFromInbox(3);
	email.display();
	std::cout << std::endl;

}
