#include "bandit.h"
#include "elf.h"
#include "bear.h"

Bandit::Bandit(const std::string& name, int x, int y) : NPC(BanditType, name, x, y) {}
Bandit::Bandit(std::istream& is) : NPC(BanditType, is) {}

void Bandit::print(std::ostream& os) {
    os << *this;
}

void Bandit::save(std::ostream& os) {
    os << BanditType << std::endl;
    NPC::save(os);
}

bool Bandit::visit([[maybe_unused]] std::shared_ptr<Bear> other) { 
    return false; 
}

bool Bandit::visit([[maybe_unused]] std::shared_ptr<Elf> other) { 
    return false; 
}

bool Bandit::visit(std::shared_ptr<Bandit> other) { 
    int attack = std::rand() % 6 + 1;
    int defense = std::rand() % 6 + 1;

    if (attack > defense) {
        fight_notify(std::static_pointer_cast<NPC>(other), true);
        return true;
    }
    
    return false; 
}

bool Bandit::accept(std::shared_ptr<NPC> attacker) {
    return attacker->visit(std::dynamic_pointer_cast<Bandit>(shared_from_this()));
}

std::ostream& operator<<(std::ostream& os, Bandit& bandit) {
    os << "Разбойник: " << bandit.name << " " << *static_cast<NPC*>(&bandit) << std::endl;
    return os;
}
