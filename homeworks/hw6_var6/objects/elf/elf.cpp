#include "elf.h"

Elf::Elf(const std::string& name, int x, int y) : NPC(ElfType, name, x, y) {}
Elf::Elf(std::istream& is) : NPC(ElfType, is) {}

void Elf::print(std::ostream& os) {
    os << *this;
}

void Elf::save(std::ostream& os) {
    os << ElfType << std::endl;
    NPC::save(os);
}

bool Elf::visit(std::shared_ptr<Bear> other) { 
    (void)other;
    return false; 
}

bool Elf::visit(std::shared_ptr<Elf> other) { 
    (void)other;
    return false; 
}

bool Elf::visit(std::shared_ptr<Bandit> other) { 
    fight_notify(std::static_pointer_cast<NPC>(other), true);
    return true; 
}

bool Elf::accept(std::shared_ptr<NPC> attacker) {
    return attacker->visit(std::dynamic_pointer_cast<Elf>(shared_from_this()));
}

std::ostream& operator<<(std::ostream& os, Elf& elf) {
    os << "elf: " << elf.name << " " << *static_cast<NPC*>(&elf) << std::endl;
    return os;
}