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

#include <thread>
#include <mutex>
#include <queue>
#include <optional>
#include <chrono>
#include <atomic>
#include <array>

using namespace std::chrono_literals;

std::mutex print_mutex;

constexpr int MAP_X = 50;
constexpr int MAP_Y = 50;
constexpr int GRID = 25;

const bool USE_TEXT_OBSERVER = false;
const bool USE_FILE_OBSERVER = true;

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
            std::lock_guard<std::mutex> lck(print_mutex);
            std::cout << "\n" << "Убийца --------" << "\n";
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
            fs << "\n" << "Убийца --------" << "\n";
            attacker->print(fs);
            defender->print(fs);
        }
    }
};

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
        if constexpr (USE_TEXT_OBSERVER)
            result->subscribe(TextObserver::get());
        if constexpr (USE_FILE_OBSERVER)
            result->subscribe(FileObserver::get());
    }

    return result;
}

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
private:
    std::queue<FightEvent> events;
    std::mutex mtx;
    FightManager() {}

public:
    static FightManager& get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent&& event) {
        std::lock_guard<std::mutex> lck(mtx);
        events.push(event);
    }

    void operator()() {
        while (true) {
            std::optional<FightEvent> event;
            
            {
                std::lock_guard<std::mutex> lck(mtx);
                if (!events.empty()) {
                    event = events.front();
                    events.pop();
                }
            }

            if (event)
                if (event->attacker->is_alive() && event->defender->is_alive())
                    if (event->defender->accept(event->attacker))
                        event->defender->must_die();

            std::this_thread::sleep_for(100ms);
        }
    }
};

void draw_map(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::array<std::pair<std::string, char>, GRID * GRID> field{};

    for (auto& cell : field)
        cell = {"", ' '};

    for (const auto& npc : npcs) {
        if (!npc->is_alive())
            continue;
        
        auto [x, y] = npc->position();
        int gx = std::min(x * GRID / MAP_X, GRID - 1);
        int gy = std::min(y * GRID / MAP_Y, GRID - 1);

        char c = '?';
        switch (npc->type) {
            case BearType: c = 'M'; break;
            case ElfType: c = 'E'; break;
            case BanditType: c = 'R'; break;
            default: break;
        }

        field[gx + gy * GRID] = {npc->get_color(), c};
    }

    std::lock_guard<std::mutex> lck(print_mutex);
    std::cout << "\n";

    for (int y = 0; y < GRID; ++y) {
        for (int x = 0; x < GRID; ++x) {
            auto [color, c] = field[x + y * GRID];

            if (c != ' ')
                std::cout << "|" << color << c << "\033[0m|";
            else 
                std::cout << "| |";
        }
        std::cout << "\n";
    }
    std::cout << std::string(GRID * 3, '=') << "\n";

    int alive_bears = 0, alive_elves = 0, alive_bandits = 0;
    for (const auto& npc : npcs) {
        if (!npc->is_alive()) continue;
        switch (npc->type) {
            case BearType:   alive_bears++; break;
            case ElfType:    alive_elves++; break;
            case BanditType: alive_bandits++; break;
            default: break;
        }
    }

    std::cout << "\033[33mМедведи: " << alive_bears << "\033[0m | "
              << "\033[32mЭльфы: " << alive_elves << "\033[0m | "
              << "\033[31mРазбойники: " << alive_bandits << "\033[0m | "
              << "Всего: " << (alive_bears + alive_elves + alive_bandits) << "/50\n";
}


int main() {
    std::srand(static_cast<unsigned>(time(nullptr)));

    std::vector<std::shared_ptr<NPC>> npcs;

    std::cout << "Создание 50 NPC..." << "\n";
    for (int i = 0; i < 50; ++i) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string name;
        switch (type) {
            case BearType: name = "Bear_"; break;
            case ElfType: name = "Elf_"; break;
            case BanditType: name = "Bandit_"; break;
            case Unknown: name = "Unknown_"; break;
        }
        name += std::to_string(i);
        
        npcs.push_back(factory(type, name, std::rand() % MAP_X, std::rand() % MAP_Y));
    }

    std::atomic<bool> running{true};

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&npcs, &running]() {
        while (running) {
            for (auto& npc : npcs) {
                if (!npc->is_alive())
                    continue;

                int move_dist = npc->get_move_distance();
                int shift_x = std::rand() % (2 * move_dist + 1) - move_dist;
                int shift_y = std::rand() % (2 * move_dist + 1) - move_dist;
                
                npc->move(shift_x, shift_y, MAP_X, MAP_Y);
            }

            for (auto& attacker : npcs) {
                if (!attacker->is_alive())
                    continue;
                
                int kill_dist = attacker->get_kill_distance();
                
                for (auto& defender : npcs) {
                    if (attacker == defender || !defender->is_alive())
                        continue;
                    
                    if (attacker->is_close(defender, kill_dist))
                        FightManager::get().add_event({attacker, defender});
                }
            }

            std::this_thread::sleep_for(100ms);
        }
    });

    std::thread print_thread([&npcs, &running]() {
        while (running) {
            draw_map(npcs);
            std::this_thread::sleep_for(1s);
        }
    });

    std::this_thread::sleep_for(30s);
    running = false;

    move_thread.join();
    print_thread.join();
    fight_thread.detach();

    std::cout << "\n=== ВЫЖИВШИЕ ===\n";
    int survivors = 0;
    for (const auto& npc : npcs) {
        if (npc->is_alive()) {
            npc->print(std::cout);
            survivors++;
        }
    }
    std::cout << "\nВсего выжило: " << survivors << "/" << npcs.size() << "\n";
    std::cout << "Лог боёв сохранён в файл log.txt" << "\n";
    
    return 0;
}
