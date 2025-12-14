#include "elf.h"
#include "bandit.h"
#include "bear.h"

Elf::Elf(const std::string& name, int x, int y) : NPC(ElfType, name, x, y) {}
Elf::Elf(std::istream& is) : NPC(ElfType, is) {}

void Elf::print(std::ostream& os) {
    os << *this;
}

void Elf::save(std::ostream& os) {
    os << ElfType << std::endl;
    NPC::save(os);
}

bool Elf::visit([[maybe_unused]] std::shared_ptr<Bear> other) { 
    return false; 
}

bool Elf::visit([[maybe_unused]] std::shared_ptr<Elf> other) { 
    return false; 
}

bool Elf::visit(std::shared_ptr<Bandit> other) { 
    int attack = std::rand() % 6 + 1;
    int defense = std::rand() % 6 + 1;

    if (attack >= defense) {
        fight_notify(std::static_pointer_cast<NPC>(other), true);
        return true;
    }
    
    return false; 
}

bool Elf::accept(std::shared_ptr<NPC> attacker) {
    return attacker->visit(std::dynamic_pointer_cast<Elf>(shared_from_this()));
}

std::ostream& operator<<(std::ostream& os, Elf& elf) {
    os << "Эльф: " << elf.name << " " << *static_cast<NPC*>(&elf) << std::endl;
    return os;
}