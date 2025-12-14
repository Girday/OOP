#include "npc.h"

NPC::NPC(NpcType t, const std::string& n, int _x, int _y) : type(t), name(n), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream& is) : type(t) {
    is >> name >> x >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto& o : observers)
        o->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return dx * dx + dy * dy <= (int)(distance * distance);
}

void NPC::save(std::ostream& os) {
    os << name << std::endl << x << std::endl << y << std::endl;
}

std::ostream& operator<<(std::ostream& os, NPC& npc) {
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}
