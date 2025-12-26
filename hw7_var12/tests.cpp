#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <optional>
#include <chrono>
#include <atomic>
#include <array>

#include "bear.h"
#include "elf.h"
#include "bandit.h"

using namespace std::chrono_literals;
std::mutex print_mutex;

constexpr int MAP_X = 50;
constexpr int MAP_Y = 50;
constexpr int GRID = 25;

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
        std::lock_guard<std::mutex> lck(mtx);
        while (!events.empty()) {
            auto event = events.front();
            events.pop();
            if (event.attacker->is_alive() && event.defender->is_alive()) {
                if (event.defender->accept(event.attacker)) {
                    event.defender->must_die();
                }
            }
        }
    }
};

void draw_map(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::array<std::pair<std::string, char>, GRID * GRID> field{};
    int bears = 0, elfs = 0, bandits = 0;

    for (auto& npc : npcs) {
        if (!npc->is_alive()) continue;

        auto [x, y] = npc->position();
        int gx = std::min(x * GRID / MAP_X, GRID - 1);
        int gy = std::min(y * GRID / MAP_Y, GRID - 1);
        char symbol;
        std::string color = npc->get_color();

        switch (npc->type) {
            case BearType: symbol = 'M'; ++bears; break;
            case ElfType: symbol = 'E'; ++elfs; break;
            case BanditType: symbol = 'R'; ++bandits; break;
            default: continue;
        }

        field[gx + gy * GRID] = {color, symbol};
    }

    {
        std::lock_guard<std::mutex> lck(print_mutex);
        for (int y = 0; y < GRID; ++y) {
            for (int x = 0; x < GRID; ++x) {
                auto [color, c] = field[x + y * GRID];
                if (c != ' ') std::cout << "|" << color << c << "\033[0m|";
                else std::cout << "| |";
            }
            std::cout << "\n";
        }
        std::cout << std::string(GRID * 3, '=') << "\n";
        std::cout << "Медведи: " << bears << " | Эльфы: " << elfs << " | Разбойники: " << bandits << " | Всего: " << bears + elfs + bandits << "/50\n";
    }
}

TEST(NPCCreation, CreateBear) {
    Bear bear("TestBear", 100, 200);
    EXPECT_EQ(bear.type, BearType);
    EXPECT_EQ(bear.name, "TestBear");
    EXPECT_EQ(bear.x, 100);
    EXPECT_EQ(bear.y, 200);
}

TEST(NPCCreation, CreateElf) {
    Elf elf("TestElf", 150, 250);
    EXPECT_EQ(elf.type, ElfType);
    EXPECT_EQ(elf.name, "TestElf");
    EXPECT_EQ(elf.x, 150);
    EXPECT_EQ(elf.y, 250);
}

TEST(NPCCreation, CreateBandit) {
    Bandit bandit("TestBandit", 200, 300);
    EXPECT_EQ(bandit.type, BanditType);
    EXPECT_EQ(bandit.name, "TestBandit");
    EXPECT_EQ(bandit.x, 200);
    EXPECT_EQ(bandit.y, 300);
}

TEST(Serialization, SaveAndLoadBear) {
    auto bear = std::make_shared<Bear>("SavedBear", 123, 456);
    
    std::stringstream ss;
    bear->save(ss);
    
    int type;
    ss >> type;
    EXPECT_EQ(type, BearType);
    
    Bear loaded(ss);
    EXPECT_EQ(loaded.name, "SavedBear");
    EXPECT_EQ(loaded.x, 123);
    EXPECT_EQ(loaded.y, 456);
}

TEST(Serialization, SaveAndLoadElf) {
    auto elf = std::make_shared<Elf>("SavedElf", 234, 567);
    
    std::stringstream ss;
    elf->save(ss);
    
    int type;
    ss >> type;
    EXPECT_EQ(type, ElfType);
    
    Elf loaded(ss);
    EXPECT_EQ(loaded.name, "SavedElf");
    EXPECT_EQ(loaded.x, 234);
    EXPECT_EQ(loaded.y, 567);
}

TEST(Serialization, SaveAndLoadBandit) {
    auto bandit = std::make_shared<Bandit>("SavedBandit", 345, 678);
    
    std::stringstream ss;
    bandit->save(ss);
    
    int type;
    ss >> type;
    EXPECT_EQ(type, BanditType);
    
    Bandit loaded(ss);
    EXPECT_EQ(loaded.name, "SavedBandit");
    EXPECT_EQ(loaded.x, 345);
    EXPECT_EQ(loaded.y, 678);
}

TEST(Print, BearPrint) {
    Bear bear("PrintBear", 10, 20);
    std::stringstream ss;
    bear.print(ss);
    EXPECT_EQ(ss.str(), "Медведь: PrintBear { x:10, y:20} \n");
}

TEST(Print, ElfPrint) {
    Elf elf("PrintElf", 30, 40);
    std::stringstream ss;
    elf.print(ss);
    EXPECT_EQ(ss.str(), "Эльф: PrintElf { x:30, y:40} \n");
}

TEST(Print, BanditPrint) {
    Bandit bandit("PrintBandit", 50, 60);
    std::stringstream ss;
    bandit.print(ss);
    EXPECT_EQ(ss.str(), "Разбойник: PrintBandit { x:50, y:60} \n");
}

TEST(Movement, GetMoveDistance) {
    Bear bear("Bear", 0, 0);
    EXPECT_EQ(bear.get_move_distance(), 5);

    Elf elf("Elf", 0, 0);
    EXPECT_EQ(elf.get_move_distance(), 10);

    Bandit bandit("Bandit", 0, 0);
    EXPECT_EQ(bandit.get_move_distance(), 10);
}

TEST(Movement, StayWithinBounds) {
    Bear bear("Bear", 0, 0);
    bear.move(-10, -10, 100, 100);
    auto pos = bear.position();
    EXPECT_EQ(pos.first, 0);
    EXPECT_EQ(pos.second, 0);

    bear.move(150, 150, 100, 100);
    pos = bear.position();
    EXPECT_EQ(pos.first, 100);
    EXPECT_EQ(pos.second, 100);
}

TEST(Distance, GetKillDistance) {
    Bear bear("Bear", 0, 0);
    EXPECT_EQ(bear.get_kill_distance(), 10);

    Elf elf("Elf", 0, 0);
    EXPECT_EQ(elf.get_kill_distance(), 50);

    Bandit bandit("Bandit", 0, 0);
    EXPECT_EQ(bandit.get_kill_distance(), 10);
}

TEST(Distance, IsClose) {
    auto npc1 = std::make_shared<Bear>("Bear1", 0, 0);
    auto npc2 = std::make_shared<Elf>("Elf2", 3, 4);
    EXPECT_TRUE(npc1->is_close(npc2, 5));
    EXPECT_FALSE(npc1->is_close(npc2, 4));
}

TEST(Fight, BearKillsElfLose) {
    srand(0);
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 0, 0);
    bool success = elf->accept(bear);
    EXPECT_FALSE(success);
    EXPECT_TRUE(elf->is_alive());
}

class MockObserver : public IFightObserver {
public:
    bool called = false;
    std::shared_ptr<NPC> last_attacker;
    std::shared_ptr<NPC> last_defender;
    bool last_win;

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        called = true;
        last_attacker = attacker;
        last_defender = defender;
        last_win = win;
    }
};

TEST(Observer, NoNotifyOnFightLose) {
    auto mock = std::make_shared<MockObserver>();
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    bear->subscribe(mock);
    auto elf = std::make_shared<Elf>("Elf", 0, 0);
    srand(0);
    bear->visit(elf);
    EXPECT_FALSE(mock->called);
}

TEST(MapDrawing, SimpleDrawWithOneNPC) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto bear = std::make_shared<Bear>("Bear", 25, 25);
    npcs.push_back(bear);

    ::testing::internal::CaptureStdout();
    draw_map(npcs);
    std::string output = ::testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("\033[33mM\033[0m"), std::string::npos);
    EXPECT_NE(output.find("Медведи: 1"), std::string::npos);
}

TEST(EdgeCases, EmptyName) {
    Bear bear("", 0, 0);
    EXPECT_EQ(bear.name, "");
}

TEST(EdgeCases, NegativeCoordinates) {
    Elf elf("Elf", -100, -200);
    EXPECT_EQ(elf.x, -100);
    EXPECT_EQ(elf.y, -200);
}

TEST(EdgeCases, NegativeCoordinatesMove) {
    Elf elf("Elf", -100, -200);
    elf.move(-10, -10, 100, 100);
    auto pos = elf.position();
    EXPECT_EQ(pos.first, 0);
    EXPECT_EQ(pos.second, 0);
}

TEST(EdgeCases, ZeroDistance) {
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    EXPECT_FALSE(bear->is_close(elf, 0));
}

TEST(Integration, SaveAndLoadFile) {
    set_t original;
    original.insert(std::make_shared<Bear>("Bear1", 100, 200));
    original.insert(std::make_shared<Elf>("Elf1", 150, 250));
    original.insert(std::make_shared<Bandit>("Bandit1", 200, 300));
    
    std::string filename = "test_npc.txt";
    std::ofstream ofs(filename);
    ofs << original.size() << std::endl;
    for (auto& npc : original)
        npc->save(ofs);
    ofs.close();
    
    set_t loaded;
    std::ifstream ifs(filename);
    ASSERT_TRUE(ifs.is_open());
    
    int count;
    ifs >> count;
    EXPECT_EQ(count, 3);
    
    ifs.close();
    std::remove(filename.c_str());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
