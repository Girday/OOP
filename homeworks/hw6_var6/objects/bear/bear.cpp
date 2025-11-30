#include "bear.h"

Bear::Bear(const std::string& name, int x, int y) : NPC(BearType, name, x, y) {}
Bear::Bear(std::istream& is) : NPC(BearType, is) {}

void Bear::print(std::ostream& os) {
    os << *this;
}

void Bear::save(std::ostream& os) {
    os << BearType << std::endl;
    NPC::save(os);
}

bool Bear::visit(std::shared_ptr<Bear> other) { 
    (void)other;
    return false; 
}

bool Bear::visit(std::shared_ptr<Elf> other) { 
    fight_notify(std::static_pointer_cast<NPC>(other), true);
    return true; 
}

bool Bear::visit(std::shared_ptr<Bandit> other) { 
    (void)other;
    return false; 
}

bool Bear::accept(std::shared_ptr<NPC> attacker) {
    return attacker->visit(std::dynamic_pointer_cast<Bear>(shared_from_this()));
}

std::ostream& operator<<(std::ostream& os, Bear& bear) {
    os << "bear: " << bear.name << " " << *static_cast<NPC*>(&bear) << std::endl;
    return os;
}
