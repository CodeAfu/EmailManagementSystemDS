#pragma once

namespace OutboxMenu::Sent {
    void run(User& user);
}

namespace OutboxMenu::Draft {
    void run(User& user);
}

namespace OutboxMenu::Compose {
    void run(User& user);
}