/*
    Вариант 6. Объекты: 
        Медведь, Эльф, Разбойник  
    Правило совместимости:
        Эльфы убивают разбойников 
        Разбойники убивают разбойников 
        Медведь убивает Эльфов
*/

#include "bandit.h"
#include "elf.h"
#include "bear.h"

class TextObserver : public IFightObserver {
private:
    TextObserver() {}

public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl << "Murder --------" << std::endl;
            attacker->print(std::cout);
            defender->print(std::cout);
        }
    }
};

class FileObserver : public IFightObserver {
private:
    std::ofstream fs;
    FileObserver() { fs.open("log.txt"); }

public:
    ~FileObserver() { fs.close(); }
    static std::shared_ptr<IFightObserver> get() {
        static FileObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            fs << std::endl << "Murder --------" << std::endl;
            attacker->print(fs);
            defender->print(fs);
        }
    }
};

std::shared_ptr<NPC> factory(std::istream& is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) {
        switch (type) {
        case BearType:
            result = std::make_shared<Bear>(is);
            break;
        case ElfType:
            result = std::make_shared<Elf>(is);
            break;
        case BanditType:
            result = std::make_shared<Bandit>(is);
            break;
        }
    } else
        std::cerr << "Unexpected NPC type: " << type << std::endl;

    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, const std::string& name, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
    case BearType:
        result = std::make_shared<Bear>(name, x, y);
        break;
    case ElfType:
        result = std::make_shared<Elf>(name, x, y);
        break;
    case BanditType:
        result = std::make_shared<Bandit>(name, x, y);
        break;
    default:
        break;
    }

    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}

void save(const set_t& array, const std::string& filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    
    for (auto& n : array)
        n->save(fs);

    fs.flush();
    fs.close();
}

set_t load(const std::string& filename) {
    set_t result;
    std::ifstream is(filename);
    
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(is));
        is.close();
    } else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;

    return result;
}

std::ostream& operator<<(std::ostream& os, const set_t& array) {
    for (auto& n : array)
        n->print(os);
    
    return os;
}

set_t fight(const set_t& array, size_t distance) {
    set_t dead_list;

    for (const auto& attacker : array)
        for (const auto& defender : array)
            if ((attacker != defender) && (attacker->is_close(defender, distance))) {
                bool success = defender->accept(attacker);
                if (success)
                    dead_list.insert(defender);
            }

    return dead_list;
}

int main() {
    set_t array;

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string name;
        switch (type) {
            case BearType: name = "bear_"; break;
            case ElfType: name = "elf_"; break;
            case BanditType: name = "bandit_"; break;
            case Unknown: name = "unknown_"; break;
        }

        name += std::to_string(i);
        array.insert(factory(type, name, std::rand() % 501, std::rand() % 501));
    }
    
    std::cout << "Saving ..." << std::endl;
    save(array, "npc.txt");

    std::cout << "Loading ..." << std::endl;
    array = load("npc.txt");

    std::cout << "Fighting ..." << std::endl << array;

    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10) {
        auto dead_list = fight(array, distance);
        for (auto& d : dead_list)
            array.erase(d);
            
        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << std::endl << std::endl;
    }

    std::cout << "Survivors: " << array;

    return 0;
}
