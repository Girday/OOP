#pragma once

#include "npc.h"

struct Elf : public NPC {
    Elf(const std::string& name, int x, int y);
    Elf(std::istream& is);

    void print(std::ostream& os) override;
    void save(std::ostream& os) override;

    bool visit(std::shared_ptr<Bear> other) override;
    bool visit(std::shared_ptr<Elf> other) override;
    bool visit(std::shared_ptr<Bandit> other) override;

    bool accept(std::shared_ptr<NPC> attacker) override;

    friend std::ostream& operator<<(std::ostream& os, Elf& elf);
};
