#include "bandit.h"

Bandit::Bandit(const std::string& name, int x, int y) : NPC(BanditType, name, x, y) {}
Bandit::Bandit(std::istream& is) : NPC(BanditType, is) {}

void Bandit::print(std::ostream& os) {
    os << *this;
}

void Bandit::save(std::ostream& os) {
    os << BanditType << std::endl;
    NPC::save(os);
}

bool Bandit::visit(Bear&) { return false; }
bool Bandit::visit(Elf&) { return false; }
bool Bandit::visit(Bandit&) { return true; }  // Bandit kills Bandit

bool Bandit::accept(std::shared_ptr<NPC> attacker) {
    return attacker->visit(*this);
}

std::ostream& operator<<(std::ostream& os, Bandit& Bandit) {
    os << "Bandit: " << Bandit.name << " " << *static_cast<NPC*>(&Bandit) << std::endl;
    return os;
}
