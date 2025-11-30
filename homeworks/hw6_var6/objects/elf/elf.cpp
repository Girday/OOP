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

bool Elf::visit(Bear&) { return false; }
bool Elf::visit(Elf&) { return false; }
bool Elf::visit(Bandit&) { return true; }  // Elf kills Bandit

bool Elf::accept(std::shared_ptr<NPC> attacker) {
    return attacker->visit(*this);
}

std::ostream& operator<<(std::ostream& os, Elf& elf) {
    os << "elf: " << elf.name << " " << *static_cast<NPC*>(&elf) << std::endl;
    return os;
}