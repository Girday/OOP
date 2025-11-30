#pragma once

#include "npc.h"

struct Bear : public NPC {
    Bear(const std::string& name, int x, int y);
    Bear(std::istream& is);

    void print(std::ostream& os) override;
    void save(std::ostream& os) override;

    bool visit(Bear& other) override;
    bool visit(Elf& other) override;
    bool visit(Bandit& other) override;

    bool accept(std::shared_ptr<NPC> attacker) override;

    friend std::ostream& operator<<(std::ostream& os, Bear& bear);
};
