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

bool Bear::visit(Bear&) { return false; }
bool Bear::visit(Elf&) { return true; }  // Bear kills Elf
bool Bear::visit(Bandit&) { return false; }

bool Bear::accept(std::shared_ptr<NPC> attacker) {
    return attacker->visit(*this);
}

std::ostream& operator<<(std::ostream& os, Bear& bear) {
    os << "bear: " << bear.name << " " << *static_cast<NPC*>(&bear) << std::endl;
    return os;
}
