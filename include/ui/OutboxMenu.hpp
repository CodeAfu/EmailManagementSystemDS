#pragma once

namespace OutboxMenu::Sent {
    void viewSentEmails(User& user);
}

namespace OutboxMenu::Draft {
    void viewDraftEmails(User& user);
}

namespace OutboxMenu::Compose {
    void composeEmail(User& user);
}